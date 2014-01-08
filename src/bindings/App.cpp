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

// dummy classes for enums

struct Orientation {};
struct WindowMode {};

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
		class_<Orientation>("ORIENTATION")
			.enum_("type") [
				value("DEFAULT", OF_ORIENTATION_DEFAULT),
				value("180", OF_ORIENTATION_180),
				value("90_LEFT", OF_ORIENTATION_90_LEFT),
				value("90_RIGHT", OF_ORIENTATION_90_RIGHT),
				value("UNKNOWN", OF_ORIENTATION_UNKNOWN)
			],
		
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
		class_<WindowMode>("WINDOW_MODE")
			.enum_("mode") [
				value("WINDOW", OF_WINDOW),
				value("FULLSCREEN", OF_FULLSCREEN),
				value("GAME_MODE", OF_GAME_MODE)
			],
		
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
