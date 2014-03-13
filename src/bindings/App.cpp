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
    
//dummy empty class for target enum
struct Target {};
    
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
		def("setVerticalSync", &ofSetVerticalSync),
    

        class_<Target>("TARGET")
        .enum_("enum") [
                    
                    value("OSX", OF_TARGET_OSX),
                    value("WINGCC", OF_TARGET_WINGCC),
                    value("WINVS", OF_TARGET_WINVS),
                    value("IOS", OF_TARGET_IOS),
                    value("ANDROID", OF_TARGET_ANDROID),
                    value("LINUX", OF_TARGET_LINUX),
                    value("LINUX64", OF_TARGET_LINUX64),
                    value("LINUXARMV6L", OF_TARGET_LINUXARMV6L),
                    value("LINUXARMV7L", OF_TARGET_LINUXARMV7L),
                    value("RASPBERRYPI", 1000),

                    
#ifdef TARGET_WIN32
                    value("CURRENT", OF_TARGET_WINGCC)
#endif
#ifdef TARGET_OF_IOS
                    value("CURRENT", TARGET_OF_IOS)
#endif
#ifdef TARGET_OSX
                    value("CURRENT", OF_TARGET_OSX)
#endif
#ifdef TARGET_ANDROID
                    value("CURRENT", OF_TARGET_ANDROID)
#endif
#ifdef TARGET_LINUX
    #ifdef TARGET_LINUX_ARM
        #ifdef TARGET_RASPBERRY_PI
                    value("CURRENT", 1000)
        #else
                    value("CURRENT", OF_TARGET_LINUXARMV6L)
        #endif
    #else
                    value("CURRENT", OF_TARGET_LINUX)
    #endif
#endif


                    
                    
                    ]

	;
}

} // namespace
