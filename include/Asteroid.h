#ifndef _ASTEROID_
#define _ASTEROID_

#include "Enemy.h"

class Player;
class MathVector;
class Universe;
class PhysicalEntity;

class Asteroid : public Enemy {
	public:
		enum Type{			
			CLASSIC = 4,			
			INDESTRUCTIBLE = 500,
			EXPLOSIVE = 6,
			FOLLOWER = 3,
			SMALL_CLASSIC = 2
		};

		Asteroid(const Asteroid &) = delete;
		Asteroid & operator=(const Asteroid &) = delete;

		Asteroid(MathVector position, Universe & _universe, int _type, MathVector _velocity = {1.0, 1.0}, int _lifePoint = 0);
		Asteroid(int h, int v, Universe & _universe, int _type, float _velX, float _velY, int _life);

		void update(sf::Time deltaTime);
		bool isColliding(const PhysicalEntity &) const;
		void onCollide(PhysicalEntity &);
		bool isClosing(const PhysicalEntity &) const;
		void onClose(PhysicalEntity &);


	private:
		bool isFollowing;
		const Player * toFollow;
		MathVector angle;
};

#endif
