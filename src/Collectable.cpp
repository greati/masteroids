#include "Collectable.h"
#include "Universe.h"
#include "CollisionTools.h"
#include "MathVector.h"

Collectable::Collectable(Collectable::CollectableType _type, MathVector & initialPos, sf::Texture & _texture, Universe & _universe, double _frameW, double _frameH, sf::Time _frameDuration) : AnimatedPhysicalEntity(_texture, _universe, _frameW, _frameH, _frameDuration), type {_type} {
	position = initialPos;
	setCurrentFrame(type);	
	stop();
}

void Collectable::update(sf::Time deltaTime) {
	AnimatedPhysicalEntity::update(deltaTime);
	sprite.setPosition(position.horizontal, position.vertical);
}

bool Collectable::isColliding(const PhysicalEntity & other) const {
	if (dynamic_cast<const Player*>(&other) != nullptr) {
		if (CollisionTools::circleCollision(*this, other)) {
			return true;
		}
	}
	return false;
}

void Collectable::onCollide(PhysicalEntity & other) {
	if (not collidable) return;
	if (dynamic_cast<const Player*>(&other) != nullptr) { 
		Configuration::musics.get(Configuration::Musics::PowerUp).play();
		Player * p = dynamic_cast<Player*>(&other); 
		switch(type) {
			case CollectableType::DamageUp:
			case CollectableType::PrecisionUp:
			case CollectableType::Indestructible:
			case CollectableType::SlowAsteroid:
			case CollectableType::ByPass:
				p->collectPower(this);
			break;
			case CollectableType::WeaponUp:
				alive = false;
				p->increaseShotLevel();
			break;
		}
		collidable = false;
	}
}

bool Collectable::isClosing(const PhysicalEntity & other) const { 
	return false;  
}

void Collectable::onClose(PhysicalEntity & other) {
	return;
}

Collectable::CollectableType Collectable::randCollectable() {
	int randomic = rand() % 500;	
	if (randomic >= 0 && randomic <= 10) {
		return Collectable::CollectableType::ByPass;	
	} else if (randomic <= 20) {
		return Collectable::CollectableType::Indestructible;	
	} else if (randomic <= 30) {
		return Collectable::CollectableType::SlowAsteroid;	
	} else if (randomic <= 40) {
		return Collectable::CollectableType::PrecisionUp;	
	} else if (randomic <= 50) {
		return Collectable::CollectableType::DamageUp;	
	} else if (randomic <= 70) {
		return Collectable::CollectableType::DamageUp;	
	} else if (randomic <= 90) {
		return Collectable::CollectableType::WeaponUp;	
	} else 
		return Collectable::CollectableType::None;
}
