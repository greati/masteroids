#ifndef _STAGE_
#define _STAGE_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Universe;
class Player;
class Asteroid;

class Stage : public sf::Drawable{

	protected:
		sf::Sprite sprite;
		Universe * universe;
		int type;
		int createdAliens;
		Player * player;
		sf::Time currentDuration;

	public:
		enum Stages{
			EARTH,
			KEPLER,
			BLUE
		};

		Stage();
		Stage(Universe * _universe, int _type, Player * _player);
		virtual void update(sf::Time deltaTime);
		void updateEarth(sf::Time deltaTime);
		void updateKepler(sf::Time deltaTime);
		void updateBlue(sf::Time deltaTime);
		int getAsteroid(int max);
		int getNumberAliens();

		void draw(sf::RenderTarget & target, 
				  sf::RenderStates states) const override;
};

#endif