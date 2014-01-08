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

#include "ofxOsc.h"
#include "../Global.h"

namespace lua {

class Osc {

	public:
	
		static void bind(ofxLua& lua) {
		
			using namespace luabind;
			
			module(lua, "osc")
			[				
				///////////////////////////////
				/// \section Osc
				
				def("send", &send),
				def("sendFloat", &sendFloat),
				def("sendInt", &sendInt),
				def("sendString", &sendString),
				def("sendMessage", &sendMessage),
				def("sendBundle", &sendBundle),
					
				///////////////////////////////
				/// \section Message
				
				class_<ofxOscMessage>("Message")
					.def(constructor<>())
					.def("clear", &ofxOscMessage::clear)
					.def("setAddress", &ofxOscMessage::setAddress)
					.def("getAddress", &ofxOscMessage::getAddress)
					.def("getRemoteIp", &ofxOscMessage::getRemoteIp)
					.def("getRemotePort", &ofxOscMessage::getRemotePort)
					.def("setRemote", &ofxOscMessage::setRemoteEndpoint)
					.def("getType", &ofxOscMessage::getArgType)
					.def("getTypeName", &ofxOscMessage::getArgTypeName)
					.def("getInt", &ofxOscMessage::getArgAsInt32)
					.def("getFloat", &ofxOscMessage::getArgAsFloat)
					.def("getString", &ofxOscMessage::getArgAsString)
					.def("addInt", &ofxOscMessage::addIntArg)
					.def("addFloat", &ofxOscMessage::addFloatArg)
					.def("addString", &ofxOscMessage::addStringArg)
					.def_readonly("numArgs", &ofxOscMessage::getNumArgs)
					.enum_("argType")
					[
						value("NONE", OFXOSC_TYPE_NONE),
						value("INT", OFXOSC_TYPE_INT32),
						value("FLOAT", OFXOSC_TYPE_FLOAT),
						value("STRING", OFXOSC_TYPE_STRING),
						value("BLOB", OFXOSC_TYPE_BLOB),
						value("BUNDLE", OFXOSC_TYPE_BUNDLE),
						value("OUTOFBOUNDS", OFXOSC_TYPE_INDEXOUTOFBOUNDS)
					],
					
				///////////////////////////////
				/// \section Bundle
				
				class_<ofxOscBundle>("Bundle")
					.def(constructor<>())
					.def("clear", &ofxOscBundle::clear)
					.def("addMessage", &ofxOscBundle::addMessage)
					.def("addBundle", &ofxOscBundle::addBundle)
					.def("getMessage", &ofxOscBundle::getMessageAt)
					.def("getBundle", &ofxOscBundle::getBundleAt)
					.def_readonly("numMessages", &ofxOscBundle::getMessageCount)
					.def_readonly("numBundles", &ofxOscBundle::getBundleCount)
			];
		}
		
		/// \section Function & Object Wrappers
		
		/// osc
		static void send(string address) {
			ofxOscMessage msg;
			msg.setAddress(address);
			Global::instance().osc.sendOscFromScript(msg);
		}
		
		static void sendFloat(string address, float f) {
			ofxOscMessage msg;
			msg.setAddress(address);
			msg.addFloatArg(f);
			Global::instance().osc.sendOscFromScript(msg);
		}
		
		static void sendInt(string address, int i) {
			ofxOscMessage msg;
			msg.setAddress(address);
			msg.addIntArg(i);
			Global::instance().osc.sendOscFromScript(msg);
		}
		
		static void sendString(string address, string s) {
			ofxOscMessage msg;
			msg.setAddress(address);
			msg.addStringArg(s);
			Global::instance().osc.sendOscFromScript(msg);
		}
		
		static void sendMessage(ofxOscMessage& msg) {
			Global::instance().osc.sendOscFromScript(msg);
		}
		
		static void sendBundle(ofxOscBundle& bundle) {
			Global::instance().osc.sendOscFromScript(bundle);
		}
};

} // namespace
