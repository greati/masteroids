#include "Asteroid.h"
#include "MathVector.h"
#include "Universe.h"
#include "BulletShip.h"
#include "BulletAlien.h"
#include "PhysicalEntity.h"
#include "CollisionTools.h"
#include "Collectable.h"
#include "Configuration.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Asteroid::Asteroid(MathVector _position, Universe & _universe, int _type, MathVector _velocity, int _lifePoints) : Enemy(_universe) {
	alive = true;
	isFollowing = false;	
	// Setting position
	position = _position;
	// Setting velocity;
	velocity = _velocity;
	//velocity.horizontal = _velocity.horizontal;
	//velocity.vertical = _velocity.vertical;
	// Setting angle
	angleVelocity = 1;
	// Setting the type of asteroid
	type = _type;
	radius = 200;
	angle.horizontal = 1;
	angle.vertical = 1;
	exploding = sf::Time::Zero;
	switch(type){
		case Type::CLASSIC:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::ClassicAsteroid));
			currentLifePoints = maxLifePoints = 4;
			break;
		case Type::SMALL_CLASSIC:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::ClassicAsteroid));
			sprite.setScale(.8,.8);
			currentLifePoints = maxLifePoints = 2;
			break;
		case Type::EXPLOSIVE:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::ExplosiveAsteroid));
			currentLifePoints = maxLifePoints = 6;
			break;
		case Type::FOLLOWER:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::FollowerAsteroid));
			currentLifePoints = maxLifePoints = 3;
			break;
		case Type::INDESTRUCTIBLE:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::IndestructibleAsteroid));
			currentLifePoints = maxLifePoints = 1000000;
			break;
		default:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::ClassicAsteroid));
			currentLifePoints = maxLifePoints = 1;
	}

	// Setting movement direction
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setRotation(0.0);
}

void Asteroid::update(sf::Time deltaTime) {
	sprite.rotate(angleVelocity);
	if (isFollowing) {
		double _angle = std::atan2(toFollow->getPosition().vertical - position.vertical,
							   toFollow->getPosition().horizontal - position.horizontal);
		velocity.horizontal = std::cos(_angle) * 1;
		velocity.vertical = std::sin(_angle) * 1;
	}
	// Updating position
	position.horizontal += velocity.horizontal; //* angle.horizontal; //% Configuration::WINDOW_WIDTH;// * seconds;
	position.vertical += velocity.vertical; //* angle.vertical; //% Configuration::WINDOW_HEIGHT;// seconds;
	sprite.setPosition(position.horizontal, position.vertical);
	
	//Lifebar update
	lifeBar.setPosition(position.horizontal, position.vertical + 30);	
	lifeBar.setSize(sf::Vector2f(currentLifePoints*30/maxLifePoints, 3)); // curLife * BAR_SIZE / MAX_LIFE

	if (type != Type::EXPLOSIVE && currentLifePoints <= 0) {
		universe.addEntity(PhysicalEntity::EntityType::Explosion, new AnimatedPhysicalEntity(Configuration::textures.get(Configuration::Textures::ExplosionA), universe, 128, 128, sf::seconds(0.01), position));
		alive = false;
	}
	
	if(exploded){
		if(exploding >= deltaTime){
			exploded = false;
			alive = false;
			exploding = sf::Time::Zero;
		}
		exploding += deltaTime;
	}
}

bool Asteroid::isColliding(const PhysicalEntity & other) const {
	if (dynamic_cast<const Enemy*>(&other) == nullptr && 
		dynamic_cast<const Collectable*>(&other) == nullptr && 
		dynamic_cast<const AnimatedPhysicalEntity*>(&other) == nullptr) {
		if (CollisionTools::circleCollision(*this, other))
			return true;
	}
	return false;
}

