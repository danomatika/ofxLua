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
#include "ofAppRunner.h"
#include "ofxLua.h"

namespace bindings {

// wrapper functions needed for overloading

void exit0() {ofExit();}

// luabind registration
luabind::scope registerApp() {
		
	using namespace luabind;
	
	return
		
		///////////////////////////////
		/// \section ofAppRunner.h
		
		// leave out ofSetupOpenGL & ofRunApp for now,
		// shouldn't need the ofBaseAppPtr since it's easy to make globals in Lua
		
		def("exit", &exit0),
		def("exit", &ofExit),
		
		// time
		def("getFrameRate", &ofGetFrameRate),
		def("getTargetFrameRate", &ofGetTargetFrameRate),
		def("getFrameNum", &ofGetFrameNum),
		def("setFrameRate", &ofSetFrameRate),
		def("sleepMillis", &ofSleepMillis),
		def("getLastFrameTime", &ofGetLastFrameTime), // seconds
		def("setOrientation", &ofSetOrientation),
		def("getOrientation", &ofGetOrientation),
		
		/// cursor
		def("hideCursor", &ofHideCursor),
		def("showCursor", &ofShowCursor),
		
		/// window / screen
		def("getWindowPositionX", &ofGetWindowPositionX),
		def("getWindowPositionY", &ofGetWindowPositionY),
		def("getScreenWidth", &ofGetScreenWidth),
		def("getScreenHeight", &ofGetScreenHeight),
		def("getWindowMode", &ofGetWindowMode),
		def("getWidth", &ofGetWidth),
		def("getHeight", &ofGetHeight),
		def("getWindowWidth", &ofGetWindowWidth),
		def("getWindowHeight", &ofGetWindowHeight),
		def("doesHWOrientation", &ofDoesHWOrientation),
		def("getWindowSize", &ofGetWindowSize),
		def("getWindowRect", &ofGetWindowRect),
		// no ofGetWindowPtr for now
		
		def("setWindowPosition", &ofSetWindowPosition),
		def("setWindowShape", &ofSetWindowShape),
		def("setWindowTitle", &ofSetWindowTitle),
		def("enableSetupScreen", &ofEnableSetupScreen),
		def("disableSetupScreen", &ofDisableSetupScreen),
		def("setFullscreen", &ofSetFullscreen),
		def("toggleFullscreen", &ofToggleFullscreen),
		
		/// sync
		def("setVerticalSync", &ofSetVerticalSync)
	;
}

} // namespace
