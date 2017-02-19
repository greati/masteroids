#ifndef _UNIVERSE_
#define _UNIVERSE_

#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Alien.h"
#include "PhysicalEntity.h"

class Universe : public sf::Drawable {
	
	public:
		Universe(const Universe &) = delete;
		Universe & operator=(const Universe &) = delete;
	
		Universe();

		void proccessEvents();
		void update(sf::Time deltaTime);
		void clear();
		bool existPlayer();

		void addEntity(PhysicalEntity::EntityType, PhysicalEntity * newEntity);

		std::multimap<PhysicalEntity::EntityType, PhysicalEntity*> & getEntities();
		std::list<Player*> & getPlayers();
		std::list<Bullet*> & getBullets();
		std::list<Asteroid*> & getAsteroids();
		std::list<Alien*> & getAliens();

	private:
		virtual void draw(sf::RenderTarget & target, 
				  sf::RenderStates states) const override;
		
		std::multimap<PhysicalEntity::EntityType, PhysicalEntity*> entitiesList;
		std::multimap<PhysicalEntity::EntityType, PhysicalEntity*> entitiesList_temp;
		
		std::list<Bullet*> bulletList;	
		std::list<Player*> playersList;	
		std::list<Asteroid*> asteroidList;
		std::list<Alien*> alienList;
};

#endif
