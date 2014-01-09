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
