#include "BulletShip.h"
#include "Player.h"
#include "Asteroid.h"
#include "Collectable.h"
#include "Universe.h"
#include "CollisionTools.h"
#include "AnimatedPhysicalEntity.h"
#include <cmath>

BulletShip::BulletShip(Player & player, BulletShip::Type _type, BulletShip::SpawnPoint _spawnPoint, Universe & _universe) 
					   : Bullet { player, _universe }, type {_type}, spawnPoint {_spawnPoint} { 
	isFollowing = false;
	damagePoints = (int) type +  (player.getBonusDamage() / 10);
	_player = &player;
	switch (spawnPoint) {
		case BulletShip::SpawnPoint::FRONT:
			// Setting initial position
			position.horizontal = player.getPosition().horizontal + player.getWidth() * std::cos(player.getRotationRad()) / 2;
			position.vertical = player.getPosition().vertical + player.getWidth() * std::sin(player.getRotationRad()) / 2;
		break;
		case BulletShip::SpawnPoint::LEFT:
			// Setting initial position
			position.horizontal = player.getPosition().horizontal + player.getWidth()*.8 * std::cos(player.getRotationRad() + M_PI/2) / 2;
			position.vertical = player.getPosition().vertical + player.getWidth()*.8 * std::sin(player.getRotationRad() + M_PI/2) / 2;
		break;
		case BulletShip::SpawnPoint::RIGHT:
			// Setting initial position
			position.horizontal = player.getPosition().horizontal + player.getWidth() * .8 * std::cos(player.getRotationRad() - M_PI/2) / 2;
			position.vertical = player.getPosition().vertical + player.getWidth() *.8 * std::sin(player.getRotationRad() - M_PI/2) / 2;
		break;
		default: return;
	}

	Configuration::Textures texture;
	switch (type) {
		case BulletShip::Type::SIMPLE:
			texture = Configuration::Textures::SimpleShot;
		break;
		case BulletShip::Type::POWERFULL:
			texture = Configuration::Textures::PowerfullShot;
		break;
		case BulletShip::Type::LASER:
			texture = Configuration::Textures::LaserShot;
		break;
	}

	sprite.setTexture(Configuration::textures.get(texture));
	// Setting movement direction
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setRotation(player.getRotationDegree());
	// Setting velocity
	velocity.horizontal = std::cos(getRotationRad()) * 10;
	velocity.vertical = std::sin(getRotationRad()) * 10;
	// Setting duration
	currentDuration = sf::seconds(0.5);
}

void BulletShip::update(sf::Time deltaTime) {	
	if (isFollowing && toFollow->isAlive()) {
		double _angle = std::atan2(toFollow->getPosition().vertical - position.vertical,
							   toFollow->getPosition().horizontal - position.horizontal);
		sprite.setRotation(180 * _angle / M_PI);
		velocity.horizontal = std::cos(_angle) * 5;
		velocity.vertical = std::sin(_angle) * 5;
	}

	currentDuration -= deltaTime;
	if (currentDuration < sf::Time::Zero) {
		alive = false;
	}
	// Updating position
	position.horizontal = (position.horizontal + velocity.horizontal); 
	position.vertical = (position.vertical + velocity.vertical); 
	sprite.setPosition(position.horizontal, position.vertical);
}

bool BulletShip::isColliding(const PhysicalEntity & other) const {
	if (dynamic_cast<const BulletShip*>(&other) == nullptr && 
		dynamic_cast<const Collectable*>(&other) == nullptr &&
		dynamic_cast<const Player*>(&other) == nullptr &&
		dynamic_cast<const AnimatedPhysicalEntity*>(&other) == nullptr) {
		if (CollisionTools::circleCollision(*this, other))
			return true;
	}
	return false;
}

void BulletShip::onCollide(PhysicalEntity & other) {
	alive = false;
}

bool BulletShip::slowAsteroidEffect() const {
	return (_player)->isSlowingAsteroids();
}

bool BulletShip::isClosing(const PhysicalEntity & other) const {
	if (dynamic_cast<const Asteroid*>(&other) != nullptr) {
		float dist = std::sqrt(std::pow(position.horizontal - other.getPosition().horizontal, 2) + 
		     						std::pow(position.vertical - other.getPosition().vertical, 2));	
		if (_player->getBonusPrecision() > 0) {
			if(dist <= _player->getBonusPrecision()){
				return true;	
			}
		}
	}
	return false;
}

void BulletShip::onClose(PhysicalEntity & other) {
	if (dynamic_cast<const Asteroid*>(&other) != nullptr) {
		if (!isFollowing)  {
			toFollow = dynamic_cast<Asteroid*>(&other);
			isFollowing = true;
		}	
	}
}
