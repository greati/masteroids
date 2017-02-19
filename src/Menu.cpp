#include "Menu.h"
#include "Configuration.h"
#include <iostream>

Menu::Menu(Universe * _universe, int _type, sf::Texture & _texture, double _frameWidth, double _frameHeigth, sf::Time _frameDuration) : ActionTarget(Configuration::playerInputs) {
	type = Menu::Type::INITIAL;
	level = -2;
	
	universe = _universe;
	texture = _texture;
	frameWidth = _frameWidth;
	frameHeigth = _frameHeigth;
	frameDuration = _frameDuration;
	stage = nullptr;
	hud = nullptr;

	logo.setTexture(Configuration::textures.get(Configuration::Textures::MenuLogo));

	start.setTexture(Configuration::textures.get(Configuration::Textures::MenuStart));
	start.setPosition(250, 400);

	_exit.setTexture(Configuration::textures.get(Configuration::Textures::MenuExit));
	_exit.setPosition(250, 500);

	earth.setTexture(Configuration::textures.get(Configuration::Textures::IconEarth));
	earth.setPosition(224, 152);

	kepler.setTexture(Configuration::textures.get(Configuration::Textures::IconKepler));
	kepler.setPosition(0, 446);

	blue.setTexture(Configuration::textures.get(Configuration::Textures::IconBlue));
	blue.setPosition(436, 0);

	bg.setTexture(Configuration::textures.get(Configuration::Textures::StagesBg));
	bg.setPosition(0, 0);

	font.loadFromFile("media/Fonts/Colleged.ttf");

	finalText.setFont(font);
	finalText.setString("You Win");
	finalText.setPosition(200, 200);
	finalText.setColor(sf::Color::White);
	finalText.setCharacterSize(70);

	Configuration::musics.get(Configuration::Musics::InitialStage).setPlayingOffset(sf::seconds(2));
	Configuration::musics.get(Configuration::Musics::InitialStage).setLoop(true);
	Configuration::musics.get(Configuration::Musics::InitialStage).play();

	bind(Configuration::PlayerInputs::Click, [this](const sf::Event & e) {
		switch(type){
			case Menu::Type::INITIAL:
				if(isInside(e, start)){
					type = Menu::Type::STAGE;
				}else if(isInside(e, _exit)){
					Configuration::toClose = true;
				}
			break;
			case Menu::Type::STAGE:
				if(isInside(e, earth)){
					Configuration::musics.get(Configuration::Musics::InitialStage).stop();
					
					Configuration::musics.get(Configuration::Musics::Stages).setPlayingOffset(sf::seconds(7));
					Configuration::musics.get(Configuration::Musics::Stages).setLoop(true);
					Configuration::musics.get(Configuration::Musics::Stages).setVolume(50);
					Configuration::musics.get(Configuration::Musics::Stages).play();

					level = Stage::Stages::EARTH;
					if(stage != nullptr) delete stage;
					if(hud != nullptr) delete hud;

					player = new Player(texture, *universe, frameWidth, frameHeigth, frameDuration);
					universe->addEntity(PhysicalEntity::EntityType::Player, player);
					stage = new Stage(universe, level, player);
					hud = new Hud(player);
				}else if(isInside(e, kepler)){
					Configuration::musics.get(Configuration::Musics::InitialStage).stop();
					
					Configuration::musics.get(Configuration::Musics::Stages).setPlayingOffset(sf::seconds(7));
					Configuration::musics.get(Configuration::Musics::Stages).setLoop(true);
					Configuration::musics.get(Configuration::Musics::Stages).setVolume(50);
					Configuration::musics.get(Configuration::Musics::Stages).play();

					if(stage != nullptr) delete stage;
					if(hud != nullptr) delete hud;

					level = Stage::Stages::KEPLER;
					player = new Player(texture, *universe, frameWidth, frameHeigth, frameDuration);
					universe->addEntity(PhysicalEntity::EntityType::Player, player);
					stage = new Stage(universe, level, player);
					hud = new Hud(player);
				}else if(isInside(e, blue)){
					Configuration::musics.get(Configuration::Musics::InitialStage).stop();
					
					Configuration::musics.get(Configuration::Musics::Stages).setPlayingOffset(sf::seconds(7));
					Configuration::musics.get(Configuration::Musics::Stages).setLoop(true);
					Configuration::musics.get(Configuration::Musics::Stages).setVolume(50);
					Configuration::musics.get(Configuration::Musics::Stages).play();

					if(stage != nullptr) delete stage;
					if(hud != nullptr) delete hud;

					level = Stage::Stages::BLUE;
					player = new Player(texture, *universe, frameWidth, frameHeigth, frameDuration);
					universe->addEntity(PhysicalEntity::EntityType::Player, player);
					stage = new Stage(universe, level, player);
					hud = new Hud(player);
				}
			break;
			case Menu::Type::GAMEOVER:
			case Menu::Type::PLAYERWINS:
				if(isInside(e, start)){
					type = Menu::Type::STAGE;
					level = -1;
				}else if(isInside(e, _exit)){
					Configuration::toClose = true;
				}				
			break;
			default:
			break;
		}
	});
}

