#include "Masteroids.h"
#include "Configuration.h"
#include "Universe.h"

int main() {
	
	Configuration::initialize();	

	Masteroids masteroids(Configuration::WINDOW_WIDTH, Configuration::WINDOW_HEIGHT, Configuration::GAME_TITLE);
	masteroids.run(Configuration::GAME_FPS);

	return 0;
}
