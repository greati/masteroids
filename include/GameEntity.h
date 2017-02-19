#ifndef _GENTITY_
#define _GENTITY_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "GeneralEntity.h"

class GameEntity : public GeneralEntity, public sf::RenderWindow {

	public:
		GameEntity (int width, int height, std::string const & title) : 
				GeneralEntity(), 
			   	sf::RenderWindow (sf::VideoMode(width, height), title) { /* Empty */ }; 
		
		virtual void run(int minFramesPerSec);
		virtual void proccessEvents() = 0;
		virtual void update(sf::Time deltaTime) = 0;
		virtual void render() = 0;
};

#endif

