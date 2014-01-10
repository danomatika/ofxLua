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
#pragma once

#include "ofEvents.h"

/// wrapper around ofTouchEventArgs to add copy constructor/operator
/// you should wrap this object with luabind in order to receive it in your
/// lua touch event callback functions
class ofxLuaTouchEvent : public ofTouchEventArgs {

	public:
		
		ofxLuaTouchEvent() {
			type = ofTouchEventArgs::down;
			this->id = -1;
			x = 0;
			y = 0;
			numTouches = 0;
			width = 0;
			height = 0;
			angle = 0;
			minoraxis = 0;
			majoraxis = 0;
			pressure = 0;
			xspeed = 0;
			yspeed = 0;
			xaccel = 0;
			yaccel = 0;
		}
		
		ofxLuaTouchEvent(const ofxLuaTouchEvent& other) {
			copy(other);
		}
		
		ofxLuaTouchEvent& operator=(const ofxLuaTouchEvent& other) {
			return copy(other);
		}
		
		/// for operator= and copy constructor
		ofxLuaTouchEvent& copy(const ofxLuaTouchEvent& other) {
			type = other.type;
			this->id = other.id;
			x = other.x;
			y = other.y;
			numTouches = other.numTouches;
			width = other.width;
			height = other.height;
			angle = other.angle;
			minoraxis = other.minoraxis;
			majoraxis = other.majoraxis;
			pressure = other.pressure;
			xspeed = other.xspeed;
			yspeed = other.yspeed;
			xaccel = other.xaccel;
			yaccel = other.yaccel;
			return *this;
		}
		
		/// copy in ofTouchEventArgs data
		ofxLuaTouchEvent(const ofTouchEventArgs& other) {
			copy(other);
		}
		
		ofxLuaTouchEvent& operator=(const ofTouchEventArgs& other) {
			return copy(other);
		}
		
		ofxLuaTouchEvent& copy(const ofTouchEventArgs& other) {
			type = other.type;
			this->id = other.id;
			x = other.x;
			y = other.y;
			numTouches = other.numTouches;
			width = other.width;
			height = other.height;
			angle = other.angle;
			minoraxis = other.minoraxis;
			majoraxis = other.majoraxis;
			pressure = other.pressure;
			xspeed = other.xspeed;
			yspeed = other.yspeed;
			xaccel = other.xaccel;
			yaccel = other.yaccel;
			return *this;
		}
};
