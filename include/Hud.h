#ifndef _HUD_
#define _HUD_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Player;
class Collectable;

class Hud : public sf::Drawable{

	protected:

		Player * player;
		sf::RectangleShape maxLife;
		sf::RectangleShape currentLife;
		sf::RectangleShape curPower;
		sf::RectangleShape nextPower;
		int scorePoints;
		sf::Text powerTime;
		sf::Text score;
		sf::Text weaponText;
		sf::Text weaponLevel;
		sf::Text attackText;
		sf::Text attackIncrease;
		sf::Text precisionText;
		sf::Text precisionIncrease;
		sf::Text damageIncrease;
		sf::Font font;


	public:

		Hud();
		Hud(Player * _player);
		void update();

		
		void draw(sf::RenderTarget & target, 
				  sf::RenderStates states) const override;

};

#endif
