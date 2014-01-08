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

//
// naming guidelines
//
// global:
// * getters drop "get" prepend -> getWidth() becomes width()
// * setters keep "set" prepend -> setWidth() stays setWidth()
// * binary mode setters use "name" / "noName" -> smooth() / noSmooth()
// * try to associate enums with pertinent classes -> app.mouse.LEFT
//
// class binding:
// * class names start with upper case letters -> math.Point not math.point
// * getters keep "get" prepend, unless they are for simple sizes/lengths/nums
//   -> pixels.size() & msg.numArgs() instead of pixels.getSize() msg.getNumArgs()
// * setters keep "set" prepend
// * replace getter/setter pairs with a property *only* if that variable is a
//   simple class member that dosen't need to be computed/set 
//
class OFBindings {

	public:
	
		/// static function called when binding
		static void bind(ofxLua& lua) {
		
			//using namespace luabind;
			
			luabind::module(lua, "of") [
				register3d(),
				registerApp(),
				registerEvents(),
				registerGl(),
				registerGraphics(),
				registerMath(),
				registerSound(),
				registerTypes(),
				registerUtils()
			];

			/// rc-specifics
//			module(lua, "rc")
//			[
//				/// to override lua print and write functions
//				def("print", &print),
//				def("write", &write)
//			];
		}
		
		/// \section Function & Object Wrappers
		
		/// console io
//		static void print(const std::string& message) {
//			Global::instance().scriptEngine.print(message);
//		}
//		
//		static void write(const std::string& message) {
//			Global::instance().scriptEngine.write(message);
//		}
};
