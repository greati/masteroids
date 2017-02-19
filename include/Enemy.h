#ifndef _ENEMY_
#define _ENEMY_

#include "PhysicalEntity.h"

class Enemy : public PhysicalEntity {

	public:
		Enemy(const Enemy &) = delete;
		Enemy & operator=(const Enemy &) = delete;

		Enemy(Universe &);
	
		virtual void onDestroy();
		virtual int getPoints() const;
		virtual void setPoints(int);
	private:
		void draw(sf::RenderTarget & target, sf::RenderStates states) const; 
		int points;
	protected:
		sf::RectangleShape lifeBar;

};

#endif
