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
#include "ofVideoGrabber.h"
#include "ofVideoPlayer.h"
#include "ofxLua.h"

// dummy classes for empty class enums

struct LoopType {};

// luabind registration
luabind::scope registerVideo() {
		
	using namespace luabind;
	
	return
	
		class_<LoopType>("LOOP")
			.enum_("enum") [
				value("NONE", OF_LOOP_NONE),
				value("PALINDROME", OF_LOOP_PALINDROME),
				value("NORMAL", OF_LOOP_NORMAL)
			],
	
		///////////////////////////////
		/// \section ofVideoGrabber.h
		
		class_<ofVideoGrabber>("VideoGrabber")
			.def(constructor<>())
			
			.def("listDevices", &ofVideoGrabber::listDevices)
			.def("isFrameNew", &ofVideoGrabber::isFrameNew)
			.def("update", &ofVideoGrabber::update)
			.def("close", &ofVideoGrabber::close)
			.def("initGrabber", (bool(ofVideoGrabber::*)(int,int)) &ofVideoGrabber::initGrabber)
			.def("initGrabber", (bool(ofVideoGrabber::*)(int,int,bool)) &ofVideoGrabber::initGrabber)
			
			.def("setPixelFormat", &ofVideoGrabber::setPixelFormat)
			.def("getPixelFormat", &ofVideoGrabber::getPixelFormat)
			
			.def("videoSettings", &ofVideoGrabber::videoSettings)
			// ignore getPixels() for now due to pointer
			.def("getPixelsRef", &ofVideoGrabber::getPixelsRef)
			.def("getTextureReference", &ofVideoGrabber::getTextureReference)
			.def("setVerbose", &ofVideoGrabber::setVerbose)
			.def("setDeviceID", &ofVideoGrabber::setDeviceID)
			.def("setDesiredFrameRate", &ofVideoGrabber::setDesiredFrameRate)
			.def("setUseTexture", &ofVideoGrabber::setUseTexture)
			.def("draw", (void(ofVideoGrabber::*)(float,float,float,float)) &ofVideoGrabber::draw)
			.def("draw", (void(ofVideoGrabber::*)(float,float)) &ofVideoGrabber::draw)
			
			.def("setAnchorPercent", &ofVideoGrabber::setAnchorPercent)
			.def("setAnchorPoint", &ofVideoGrabber::setAnchorPoint)
			.def("resetAnchor", &ofVideoGrabber::resetAnchor)
			
			.def("getWidth",  &ofVideoGrabber::getWidth)
			.def("getHeight", &ofVideoGrabber::getHeight)
			
			.def("isInitialized", &ofVideoGrabber::isInitialized)
			
			.def_readonly("width", &ofVideoGrabber::width)
			.def_readonly("height", &ofVideoGrabber::height)
		,
		
		///////////////////////////////
		/// \section ofVideoPlayer.h
		
		class_<ofVideoPlayer>("VideoPlayer")
			.def(constructor<>())
		
			.def("loadMovie", &ofVideoPlayer::loadMovie)
			.def("getMoviePath", &ofVideoPlayer::getMoviePath)
			
			.def("setPixelFormat", &ofVideoPlayer::setPixelFormat)
			.def("getPixelFormat", &ofVideoPlayer::getPixelFormat)
			.property("pixelFormat", &ofVideoPlayer::getPixelFormat, &ofVideoPlayer::setPixelFormat)
			
			.def("closeMovie", &ofVideoPlayer::closeMovie)
			.def("close", &ofVideoPlayer::close)
			
			.def("update", &ofVideoPlayer::update)
			.def("play", &ofVideoPlayer::play)
			.def("stop", &ofVideoPlayer::stop)
		
			.def("isFrameNew", &ofVideoPlayer::isFrameNew)
			// ignore getPixels() for now due to pointer
			.def("getPixelsRef", &ofVideoPlayer::getPixelsRef)
			.def("getPosition", &ofVideoPlayer::getPosition)
			.def("getSpeed", &ofVideoPlayer::getSpeed)
			.def("getDuration", &ofVideoPlayer::getDuration)
			.def("getIsMovieDone", &ofVideoPlayer::getIsMovieDone)
			
			.def("setPosition", &ofVideoPlayer::setPosition)
			.def("setVolume", &ofVideoPlayer::setVolume)
			.def("setLoopState", &ofVideoPlayer::setLoopState)
			.def("getLoopState", &ofVideoPlayer::getLoopState)
			.def("setSpeed", &ofVideoPlayer::setSpeed)
			.def("setFrame", &ofVideoPlayer::setFrame)
			
			.def("setUseTexture", &ofVideoPlayer::setUseTexture)
			.def("getTextureReference", &ofVideoPlayer::getTextureReference)
			.def("draw", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::draw)
			.def("draw", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::draw)
			
			.def("setAnchorPercent", &ofVideoPlayer::setAnchorPercent)
			.def("setAnchorPoint", &ofVideoPlayer::setAnchorPoint)
			.def("resetAnchor", &ofVideoPlayer::resetAnchor)
			
			.def("setPaused", &ofVideoPlayer::setPaused)
			
			.def("getCurrentFrame", &ofVideoPlayer::getCurrentFrame)
			.def("getTotalNumFrames", &ofVideoPlayer::getTotalNumFrames)
			
			.def("firstFrame", &ofVideoPlayer::firstFrame)
			.def("nextFrame", &ofVideoPlayer::nextFrame)
			.def("previousFrame", &ofVideoPlayer::previousFrame)
			
			.def("getWidth",  &ofVideoPlayer::getWidth)
			.def("getHeight", &ofVideoPlayer::getHeight)
			
			.def("isPaused", &ofVideoPlayer::isPaused)
			.def("isLoaded", &ofVideoPlayer::isLoaded)
			.def("isPlaying", &ofVideoPlayer::isPlaying)
			
			.def_readonly("width", &ofVideoPlayer::width)
			.def_readonly("height", &ofVideoPlayer::height)
			
			.property("position", &ofVideoPlayer::getPosition, &ofVideoPlayer::setPosition)
			.property("speed", &ofVideoPlayer::getSpeed, &ofVideoPlayer::setSpeed)
			.property("loopState", &ofVideoPlayer::getLoopState, &ofVideoPlayer::setLoopState)
			.property("frame", &ofVideoPlayer::getCurrentFrame, &ofVideoPlayer::setFrame)
	;
}
