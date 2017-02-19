#include "Enemy.h"
#include "PhysicalEntity.h"

Enemy::Enemy(Universe & _universe) : PhysicalEntity {_universe} {
	lifeBar.setSize(sf::Vector2f(30, 3));
	lifeBar.setFillColor(sf::Color::Green);
}

void Enemy::onDestroy() {
	alive = false;
	// raise score
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
	target.draw(lifeBar, states);
}

int Enemy::getPoints() const {
	return points;
}

void Enemy::setPoints(int _points) {
	points = _points;
}
