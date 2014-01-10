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

#include "ofxLuaTouchEvent.h"

namespace bindings {

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
		class_<ofxLuaTouchEvent>("Touch")
			.def(constructor<>())
			.def(constructor<const ofxLuaTouchEvent&>())
			.def("copy", (ofxLuaTouchEvent&(ofxLuaTouchEvent::*)(const ofxLuaTouchEvent&)) &ofxLuaTouchEvent::copy)
			.def_readonly("type", &ofxLuaTouchEvent::type)
			.def_readonly("id", &ofxLuaTouchEvent::id)
			.def_readonly("time", &ofxLuaTouchEvent::time)
			.def_readonly("x", &ofxLuaTouchEvent::x)
			.def_readonly("y", &ofxLuaTouchEvent::y)
			.def_readonly("numTouches", &ofxLuaTouchEvent::numTouches)
			.def_readonly("width", &ofxLuaTouchEvent::width)
			.def_readonly("height", &ofxLuaTouchEvent::height)
			.def_readonly("angle", &ofxLuaTouchEvent::angle)
			.def_readonly("minorAxis", &ofxLuaTouchEvent::minoraxis)
			.def_readonly("majorAxis", &ofxLuaTouchEvent::majoraxis)
			.def_readonly("pressure", &ofxLuaTouchEvent::pressure)
			.def_readonly("xspeed", &ofxLuaTouchEvent::xspeed)
			.def_readonly("yspeed", &ofxLuaTouchEvent::yspeed)
			.def_readonly("xaccel", &ofxLuaTouchEvent::xaccel)
			.def_readonly("yaccel", &ofxLuaTouchEvent::yaccel)
			.enum_("touchType") [
				value("DOWN", ofTouchEventArgs::down),
				value("UP", ofTouchEventArgs::up),
				value("MOVE", ofTouchEventArgs::move),
				value("DOUBLETAP", ofTouchEventArgs::doubleTap),
				value("CANCEL", ofTouchEventArgs::cancel)
			]
	;
}

} // namespace
