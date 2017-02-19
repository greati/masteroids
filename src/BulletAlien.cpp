#include "BulletAlien.h"
#include "Alien.h"
#include "Collectable.h"
#include "Universe.h"
#include "CollisionTools.h"
#include <cmath>

BulletAlien::BulletAlien(Alien & alien, BulletAlien::Type _type, BulletAlien::SpawnPoint _spawnPoint, Universe & _universe) 
					   : Bullet { alien, _universe }, type {_type}, spawnPoint {_spawnPoint} { 
	damagePoints = (int) type;
	_alien = &alien;
	switch (spawnPoint) {
		case BulletAlien::SpawnPoint::FRONT:
			// Setting initial position
			position.horizontal = alien.getPosition().horizontal + alien.getWidth() * std::cos(alien.getRotationRad()) / 2;
			position.vertical = alien.getPosition().vertical + alien.getWidth() * std::sin(alien.getRotationRad()) / 2;
		break;
		case BulletAlien::SpawnPoint::LEFT:
			// Setting initial position
			position.horizontal = alien.getPosition().horizontal + alien.getWidth()*.8 * std::cos(alien.getRotationRad() + M_PI/2) / 2;
			position.vertical = alien.getPosition().vertical + alien.getWidth()*.8 * std::sin(alien.getRotationRad() + M_PI/2) / 2;
		break;
		case BulletAlien::SpawnPoint::RIGHT:
			// Setting initial position
			position.horizontal = alien.getPosition().horizontal + alien.getWidth() * .8 * std::cos(alien.getRotationRad() - M_PI/2) / 2;
			position.vertical = alien.getPosition().vertical + alien.getWidth() *.8 * std::sin(alien.getRotationRad() - M_PI/2) / 2;
		break;
		default: return;
	}

	Configuration::Textures texture = Configuration::Textures::SimpleAlienShot;
	sprite.setTexture(Configuration::textures.get(texture));
	// Setting movement direction
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setRotation(alien.getRotationDegree());
	// Setting velocity
	velocity.horizontal = std::cos(getRotationRad()) * 5;
	velocity.vertical = std::sin(getRotationRad()) * 5;
	// Setting duration
	currentDuration = sf::seconds(1);
	std::cout<<"criou!\n";
}

void BulletAlien::update(sf::Time deltaTime) {
	currentDuration -= deltaTime;
	if (currentDuration < sf::Time::Zero) {
		std::cout<<"Morreu\n";
		alive = false;
	}
	// Updating position
	position.horizontal = (position.horizontal + velocity.horizontal); 
	position.vertical = (position.vertical + velocity.vertical); 
	sprite.setPosition(position.horizontal, position.vertical);
}

bool BulletAlien::isColliding(const PhysicalEntity & other) const {
	if (dynamic_cast<const Player*>(&other) != nullptr) {
		if (CollisionTools::circleCollision(*this, other))
			return true;
	}
	return false;
}

void BulletAlien::onCollide(PhysicalEntity & other) {
	alive = false;
}

int BulletAlien::getType() const{
	return (int) type;
}


