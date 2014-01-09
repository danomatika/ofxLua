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

// hide everything in a namespace
namespace bindings {

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

	void addUtilsConstants(lua_State *L);
}

// naming guidelines
//
// global:
// * enums replace first two "_' with '.':
//     OF_IMAGE_COLOR -> of.IMAGE.COLOR & OF_KEY_LEFT_SHIFT -> of.KEY.LEFT_SHIFT,
//     except for OF_WINDOW, OF_FULLSCREEN, * OF_GAME_MODE which are
//     of.WINDOWMODE.WINDOW & of.WINDOWMODE.FULLSCREEN, of.WINDOWMODE.GAME_MODE
// * ofGetFill() returns a bool, there is no ofFillFlag type
//
// class binding:
// * class names start with upper case letters -> math.Point not math.point
// * most variables exposed via getters/setters are also accessible via properties:
//   myImage:getWidth() -> myImage.width, video:setSpeed(0.5) -> video.speed = 0.5
//
//   this is *only* if that variable is a simple class member that doesn't need to
//   be computed/set, ie isAllocated(), getWidth(), etc
//
class ofxLuaBindings {

	public:
	
		// static function called when binding
		static void bind(ofxLua& lua) {
			
			using namespace bindings;
			
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
			
			// add some special constants
			addUtilsConstants(lua);
		}
};
