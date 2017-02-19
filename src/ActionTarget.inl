#include "ActionTarget.h"
#include <iostream>

template <typename T>
ActionTarget<T>::ActionTarget(const ActionMap<T> & map) : _actionMap {map} { /* Empty */ }

template <typename T>
bool ActionTarget<T>::proccessEvent(const sf::Event & event) const {
	bool res = false;
	
	for (auto & action : _eventsPoll) {
		if (action.first == event) {
			action.second(event);
			res = true;
			break;
		}
	}
	return res;
}

template <typename T>
void ActionTarget<T>::proccessEvents() const {
	for (auto & action : _eventsRealTime) {
		if (action.first.test()) {
			action.second(action.first._event);
		}
	}
}

template <typename T>
void ActionTarget<T>::bind(const T & key, const FuncType & callback) {
	Action action = _actionMap.get(key);
	if (action._type & Action::Type::RealTime) {
		_eventsRealTime.emplace_back(action, callback);
	} else
		_eventsPoll.emplace_back(action, callback);
}

template <typename T>
void ActionTarget<T>::unbind(const T & key) {
	Action action = _actionMap.get(key);
	auto remove_func = [&action] (const std::pair<Action, FuncType> & pair) -> bool
	{
		return pair.first == action;
	};
	
	if (action._type & Action::Type::RealTime)
		_eventsRealTime.remove_if(remove_func);
	else
		_eventsPoll.remove_if(remove_func);
}


