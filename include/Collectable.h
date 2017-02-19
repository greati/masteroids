#ifndef _COLLECT_
#define _COLLECT_

#include "AnimatedPhysicalEntity.h"

class Universe;

class Collectable : public AnimatedPhysicalEntity {
	public:
		enum CollectableType {
			DamageUp = 0,			/*!< Increase player's damage */
			PrecisionUp = 1,			/*!< Increase bullet's precision */
			Indestructible = 2,			/*!< Makes players indestructible */
			SlowAsteroid = 3,			/*!< Slow asteroids */
			ByPass = 4,
			WeaponUp = 5,
			None = 6				/*!< Player can pass through asteroids */
		};

		Collectable(const Collectable &) = delete;	
		Collectable & operator=(const Collectable &) = delete;
		Collectable(CollectableType, MathVector &, sf::Texture &, Universe &, double, double, sf::Time);
		
		void update(sf::Time deltaTime);
		bool isColliding(const PhysicalEntity &) const;
		void onCollide(PhysicalEntity &);
		void onClose(PhysicalEntity &);
		bool isClosing(const PhysicalEntity &) const;
		CollectableType static randCollectable();
		
		CollectableType type;
		
		private:
				
};

#endif
