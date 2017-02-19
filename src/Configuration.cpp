#include "Configuration.h"

int Configuration::WINDOW_WIDTH = 800;
int Configuration::WINDOW_HEIGHT = 600;
std::string Configuration::GAME_TITLE = "Masteroids";
int Configuration::GAME_FPS = 60;
bool Configuration::toClose = false;

ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::Music, int> Configuration::musics;
ActionMap<int> Configuration::playerInputs;

void Configuration::initialize() {
	initTextures();
	initMusics();
	initPlayerInputs();
}

void Configuration::initTextures() {
	textures.load(Textures::Player, "media/Player/ship.png");
	textures.load(Textures::SimpleShot, "media/Bullets/simple.png");
	textures.load(Textures::PowerfullShot, "media/Bullets/powerfull.png");
	textures.load(Textures::LaserShot, "media/Bullets/laser.png");
	textures.load(Textures::SimpleAlienShot, "media/Bullets/simpleAlien.png");	
	textures.load(Textures::ClassicAsteroid, "media/Asteroids/classicAsteroid.png");
	textures.load(Textures::ExplosiveAsteroid, "media/Asteroids/explosiveAsteroid.png");
	textures.load(Textures::FollowerAsteroid, "media/Asteroids/followerAsteroid.png");
	textures.load(Textures::IndestructibleAsteroid, "media/Asteroids/indestructibleAsteroid.png");
	textures.load(Textures::Collectables, "media/Items/collectables.png");
	textures.load(Textures::ClassicAlien, "media/Aliens/classicAlien.png");
	textures.load(Textures::ShooterAlien, "media/Aliens/shooterAlien.png");
	textures.load(Textures::ExplosionA, "media/Explosion/explosionA.png");
	textures.load(Textures::ExplosionB, "media/Explosion/explosionB.png");
	textures.load(Textures::ExplosionC, "media/Explosion/explosionC.png");
	textures.load(Textures::Earth, "media/Bg/earth.png");
	textures.load(Textures::Kepler, "media/Bg/kepler.png");
	textures.load(Textures::Blue, "media/Bg/blue.png");
	textures.load(Textures::MenuLogo, "media/Menu/logo.png");
	textures.load(Textures::MenuStart, "media/Menu/start.png");
	textures.load(Textures::MenuExit, "media/Menu/exit.png");
	textures.load(Textures::IconEarth, "media/Menu/earthIcon.png");
	textures.load(Textures::IconKepler, "media/Menu/keplerIcon.png");
	textures.load(Textures::IconBlue, "media/Menu/blueIcon.png");
	textures.load(Textures::StagesBg, "media/Bg/stages.png");
}

void Configuration::initMusics(){
	musics.load(Musics::Shot, "media/Musics/shot.wav");
	musics.load(Musics::Explosion, "media/Musics/explosion.wav");
	musics.load(Musics::GameOver, "media/Musics/gameover.wav");
	musics.load(Musics::PowerUp, "media/Musics/powerup.wav");
	musics.load(Musics::YouWin, "media/Musics/win.wav");
	musics.load(Musics::InitialStage, "media/Musics/initial_stages.wav");
	musics.load(Musics::Stages, "media/Musics/stage.wav");
}

void Configuration::initPlayerInputs() {
	playerInputs.map(PlayerInputs::Thrust, Action(sf::Keyboard::Up));
	playerInputs.map(PlayerInputs::TurnLeft, Action(sf::Keyboard::Left));
	playerInputs.map(PlayerInputs::TurnRight, Action(sf::Keyboard::Right));
	playerInputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Space));
	playerInputs.map(PlayerInputs::Hyperspace, Action(sf::Keyboard::H, Action::Type::Pressed));
	playerInputs.map(PlayerInputs::ActivatePowerUp, Action(sf::Keyboard::P, Action::Type::Pressed));
	playerInputs.map(PlayerInputs::Click, Action(sf::Mouse::Left, Action::Type::Pressed));
}
