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

// wrapper functions needed for overloading

//void soundPlayerLoadSound1(ofSoundPlayer* player, string filename)
//	{player->loadSound(filename);}

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
			.def("setLoop", &ofSoundPlayer::setLoop)
			.def("setMultiPlay", &ofSoundPlayer::setMultiPlay)
			.property("volume", &ofSoundPlayer::getVolume, &ofSoundPlayer::setVolume)
			.property("pan", &ofSoundPlayer::getPan, &ofSoundPlayer::setPan)
			.property("speed", &ofSoundPlayer::getSpeed, &ofSoundPlayer::setSpeed)
			.property("pos", &ofSoundPlayer::getPosition, &ofSoundPlayer::setPosition)
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
