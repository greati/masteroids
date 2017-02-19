#ifndef _PENTITY_
#define _PENTITY_

#include "MathVector.h"
#include "GeneralEntity.h"

class Universe;

class PhysicalEntity : public GeneralEntity, public sf::Drawable {

	protected:
		MathVector velocity;
		MathVector position;
		MathVector acceleration;
		double angleVelocity;	
		double angle;
		int radius;
		bool exploded;
		int maxLifePoints;
		int currentLifePoints;
		int damagePoints;
		int type;
		
		Universe & universe;		

		sf::Sprite sprite;
		sf::Time exploding;
	public:
	
		enum class EntityType : int {
			Player,
			Asteroid,
			Explosion,
			Bullet,
			Collectable,
			Alien
		};

		PhysicalEntity(Universe &);
		MathVector getPosition() const;
		MathVector getVelocity() const;
		double getRotationRad() const;
		double getRotationDegree() const;
		void setPosition(MathVector);
		double getWidth() const;
		double getHeigth() const;
		virtual void update(sf::Time deltaTime) = 0;
		bool isAlive() const;	
	
		virtual bool isColliding(const PhysicalEntity &) const = 0;
		virtual void onCollide(PhysicalEntity &) = 0;

		virtual bool isClosing(const PhysicalEntity &) const = 0;
		virtual void onClose(PhysicalEntity &) = 0;
		
		void decreaseLifePoints(int _delta);
		bool isExploded() const;
		void killEntity();
		int getDamagePoints() const;
		bool isInsideWindow();
		int getMaxLifePoints() const;
		int getCurrentLifePoints() const;

	protected:
		int angleAdjustment;
		bool alive;
		bool collidable;
	private:
		friend class Universe;
		virtual void draw(sf::RenderTarget & target, 
				  sf::RenderStates states) const override;
};

#endif