void Asteroid::onCollide(PhysicalEntity & other) {
	bool bullet = false;
	if (dynamic_cast<const BulletShip*>(&other) != nullptr) {
		currentLifePoints -= other.getDamagePoints();
		bullet = true;
		if (dynamic_cast<const BulletShip*>(&other)->slowAsteroidEffect()) {
			velocity.horizontal *= .5;
			velocity.vertical *= .5;
		}
	} else if(dynamic_cast<const BulletAlien*>(&other) != nullptr) {
		currentLifePoints -= other.getDamagePoints();
	} else if (dynamic_cast<const Player*>(&other) != nullptr) {
		if (!(dynamic_cast<const Player*>(&other)->isByPassing())) {
			currentLifePoints *= 9;
			currentLifePoints /= 10;
		}
	}

	switch(type){
		case Type::CLASSIC:
			if(bullet && currentLifePoints > 0){
				universe.addEntity(PhysicalEntity::EntityType::Asteroid, new Asteroid(position, universe, Asteroid::Type::SMALL_CLASSIC, {velocity.horizontal, velocity.vertical * (-1)}));
				universe.addEntity(PhysicalEntity::EntityType::Asteroid, new Asteroid(position, universe, Asteroid::Type::SMALL_CLASSIC, {velocity.horizontal * (-1), velocity.vertical}));
				currentLifePoints = 0;						
			}
			alive = false;
			universe.addEntity(PhysicalEntity::EntityType::Explosion, new AnimatedPhysicalEntity(Configuration::textures.get(Configuration::Textures::ExplosionA), universe, 128, 128, sf::seconds(0.01), position));
			Configuration::musics.get(Configuration::Musics::Explosion).play();
		break;
		case Type::SMALL_CLASSIC:
			alive = false;
			universe.addEntity(PhysicalEntity::EntityType::Explosion, new AnimatedPhysicalEntity(Configuration::textures.get(Configuration::Textures::ExplosionA), universe, 128, 128, sf::seconds(0.01), position));
			Configuration::musics.get(Configuration::Musics::Explosion).play();
		break;
		case Type::EXPLOSIVE:
			if(currentLifePoints <= 0) {
				exploded = true;
				universe.addEntity(PhysicalEntity::EntityType::Explosion, new AnimatedPhysicalEntity(Configuration::textures.get(Configuration::Textures::ExplosionA), universe, 128, 128, sf::seconds(0.01), position));
				Configuration::musics.get(Configuration::Musics::Explosion).play();
			}
		break;
		case Type::FOLLOWER:
			if(currentLifePoints <= 0){
				alive = false;
				universe.addEntity(PhysicalEntity::EntityType::Explosion, new AnimatedPhysicalEntity(Configuration::textures.get(Configuration::Textures::ExplosionA), universe, 128, 128, sf::seconds(0.01), position));
				Configuration::musics.get(Configuration::Musics::Explosion).play();
			}
		break;
		case Type::INDESTRUCTIBLE:
			break;
		default:
			alive = false;
	}

	if(bullet && currentLifePoints <= 0){
		Collectable::CollectableType toDrop = Collectable::randCollectable();
		if (toDrop != Collectable::CollectableType::None) {	
			universe.addEntity(PhysicalEntity::EntityType::Collectable, 
					   new Collectable (toDrop, 
					   position, Configuration::textures.get(Configuration::Textures::Collectables), 
				           universe, 35, 35, sf::seconds(1)));
		}
		dynamic_cast<const BulletShip*>(&other)->_player->increaseScore(maxLifePoints);
	}
}

bool Asteroid::isClosing(const PhysicalEntity & other) const {
	float dist = std::sqrt(std::pow(position.horizontal - other.getPosition().horizontal, 2) + 
						  	   std::pow(position.vertical - other.getPosition().vertical, 2));	
	if (type == Type::FOLLOWER || (type == Type::EXPLOSIVE && exploded)) {
		if(dist <= radius){
			return true;	
		}
	}

	return false;
}

void Asteroid::onClose(PhysicalEntity & other) {
	switch(type){
		case Type::FOLLOWER:
			if (dynamic_cast<const Player*>(&other) != nullptr) {
				toFollow = dynamic_cast<const Player*>(&other);
				isFollowing = true;
			}
			break;
		case Type::EXPLOSIVE:
			if(exploded){
				other.decreaseLifePoints(2);
			}
			break;
		default:
			return; 
	}
}
