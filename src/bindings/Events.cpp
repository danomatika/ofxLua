/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "ofEvents.h"
#include "ofxLua.h"

#include "TouchEvent.h"
	
/// dummy classes for empty class enums
struct MouseVars {};
struct KeyboardVars {};

// luabind registration
luabind::scope registerEvents() {
		
	using namespace luabind;
	
	return
		
		///////////////////////////////
		/// \section ofEvents.h
		
		/// mouse/key query
		def("getMousePressed", &ofGetMousePressed),
		def("getKeyPressed", &ofGetKeyPressed),
		def("getMouseX", &ofGetMouseX),
		def("getMouseY", &ofGetMouseY),
		def("getPreviousMouseX", &ofGetPreviousMouseX),
		def("getPreviousMouseY", &ofGetPreviousMouseY),
		def("setEscapeQuitsApp", &ofSetEscapeQuitsApp),
		def("exitApp", &exitApp),
		
		// class wrappers for enums
		class_<MouseVars>("MOUSE")
			.enum_("button") [
				value("BUTTON_1", OF_MOUSE_BUTTON_1),
				value("BUTTON_2", OF_MOUSE_BUTTON_2),
				value("BUTTON_3", OF_MOUSE_BUTTON_3),
				value("BUTTON_4", OF_MOUSE_BUTTON_4),
				value("BUTTON_5", OF_MOUSE_BUTTON_5),
				value("BUTTON_6", OF_MOUSE_BUTTON_6),
				value("BUTTON_7", OF_MOUSE_BUTTON_7),
				value("BUTTON_8", OF_MOUSE_BUTTON_8),
				value("BUTTON_LAST", OF_MOUSE_BUTTON_LAST),
				value("BUTTON_LEFT", OF_MOUSE_BUTTON_LEFT),
				value("BUTTON_LAST", OF_MOUSE_BUTTON_LAST),
				value("BUTTON_MIDDLE", OF_MOUSE_BUTTON_MIDDLE),
				value("BUTTON_RIGHT", OF_MOUSE_BUTTON_RIGHT)
			],
		class_<KeyboardVars>("KEY")
			.enum_("sym") [
				value("MODIFIER", OF_KEY_MODIFIER),
				value("RETURN", OF_KEY_RETURN),
				value("ESC", OF_KEY_ESC),
				value("TAB", OF_KEY_TAB),
				value("COMMAND", OF_KEY_COMMAND),
				
				value("BACKSPACE", OF_KEY_BACKSPACE),
				value("DEL", OF_KEY_DEL),
			
				value("F1", OF_KEY_F1),
				value("F2", OF_KEY_F2),
				value("F3", OF_KEY_F3),
				value("F4", OF_KEY_F4),
				value("F5", OF_KEY_F5),
				value("F6", OF_KEY_F6),
				value("F7", OF_KEY_F7),
				value("F8", OF_KEY_F8),
				value("F9", OF_KEY_F9),
				value("F10", OF_KEY_F10),
				value("F11", OF_KEY_F11),
				value("F12", OF_KEY_F12),
			
				value("LEFT", OF_KEY_LEFT),
				value("UP", OF_KEY_UP),
				value("RIGHT", OF_KEY_RIGHT),
				value("DOWN", OF_KEY_DOWN),
				
				value("PAGE_UP", OF_KEY_PAGE_UP),
				value("PAGE_DOWN", OF_KEY_PAGE_DOWN),
				value("HOME", OF_KEY_HOME),
				value("END", OF_KEY_END),
				value("INSERT", OF_KEY_INSERT),
				
				value("CONTROL", OF_KEY_CONTROL),
				value("ALT", OF_KEY_ALT),
				value("SHIFT", OF_KEY_SHIFT),
				value("SUPER", OF_KEY_SUPER),
				
				value("LEFT_SHIFT", OF_KEY_LEFT_SHIFT),
				value("RIGHT_SHIFT", OF_KEY_RIGHT_SHIFT),
				value("LEFT_CONTROL", OF_KEY_LEFT_CONTROL),
				value("RIGHT_CONTROL", OF_KEY_RIGHT_CONTROL),
				value("LEFT_ALT", OF_KEY_LEFT_ALT),
				value("RIGHT_ALT", OF_KEY_RIGHT_ALT),
				value("LEFT_SUPER", OF_KEY_LEFT_SUPER),
				value("RIGHT_SUPER", OF_KEY_RIGHT_SUPER),
				value("LEFT_COMMAND", OF_KEY_LEFT_COMMAND),
				value("RIGHT_COMMAND", OF_KEY_RIGHT_COMMAND)
			],
		
		// touch event wrapper
		class_<TouchEvent>("Touch")
			.def(constructor<>())
			.def_readonly("id", &TouchEvent::id)
			.def_readonly("time", &TouchEvent::time)
			.def_readonly("x", &TouchEvent::x)
			.def_readonly("y", &TouchEvent::y)
			.def_readonly("numTouches", &TouchEvent::numTouches)
			.def_readonly("width", &TouchEvent::width)
			.def_readonly("height", &TouchEvent::height)
			.def_readonly("angle", &TouchEvent::angle)
			.def_readonly("minorAxis", &TouchEvent::minoraxis)
			.def_readonly("majorAxis", &TouchEvent::majoraxis)
			.def_readonly("pressure", &TouchEvent::pressure)
			.def_readonly("xspeed", &TouchEvent::xspeed)
			.def_readonly("yspeed", &TouchEvent::yspeed)
			.def_readonly("xaccel", &TouchEvent::xaccel)
			.def_readonly("yaccel", &TouchEvent::yaccel)
			.enum_("touchType") [
				value("DOWN", ofTouchEventArgs::down),
				value("UP", ofTouchEventArgs::up),
				value("MOVE", ofTouchEventArgs::move),
				value("DOUBLETAP", ofTouchEventArgs::doubleTap),
				value("CANCEL", ofTouchEventArgs::cancel)
			]
	;
}
