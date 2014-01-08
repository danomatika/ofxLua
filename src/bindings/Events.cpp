/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/robotcowboy for documentation
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
				value("LEFT", 0),
				value("MIDDLE", 1),
				value("RIGHT", 2)
			],
		class_<KeyboardVars>("KEY")
			.enum_("sym") [
				value("MODIFIER", OF_KEY_MODIFIER),
				value("RETURN", OF_KEY_RETURN),
				value("ESC", OF_KEY_ESC),
				value("CONTROL", OF_KEY_CONTROL),
				value("ALT", OF_KEY_ALT),
				value("SHIFT", OF_KEY_SHIFT),
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
				value("RIGHT", OF_KEY_RIGHT),
				value("UP", OF_KEY_UP),
				value("DOWN", OF_KEY_DOWN),
				
				value("PAGE_UP", OF_KEY_PAGE_UP),
				value("PAGE_DOWN", OF_KEY_PAGE_DOWN),
				value("HOME", OF_KEY_HOME),
				value("END", OF_KEY_END),
				value("INSERT", OF_KEY_INSERT)
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
