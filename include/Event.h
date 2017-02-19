#ifndef _EVENT_
#define _EVENT_

namespace V2Game {

	/*! \brief Generic event for V2Game Engine.
         *  \detail Provides an interface for working with events
	 *   no matter the low level engine that is being used.
	 *  \date 12/09/2015
         *  \version 0.0
         */
	template <typename EngineEvent>
	class Event {
		public:
			EngineEvent event;
			
			struct SizeEvent {
				unsigned int width;
				unsigned int heigth;
			};

			enum class EventType {
				CLOSED,
				RESIZED,
				LOST_FOCUS,
				GAINED_FOCUS,
				TEXT_ENTENRED,
				KEY_PRESSED,
				KEY_RELEASED,
				MOUSE_WHEEL_MOVED,
				MOUSE_BUTTON_PRESSED,
				MOUSE_BUTTON_RELEASED,
				MOUSE_MOVED,
				MOUSE_ENTERED,
				MOUSE_LEFT,
				JOYSTICK_BUTTON_PRESSED,
				JOYSTICK_BUTTON_RELEASED,
				JOYSTICK_MOVED,
				JOYSTICK_CONNECTED,
				JOYSTICK_DISCONNECTED
			};

			virtual EventType type() const;
			virtual SizeEvent size() const;
			virtual KeyEvent key() const;
			virtual TextEvent text() const;
			virtual MouseMoveEvent mouseMove() const;
			virtual MouseButtonEvent mouseButton() const;
			virtual MouseWheelEvent mouseWheel() const;
			virtual JoystickMoveEvent joystickMove() const;
			virtual JoystickButtonEvent joystickButton() const;
			virtual JoystickConnectEvent joystickConnect() const;
	};

};
#endif
