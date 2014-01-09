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
#include "ofSoundPlayer.h"
#include "ofSoundStream.h"
#include "ofxLua.h"

namespace bindings {

// luabind registration
luabind::scope registerSound() {

	using namespace luabind;

	return
		
		///////////////////////////////
		/// \section ofSoundPlayer.h
		
		// don't include the global funcs aka FIX THIS SHIT!!!!!!
		
		class_<ofSoundPlayer>("SoundPlayer")
			.def(constructor<>())
			.def("loadSound", (bool(ofSoundPlayer::*)(string)) &ofSoundPlayer::loadSound)
			.def("loadSound", &ofSoundPlayer::loadSound)
			.def("unloadSound", &ofSoundPlayer::unloadSound)
			.def("isLoaded", &ofSoundPlayer::isLoaded)
			
			.def("play", &ofSoundPlayer::play)
			.def("stop", &ofSoundPlayer::stop)
			.def("setPaused", &ofSoundPlayer::setPaused)
			.def("getIsPlaying", &ofSoundPlayer::getIsPlaying)
			.property("playing", &ofSoundPlayer::getIsPlaying)
			
			.def("setLoop", &ofSoundPlayer::setLoop)
			.def("setMultiPlay", &ofSoundPlayer::setMultiPlay)
			
			.def("getVolume", &ofSoundPlayer::getVolume)
			.def("setVolume", &ofSoundPlayer::setVolume)
			.property("volume", &ofSoundPlayer::getVolume, &ofSoundPlayer::setVolume)
			
			.def("getPan", &ofSoundPlayer::getPan)
			.def("setPan", &ofSoundPlayer::setPan)
			.property("pan", &ofSoundPlayer::getPan, &ofSoundPlayer::setPan)
			
			.def("getSpeed", &ofSoundPlayer::getSpeed)
			.def("setSpeed", &ofSoundPlayer::setSpeed)
			.property("speed", &ofSoundPlayer::getSpeed, &ofSoundPlayer::setSpeed)
			
			.def("getPosition", &ofSoundPlayer::getPosition)
			.def("setPosition", &ofSoundPlayer::setPosition)
			.property("pos", &ofSoundPlayer::getPosition, &ofSoundPlayer::setPosition)
			
			.def("getPositionMS", &ofSoundPlayer::getPositionMS)
			.def("setPositionMS", &ofSoundPlayer::setPositionMS)
			.property("posMS", &ofSoundPlayer::getPositionMS, &ofSoundPlayer::setPositionMS),
			
		///////////////////////////////
		/// \section ofSoundStream.h
		
		// ignore the ofSoundStreamSetup's that take ofBaseAppPtr
		def("soundStreamSetup", (void(*)(int,int,int,int,int)) &ofSoundStreamSetup),
		def("soundStreamStop", &ofSoundStreamStop),
		def("soundStreamStart", &ofSoundStreamStart),
		def("soundStreamClose", &ofSoundStreamListDevices)
		
		// don't wrap ofSoundStream class for now
	;
}

} // namespace
