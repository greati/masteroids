#ifndef _ALIEN_
#define _ALIEN_

#include "Enemy.h"

class Player;
class MathVector;
class Universe;
class PhysicalEntity;

class Alien : public Enemy {
	public:
		enum Type{
			CLASSIC = 5,
			SHOOTER = 10
		};

		Alien(const Alien &) = delete;
		Alien & operator=(const Alien &) = delete;

		Alien(MathVector position, Universe & _universe, int _type, MathVector _velocity = {1.0, 1.0}, int _lifePoint = 0);
		Alien(int h, int v, Universe & _universe, int _type, float _velX, float _velY, int _life);

		void update(sf::Time deltaTime);
		bool isColliding(const PhysicalEntity &) const;
		void onCollide(PhysicalEntity &);
		bool isClosing(const PhysicalEntity &) const;
		void onClose(PhysicalEntity &);
		void shot();


	private:
		bool isFollowing;
		const Player * toFollow;
		MathVector angle;
		int type;
		sf::Time timeLastShot;
};

#endif
