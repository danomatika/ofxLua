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
#include "ofUtils.h"
#include "ofxLua.h"

// wrapper functions needed for overloading

double getPI() {return PI;}
double getTWO_PI() {return TWO_PI;}
double getFOUR_PI() {return FOUR_PI;}
double getHALF_PI() {return HALF_PI;}

// luabind registration
luabind::scope registerUtils() {
		
	using namespace luabind;
	
	return
	
		// TODO: wrap ofFileUtils.h, ofLog.h, ofSystemUtils.h, ofThread.h,
		//       ofURLFileLoader.h, ofXml.h
	
		///////////////////////////////
		/// \section ofConstants.h
		
		def("PI", &getPI),
		def("TWO_PI", &getTWO_PI),
		def("FOUR_PI", &getFOUR_PI),
		def("HALF_PI", &getHALF_PI),
	
		///////////////////////////////
		/// \section ofUtils.h
		
		def("resetElapsedTimeCounter", &ofResetElapsedTimeCounter),
		def("getElapsedTimef", &ofGetElapsedTimef),
		def("getElapsedTimeMillis", &ofGetElapsedTimeMillis),
		def("getElapsedTimeMicros", &ofGetElapsedTimeMicros),
		def("getFrameNum", &ofGetFrameNum),
		
		def("getSeconds", &ofGetSeconds),
		def("getMinutes", &ofGetMinutes),
		def("getHours", &ofGetHours),
		
		def("getUnixTime", &ofGetUnixTime),
		def("getSystemTime", &ofGetSystemTime),
		def("getSystemTimeMicros", &ofGetSystemTimeMicros),
		
		def("getTimestampString", (string(*)(void)) &ofGetTimestampString),
		def("getTimestampString", (string(*)(string)) &ofGetTimestampString),
		
		def("getYear", &ofGetYear),
		def("getMonth", &ofGetMonth),
		def("getDay", &ofGetDay),
		def("getWeekday", &ofGetWeekday),
		
		def("launchBrowser", (void(*)(string)) &ofLaunchBrowser),
		def("launchBrowser", (void(*)(string,bool)) &ofLaunchBrowser),
		
		def("enableDataPath", &ofEnableDataPath),
		def("disableDataPath", &ofDisableDataPath),
		def("toDataPath", (void(*)(string)) &ofToDataPath),
		def("toDataPath", (void(*)(string,bool)) &ofToDataPath),
		
		// ignoring templated vector algorithm wrappers
		
		def("setWorkingDirectoryToDefault", &ofSetWorkingDirectoryToDefault),
		def("setDataPathRoot", &ofSetDataPathRoot),
		
		// ignoring type conversion functions for now
		
		def("getVersionInfo", &ofGetVersionInfo),
		def("getVersionMajor", &ofGetVersionMajor),
		def("getVersionMinor", &ofGetVersionMinor),
		def("getVersionPatch", &ofGetVersionPatch),
		
		def("saveScreen", &ofSaveScreen),
		def("saveFrame", (void(*)(void)) &ofSaveFrame),
		def("saveFrame", (void(*)(bool)) &ofSaveFrame),
		def("saveViewport", &ofSaveViewport),
		
		// ignoring string functions, use lua string lib
		
		// no VAArgs in lua
		
		def("system", &ofSystem)
		
		// ignoring getTargetPlatform for now
	;
}
