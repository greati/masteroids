#include "ActionMap.h"

template<typename T>
ActionMap<T>::ActionMap(const ActionMap<T> & map) : _map {map._map} { /* Empty */}

template <typename T>
void ActionMap<T>::map(const T & key, const Action & action) {
	_map.emplace(key, action);
}

template <typename T>
const Action & ActionMap<T>::get(const T & key) const {
	return _map.at(key);
}
