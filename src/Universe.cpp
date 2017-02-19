#include "Universe.h"
#include <map>

Universe::Universe() {};

void Universe::draw(sf::RenderTarget & target, 
				  sf::RenderStates states) const {
	for (auto e : entitiesList)
		target.draw(*(e.second), states);
	/*for (auto e : bulletList)
		target.draw(*e, states);
	for (auto e : playersList)
		target.draw(*e, states);
	for (auto e : asteroidList)
		target.draw(*e, states);*/
}

void Universe::addEntity (PhysicalEntity::EntityType entType, PhysicalEntity * newEntity) {
	entitiesList_temp.emplace(entType, newEntity);
}

std::multimap<PhysicalEntity::EntityType, PhysicalEntity*> & Universe::getEntities() {
	return entitiesList;
}

std::list<Player*> & Universe::getPlayers() {
	return playersList;
}

std::list<Bullet*> & Universe::getBullets() {
	return bulletList;
}

std::list<Asteroid*> & Universe::getAsteroids() {
	return asteroidList;
}

std::list<Alien*> & Universe::getAliens() {
	return alienList;
}

void Universe::proccessEvents() {
	std::pair<std::multimap<PhysicalEntity::EntityType, PhysicalEntity*>::iterator, std::multimap<PhysicalEntity::EntityType, PhysicalEntity*>::iterator> range; 
	range = entitiesList.equal_range(PhysicalEntity::EntityType::Player);
	for (auto ip (range.first); ip != range.second; ip++) {
		((Player*)((*ip)).second)->proccessEvents();
	}
}

void Universe::update(sf::Time deltaTime) {
	if(entitiesList_temp.size() > 0)
		entitiesList.insert(entitiesList_temp.begin(), entitiesList_temp.end());
	
	entitiesList_temp.clear();
	
	for (auto p : entitiesList)
		(p.second)->update(deltaTime);
	
	const auto end (entitiesList.end());
	for (auto i = entitiesList.begin(); i != end; ++i) {
		PhysicalEntity & ie = *((*i).second);
		auto j ( i );
		j++;
		while (j != end) {	
			PhysicalEntity & je = *((*j).second);
			//std::cout << ie.isAlive() << std::endl;
			if (ie.isAlive() && je.isAlive() && (ie.isColliding(je) || je.isColliding(ie))) {
				ie.onCollide(je);
				je.onCollide(ie);
			}
			if(ie.isAlive() && je.isAlive() && (ie.isClosing(je) || je.isClosing(ie))){
				ie.onClose(je);
				je.onClose(ie);
			}
			if(ie.isInsideWindow()){
				ie.killEntity();
			}
			if(je.isInsideWindow()){
				je.killEntity();
			}
			j++;
		}
	}

	for (auto i = entitiesList.begin(); i != entitiesList.end();) {
		if (not (((*i).second)->isAlive())) {
			delete (*i).second;
			i = entitiesList.erase(i);
		} else i++;
	}
}

void Universe::clear() {
	for (auto i = entitiesList.begin(); i != entitiesList.end();) {
		delete (*i).second;
		i = entitiesList.erase(i);
	}
}

bool Universe::existPlayer(){
	for (auto i = entitiesList.begin(); i != entitiesList.end();) {
		if((*i).first == PhysicalEntity::EntityType::Player){
			return true;
		}else{
			++i;
		}
	}
	return false;
}