void Menu::update(sf::Time deltaTime){
	if(level > -1){
		if(!universe->existPlayer()){
			level = -1;
			finalText.setPosition(150, 200);
			finalText.setString("GAME OVER");
			type = Menu::Type::GAMEOVER;
			Configuration::musics.get(Configuration::Musics::Stages).stop();
			Configuration::musics.get(Configuration::Musics::GameOver).play();
			Configuration::musics.get(Configuration::Musics::InitialStage).setPlayingOffset(sf::seconds(2));
			Configuration::musics.get(Configuration::Musics::InitialStage).setLoop(true);
			Configuration::musics.get(Configuration::Musics::InitialStage).play();
		}else{
			stage->update(deltaTime);
			hud->update();
			switch(level){
				case Stage::Stages::EARTH:
					if(player->getScore() > 500 && stage->getNumberAliens() >= 5){
						level = -1;					
						finalText.setPosition(200, 200);
						finalText.setString("You Win");
						type = Menu::Type::PLAYERWINS;
						Configuration::musics.get(Configuration::Musics::Stages).stop();
						Configuration::musics.get(Configuration::Musics::YouWin).play();
						Configuration::musics.get(Configuration::Musics::InitialStage).setPlayingOffset(sf::seconds(2));
						Configuration::musics.get(Configuration::Musics::InitialStage).setLoop(true);
						Configuration::musics.get(Configuration::Musics::InitialStage).play();
					}
				break;
				case Stage::Stages::KEPLER:
					if(player->getScore() > 1000 && stage->getNumberAliens() >= 10){
						level = -1;
						finalText.setPosition(200, 200);
						finalText.setString("You Win");
						type = Menu::Type::PLAYERWINS;
						Configuration::musics.get(Configuration::Musics::Stages).stop();
						Configuration::musics.get(Configuration::Musics::YouWin).play();
						Configuration::musics.get(Configuration::Musics::InitialStage).setPlayingOffset(sf::seconds(2));
						Configuration::musics.get(Configuration::Musics::InitialStage).setLoop(true);
						Configuration::musics.get(Configuration::Musics::InitialStage).play();
					}
				break;
				case Stage::Stages::BLUE:
					if(player->getScore() > 1500 && stage->getNumberAliens() >= 15){
						level = -1;
						finalText.setPosition(200, 200);
						finalText.setString("You Win");
						type = Menu::Type::PLAYERWINS;
						Configuration::musics.get(Configuration::Musics::Stages).stop();
						Configuration::musics.get(Configuration::Musics::YouWin).play();
						Configuration::musics.get(Configuration::Musics::InitialStage).setPlayingOffset(sf::seconds(2));
						Configuration::musics.get(Configuration::Musics::InitialStage).setLoop(true);
						Configuration::musics.get(Configuration::Musics::InitialStage).play();
					}
				break;
				default:
				return;
			}
		}
		
	}else{
		universe->clear();
	}
	
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if(level > -1){
		stage->draw(target, states);
		hud->draw(target, states);
	}else{
		if(level == -1){
			stage->draw(target, states);
		}
		switch(type){
			case Menu::Type::INITIAL:
				target.draw(logo, states);
				target.draw(start, states);
				target.draw(_exit, states);
			break;
			case Menu::Type::STAGE:
				target.draw(bg, states);
				target.draw(earth, states);
				target.draw(kepler, states);
				target.draw(blue, states);
			break;
			case Menu::Type::GAMEOVER:
			case Menu::Type::PLAYERWINS:
				target.draw(finalText, states);
				target.draw(start, states);
				target.draw(_exit, states);
			break;
			default:
			break;
		}
	}
	
}

bool Menu::isInside(const sf::Event & _mouse, sf::Sprite & sprite){
	if(_mouse.mouseButton.x >= sprite.getPosition().x && _mouse.mouseButton.x <= sprite.getPosition().x + sprite.getTexture()->getSize().x &&
	   _mouse.mouseButton.y >= sprite.getPosition().y && _mouse.mouseButton.y <= sprite.getPosition().y + sprite.getTexture()->getSize().y){
		return true;
	}else{
		return false;
	}
}
