#include "GameEntity.h"

void GameEntity::run(int minFramesPerSec) {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time timePerFrame = sf::seconds(1.f / minFramesPerSec);
	while (isOpen()) {
		proccessEvents();
		timeSinceLastUpdate = clock.restart();
		
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}	
		
		update(timeSinceLastUpdate);
		render();
	}
}
