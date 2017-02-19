#include "Stage.h"
#include "Player.h"
#include "Universe.h"
#include "PhysicalEntity.h"
#include "Asteroid.h"
#include "Alien.h"
#include "CollisionTools.h"
#include <iostream>

Stage::Stage(){ 
	//STUB 
}

Stage::Stage(Universe * _universe, int _type, Player * _player) : 
universe {_universe}, type {_type}, player{_player}{
	createdAliens = 0;

	switch(type){
		case Stages::EARTH:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::Earth));
		break;
		case Stages::KEPLER:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::Kepler));
		break;
		case Stages::BLUE:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::Blue));
		break;
		default:
			sprite.setTexture(Configuration::textures.get(Configuration::Textures::Earth));
		break;
	}

}

void Stage::update(sf::Time deltaTime){
	switch(type){
		case Stages::EARTH:
			updateEarth(deltaTime);		
		break;
		case Stages::KEPLER:
			updateKepler(deltaTime);	
		break;
		case Stages::BLUE:
			updateBlue(deltaTime);		
		break;
		default:
		break;
	}
}

void Stage::updateEarth(sf::Time deltaTime){
	if(currentDuration <= sf::Time::Zero){
		MathVector * newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
		while(std::sqrt(std::pow(newPos->horizontal - player->getPosition().horizontal, 2) + 
						std::pow(newPos->vertical - player->getPosition().vertical, 2)) < 2 * player->getHeigth()){
			newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
		}
		
		MathVector * auxVel = new MathVector {rand() % 2, rand() % 2};
		MathVector * newVel = new MathVector {1.0 / (rand() % 10) + .5, 1.0 / (rand() % 10) + .5};
				//std::cout<<"X: "<<newVel->horizontal<<", Y: "<<newVel->vertical<<std::endl;
		if((int)auxVel->horizontal % 2 != 0)
			newVel->horizontal *= -1;
		if((int)auxVel->vertical % 2 != 0)
			newVel->vertical *= -1;

		double _angle = std::atan2(player->getPosition().vertical - newPos->vertical,
								   player->getPosition().horizontal - newPos->horizontal);
				
		newVel->horizontal = std::cos(_angle) * 1;
		newVel->vertical = std::sin(_angle) * 1;

		universe->addEntity(PhysicalEntity::EntityType::Asteroid, new Asteroid(*newPos, *universe, getAsteroid(80), *newVel));
		currentDuration = sf::seconds(1);

		if(player->getScore() / 100 > createdAliens){
			newPos = new MathVector {rand() % 500 + 100, rand() % 300 + 100};
			while(std::sqrt(std::pow(newPos->horizontal - player->getPosition().horizontal, 2) + 
		            		std::pow(newPos->vertical - player->getPosition().vertical, 2)) < 2 * player->getHeigth()){
				newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
			}
			auxVel = new MathVector {rand() % 2, rand() % 2};
			newVel = new MathVector {(rand() % 10 + 1)/ 10.0 , (rand() % 10 + 1)/ 10.0 };
			
			if((int)auxVel->horizontal % 2 != 0)
				newVel->horizontal *= -1.0;
			if((int)auxVel->vertical % 2 != 0)
				newVel->vertical *= -1.0;

			universe->addEntity(PhysicalEntity::EntityType::Alien, new Alien(*newPos, *universe, Alien::Type::CLASSIC, *newVel));
			++createdAliens;
		}

		delete newPos;
		delete auxVel;
		delete newVel;
	}else{
		currentDuration -= deltaTime;
	}
}

