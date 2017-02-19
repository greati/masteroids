#ifndef _BALIEN_
#define _BALIEN_

#include "Bullet.h"
#include "Alien.h"

class BulletAlien : public Bullet {

	public:
		enum Type {
			SIMPLE = 3
		};

		enum SpawnPoint {
			FRONT = 0,
			LEFT,
			RIGHT
		};

		BulletAlien(const BulletAlien &) = delete;
		BulletAlien & operator=(const BulletAlien &) = delete;

		BulletAlien(Alien &, Type, SpawnPoint, Universe &);

		virtual void update(sf::Time deltaTime);
		bool isColliding(const PhysicalEntity &) const;
		void onCollide(PhysicalEntity &);
		bool isClosing(const PhysicalEntity &) const{ return false;};
		void onClose(PhysicalEntity &){return;};
		void setDamage(int _damage);
		int getType() const;

		Alien * _alien;
	private:
		Type type;
		SpawnPoint spawnPoint;
};

#endif
