#ifndef _ANIMATED_
#define _ANIMATED_

#include "PhysicalEntity.h"

class AnimatedPhysicalEntity : public PhysicalEntity {
	public:
		AnimatedPhysicalEntity(const AnimatedPhysicalEntity &) = delete;
		AnimatedPhysicalEntity & operator=(const AnimatedPhysicalEntity &) = delete;
		AnimatedPhysicalEntity(sf::Texture & _texture, Universe &, double, double, sf::Time _frameDuration, MathVector _position = {0.0, 0.0});
		void play();
		void stop();
		void pause();
		bool isPlaying() const;
		bool isPaused() const;
		void setLooping(bool);
		bool isLooping() const;
		void setAnimation(sf::Texture & _texture, double _frameWidth, double _frameHeigth, sf::Time _frameDuration);
		void setFrameDuration(sf::Time frameDuration);
		void setCurrentFrame(int);
		int countFrames() const;
		void update(sf::Time deltaTime);
		bool isColliding(const PhysicalEntity &) const;
		void onCollide(PhysicalEntity &);
		bool isClosing(const PhysicalEntity &) const;
		void onClose(PhysicalEntity &);
		double getFrameWidth() const;
		double getFrameHeigth() const;
		sf::Time getFrameDuration() const;

	private:
		std::vector<sf::IntRect> framesRects;
		bool on;
		bool paused;
		bool looping;
		double frameWidth;
		double frameHeigth;
		sf::Time currentTime;
		sf::Time frameDuration;

		void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	protected:
		int currentFrame;
};

#endif