void Stage::updateKepler(sf::Time deltaTime){
	if(currentDuration <= sf::Time::Zero){
		MathVector * newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
		while(std::sqrt(std::pow(newPos->horizontal - player->getPosition().horizontal, 2) + 
						std::pow(newPos->vertical - player->getPosition().vertical, 2)) < 2 * player->getHeigth()){
			newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
		}
		
		MathVector * auxVel = new MathVector {rand() % 2, rand() % 2};
		MathVector * newVel = new MathVector {1.0 / (rand() % 10) + .5, 1.0 / (rand() % 10) + .5};
				//std::cout<<"X: "<<newVel->horizontal<<", Y: "<<newVel->vertical<<std::endl;
		if((int)auxVel->horizontal % 2 != 0)
			newVel->horizontal *= -1;
		if((int)auxVel->vertical % 2 != 0)
			newVel->vertical *= -1;

		double _angle = std::atan2(player->getPosition().vertical - newPos->vertical,
								   player->getPosition().horizontal - newPos->horizontal);
				
		newVel->horizontal = std::cos(_angle) * 1;
		newVel->vertical = std::sin(_angle) * 1;

		universe->addEntity(PhysicalEntity::EntityType::Asteroid, new Asteroid(*newPos, *universe, getAsteroid(85), *newVel));
		currentDuration = sf::seconds(1);

		if(player->getScore() / 100 > createdAliens){
			newPos = new MathVector {rand() % 500 + 100, rand() % 300 + 100};
			while(std::sqrt(std::pow(newPos->horizontal - player->getPosition().horizontal, 2) + 
		            		std::pow(newPos->vertical - player->getPosition().vertical, 2)) < 2 * player->getHeigth()){
				newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
			}
			auxVel = new MathVector {rand() % 2, rand() % 2};
			newVel = new MathVector {(rand() % 10 + 1)/ 10.0 , (rand() % 10 + 1)/ 10.0 };
			
			if((int)auxVel->horizontal % 2 != 0)
				newVel->horizontal *= -1.0;
			if((int)auxVel->vertical % 2 != 0)
				newVel->vertical *= -1.0;

			universe->addEntity(PhysicalEntity::EntityType::Alien, new Alien(*newPos, *universe, Alien::Type::CLASSIC, *newVel));
			++createdAliens;
		}

		delete newPos;
		delete auxVel;
		delete newVel;
	}else{
		currentDuration -= deltaTime;
	}
}

void Stage::updateBlue(sf::Time deltaTime){
	if(currentDuration <= sf::Time::Zero){
		MathVector * newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
		while(std::sqrt(std::pow(newPos->horizontal - player->getPosition().horizontal, 2) + 
						std::pow(newPos->vertical - player->getPosition().vertical, 2)) < 2 * player->getHeigth()){
			newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
		}
		
		MathVector * auxVel = new MathVector {rand() % 2, rand() % 2};
		MathVector * newVel = new MathVector {1.0 / (rand() % 10) + .5, 1.0 / (rand() % 10) + .5};
				//std::cout<<"X: "<<newVel->horizontal<<", Y: "<<newVel->vertical<<std::endl;
		if((int)auxVel->horizontal % 2 != 0)
			newVel->horizontal *= -1;
		if((int)auxVel->vertical % 2 != 0)
			newVel->vertical *= -1;

		double _angle = std::atan2(player->getPosition().vertical - newPos->vertical,
								   player->getPosition().horizontal - newPos->horizontal);
				
		newVel->horizontal = std::cos(_angle) * 1;
		newVel->vertical = std::sin(_angle) * 1;

		universe->addEntity(PhysicalEntity::EntityType::Asteroid, new Asteroid(*newPos, *universe, getAsteroid(100), *newVel));
		currentDuration = sf::seconds(1);

		if(player->getScore() / 100 > createdAliens){
			newPos = new MathVector {rand() % 500 + 100, rand() % 300 + 100};
			while(std::sqrt(std::pow(newPos->horizontal - player->getPosition().horizontal, 2) + 
		            		std::pow(newPos->vertical - player->getPosition().vertical, 2)) < 2 * player->getHeigth()){
				newPos = new MathVector {rand() % 700 + 100, rand() % 500 + 100};
			}
			auxVel = new MathVector {rand() % 2, rand() % 2};
			newVel = new MathVector {(rand() % 10 + 1)/ 10.0 , (rand() % 10 + 1)/ 10.0 };
			
			if((int)auxVel->horizontal % 2 != 0)
				newVel->horizontal *= -1.0;
			if((int)auxVel->vertical % 2 != 0)
				newVel->vertical *= -1.0;
							
			universe->addEntity(PhysicalEntity::EntityType::Alien, new Alien(*newPos, *universe, Alien::Type::SHOOTER, *newVel));
			++createdAliens;
		}

		delete newPos;
		delete auxVel;
		delete newVel;
	}else{
		currentDuration -= deltaTime;
	}
}

int Stage::getAsteroid(int max){
	int random = rand() % max;
	if(random < 50){
		return Asteroid::Type::CLASSIC;
	}else if(random < 80){
		return Asteroid::Type::EXPLOSIVE;
	}else if(random < 95){		
		return Asteroid::Type::FOLLOWER;
	}else{
		return Asteroid::Type::INDESTRUCTIBLE;
	}
}

void Stage::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

int Stage::getNumberAliens(){
	return createdAliens;
}