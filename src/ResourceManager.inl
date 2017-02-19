#include <iostream>

template <typename Resource, typename Identifier>
template <typename ... Args>
void ResourceManager<Resource, Identifier>::load(const Identifier & id, Args && ... args) {
	std::unique_ptr<Resource> ptr { new Resource };		
	if (not ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("File not loaded!");
	_map.emplace(id, std::move(ptr));
} 

template <typename Resource, typename Identifier>
Resource & ResourceManager<Resource, Identifier>::get(const Identifier & id) const {
	return *_map.at(id);	
} 

template <typename Identifier>
template <typename ... Args>
void ResourceManager<sf::Music, Identifier>::load(const Identifier & id, Args && ... args) {
	std::unique_ptr<sf::Music> ptr { new sf::Music };		
	if (not ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("File not loaded!");
	_map.emplace(id, std::move(ptr));
} 

template <typename Identifier>
sf::Music & ResourceManager<sf::Music, Identifier>::get(const Identifier & id) const {
	return *_map.at(id);	
} 
