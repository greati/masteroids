#include "PhysicalEntity.h"
#include "Universe.h"
#include "Configuration.h"

PhysicalEntity::PhysicalEntity(Universe & _universe) : GeneralEntity(), sf::Drawable(), universe (_universe) { 
	alive = true;
	collidable = true;
	exploded = false;
	angleAdjustment = 0;
	exploding = sf::seconds(0.5);
};

void PhysicalEntity::setPosition(MathVector pos) {
	position = pos;
}

MathVector PhysicalEntity::getPosition() const {
	//std::cout<<"Problem here!!! getPosition"<<std::endl;
	//std::cout<<"wwProblem here!!! getPosition"<<std::endl;
	//std::cout<<"Horizontal: "<<position.horizontal<<std::endl;
	//std::cout<<"Vertical: "<<position.vertical<<std::endl;
	return position;
}

MathVector PhysicalEntity::getVelocity() const {
	return velocity;
}

double PhysicalEntity::getRotationRad() const {
	return (sprite.getRotation() - angleAdjustment) / 180 * M_PI;
}

double PhysicalEntity::getRotationDegree() const {
	return sprite.getRotation() - angleAdjustment;
}

double PhysicalEntity::getWidth() const {
	return sprite.getTextureRect().width * sprite.getScale().x; 
}

double PhysicalEntity::getHeigth() const {
	return sprite.getTextureRect().height * sprite.getScale().y; 
}

bool PhysicalEntity::isAlive() const {
	return alive;
}

void PhysicalEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

bool PhysicalEntity::isExploded() const {
	return exploded;
}

void PhysicalEntity::killEntity(){
	alive = false;
}

int PhysicalEntity::getDamagePoints() const {
	return damagePoints;
}

bool PhysicalEntity::isInsideWindow(){
	if(position.horizontal * 2 - getWidth()  < 0 || position.horizontal * 2 + getWidth()> Configuration::WINDOW_WIDTH || 
	position.vertical * 2 - getHeigth() || position.vertical * 2 + getHeigth() > Configuration::WINDOW_HEIGHT){
		return false;
	}else{		
		return true;
	}

}

int PhysicalEntity::getMaxLifePoints() const{
	return maxLifePoints;
}

int PhysicalEntity::getCurrentLifePoints() const{
	return currentLifePoints;
}

void PhysicalEntity::decreaseLifePoints(int _delta) {
	currentLifePoints = std::max(0, currentLifePoints - _delta);
}
