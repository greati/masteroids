#include "AnimatedPhysicalEntity.h"

AnimatedPhysicalEntity::AnimatedPhysicalEntity(sf::Texture & _texture, Universe & _universe, double _frameWidth, double _frameHeigth, sf::Time _frameDuration, MathVector _position)				:PhysicalEntity {_universe}, frameWidth {_frameWidth}, frameHeigth {_frameHeigth}, frameDuration {_frameDuration} {
	on = true;
	paused = false;
	looping = false;	
	currentTime = sf::Time::Zero;
	setAnimation(_texture, _frameWidth, _frameHeigth, _frameDuration);
	position = _position;
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(position.horizontal, position.vertical);
}

void AnimatedPhysicalEntity::setAnimation(sf::Texture & _texture, double _frameWidth, double _frameHeigth, sf::Time _frameDuration) {
	framesRects.clear();
	_texture.setSmooth(true);
	sprite.setTexture(_texture);
	frameWidth = _frameWidth;
	frameHeigth = _frameHeigth;
	frameDuration = _frameDuration;
	currentFrame = 0;
	int countX = _texture.getSize().x / _frameWidth;	
	int countY = _texture.getSize().y / _frameHeigth;	
	for (int i = 0; i < countY; ++i) {
		for (int j = 0; j < countX; ++j) {
			framesRects.push_back(sf::IntRect(j * _frameWidth, i * _frameHeigth, _frameWidth, _frameHeigth));	
		}
	}
	sprite.setTextureRect(framesRects[currentFrame]);
}

void AnimatedPhysicalEntity::play() {
	on = true;
}

void AnimatedPhysicalEntity::stop() {
	on = false;
}

void AnimatedPhysicalEntity::pause() {
	on = false;
	paused = true;
}

bool AnimatedPhysicalEntity::isPlaying() const {
	return on;
}

bool AnimatedPhysicalEntity::isPaused() const {
	return paused;
}

void AnimatedPhysicalEntity::setLooping(bool _looping) {
	looping = _looping;
}

bool AnimatedPhysicalEntity::isLooping() const {
	return looping;
}

int AnimatedPhysicalEntity::countFrames() const {
	return framesRects.size();
}

void AnimatedPhysicalEntity::setFrameDuration(sf::Time _frameDuration) {
	frameDuration = _frameDuration;
}

void AnimatedPhysicalEntity::update(sf::Time deltaTime) {	
	if (on and not paused) {
		currentTime += deltaTime;
		if (currentTime >= frameDuration) {
			currentFrame = (currentFrame + 1) % countFrames(); 
			sprite.setTextureRect(framesRects[currentFrame]);
			currentTime = sf::Time::Zero;
		}
		if (!looping && currentFrame == countFrames() - 1) {
			alive = false;
		}
	}
	sprite.setTextureRect(framesRects[currentFrame]);
}

void AnimatedPhysicalEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

bool AnimatedPhysicalEntity::isColliding(const PhysicalEntity & _entity) const {
	return false;
}; 		
void AnimatedPhysicalEntity::onCollide(PhysicalEntity &) {};
bool AnimatedPhysicalEntity::isClosing(const PhysicalEntity &) const {
	return false;
};
void AnimatedPhysicalEntity::onClose(PhysicalEntity &) {}


void AnimatedPhysicalEntity::setCurrentFrame(int _frame) {
	currentFrame = _frame;
}

double AnimatedPhysicalEntity::getFrameWidth() const {
	return frameWidth;
}

double AnimatedPhysicalEntity::getFrameHeigth() const {
	return frameHeigth;
}

sf::Time AnimatedPhysicalEntity::getFrameDuration() const {
	return frameDuration;
}
