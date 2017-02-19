#ifndef _BSHIP_
#define _BSHIP_

#include "Bullet.h"

class Asteroid;

class BulletShip : public Bullet {

	public:
		enum Type {
			SIMPLE = 2,
			POWERFULL = 5,
			LASER = 10
		};

		enum SpawnPoint {
			FRONT = 0,
			LEFT,
			RIGHT
		};

		BulletShip(const BulletShip &) = delete;
		BulletShip & operator=(const BulletShip &) = delete;

		BulletShip(Player &, Type, SpawnPoint, Universe &);

		virtual void update(sf::Time deltaTime);
		bool isColliding(const PhysicalEntity &) const;
		void onCollide(PhysicalEntity &);
		bool isClosing(const PhysicalEntity &) const;
		void onClose(PhysicalEntity &);
		void setDamage(int _damage);
		bool slowAsteroidEffect() const;

		Player * _player;
		Asteroid * toFollow;
		bool isFollowing;
	private:
		Type type;
		SpawnPoint spawnPoint;
};

#endif
