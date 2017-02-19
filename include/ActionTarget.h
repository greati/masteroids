#ifndef _ATARGET_
#define _ATARGET_

#include <functional>
#include <utility>
#include <list>
#include "ActionMap.h"

/*! \brief Every entity that reacts to Actions (events) extends this class.
 *  \details Contains methods for binding and unbinding functionalities
 *  to Actions. Thanks to this approach, it becomes easy to change the way
 *  an entity answers to events. 
 *  It keeps an ActionMap for relating Actions to keys.
 *  \authors Vitor Greati, Vinicius Campos
 *  \date 16/11/2015
 *  \version 1.0
 */
template <typename T = int>
class ActionTarget {

	public:
		
		ActionTarget(const ActionTarget<T> &) = delete;
		ActionTarget<T> & operator=(const ActionTarget<T> &) = delete;

		using FuncType = std::function<void (const sf::Event &) >;	
		
		ActionTarget(const ActionMap<T> & map);

		/*! For non-real-time events  */
		bool proccessEvent(const sf::Event & event) const;
		
		/*! For real-time events  */
		void proccessEvents() const;

		void bind(const T & key, const FuncType & callback);
		void unbind(const T & key);
		
	private:
		std::list<std::pair<Action, FuncType>> _eventsRealTime;
		std::list<std::pair<Action, FuncType>> _eventsPoll;

		const ActionMap<T> & _actionMap;

};

#include "../src/ActionTarget.inl"

#endif
