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

#include "ofMain.h"
#include "ofxLua.h"

luabind::scope register3d();
luabind::scope registerApp();
luabind::scope registerEvents();
luabind::scope registerGl();
luabind::scope registerGraphics();
luabind::scope registerMath();
luabind::scope registerSound();
luabind::scope registerTypes();
luabind::scope registerUtils();
luabind::scope registerVideo();

// naming guidelines
//
// global:
// * enums replace first two "_' with '.':
//     OF_IMAGE_COLOR -> of.IMAGE.COLOR & OF_KEY_LEFT_SHIFT -> of.KEY.LEFT_SHIFT
//
//     except for OF_WINDOW & OF_FULLSCREEN which are
//     of.WINDOW_MODE.WINDOW & of.WINDOW_MODE.FULLSCREEN
//
// class binding:
// * class names start with upper case letters -> math.Point not math.point
// * variables exposed via getters/setters are also accessible via properties:
//   myImage:getWidth() -> myImage.width
//
//   this is *only* if that variable is a
//   simple class member that dosen't need to be computed/set 
//
class ofxLuaBindings {

	public:
	
		// static function called when binding
		static void bind(ofxLua& lua) {
			
			// since there are alot of functions and classes to wrap,
			// the bindings are implemented in individual cpp files
			luabind::module(lua, "of") [
				register3d(),
				registerApp(),
				registerEvents(),
				registerGl(),
				registerGraphics(),
				registerMath(),
				registerSound(),
				registerTypes(),
				registerUtils(),
				registerVideo()
			];
		}
};
