#ifndef _RMANAGER_
#define _RMANAGER_

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory> // unique_ptr
#include <unordered_map>

template <typename Resource, typename Identifier>
class ResourceManager {
	public:
		ResourceManager(const ResourceManager &) = delete;
		ResourceManager& operator=(const ResourceManager &) = delete;
		
		ResourceManager() = default;
		
		template <typename ... Args>
		void load(const Identifier & id, Args && ... args);

		Resource& get(const Identifier & id) const;

	private:
		std::unordered_map<Identifier, std::unique_ptr<Resource>> _map;
			
};

template <typename Identifier>
class ResourceManager<sf::Music, Identifier> {
	public:
		ResourceManager(const ResourceManager &) = delete;
		ResourceManager& operator=(const ResourceManager &) = delete;
		
		ResourceManager() = default;
		
		template <typename ... Args>
		void load(const Identifier & id, Args && ... args);

		sf::Music & get(const Identifier & id) const;

	private:
		std::unordered_map<Identifier, std::unique_ptr<sf::Music>> _map;
			
};

#include "../src/ResourceManager.inl"
#endif
