/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 * This project uses the following libraries:
 *
 * Lua, Copyright (c) 1994–2011 Lua.org, PUC-Rio using the MIT License.
 * See the file "COPYRIGHT" in src/lua.
 * See http://www.lua.org/docs.html for documentation
 *
 * Luabind, Copyright (c) 2003 Daniel Wallin and Arvid Norberg using the
 * MIT License. See the file "LICENSE" in src/luabind.
 * See http://www.rasterbar.com/products/luabind/docs.html for documentation
 *
 */
#pragma once

#include "ofxLuaBase.h"

class ofxLuaState;

///
///	a Lua coroutine (aka lua "thread")
///
/// coroutines inherit the global state from a parent lua state
///
/// A coroutine is allows code to be stoppd while running (the wait functions)
/// and started again where it left off
///
/// - Lua Coroutines Tutorial: http://lua-users.org/wiki/CoroutinesTutorial
///
/// Coroutines in Lua are not operating system threads or processes. Coroutines
/// are blocks of Lua code which are created within Lua, and have their own flow
/// of control like threads. Only one coroutine ever runs at a time, and it runs
/// until it activates another coroutine, or yields (returns to the coroutine
/// that invoked it).
///
/// - Lua Threads: https://medek.wordpress.com/2009/01/22/lua-threads-and-stuff/
///
class ofxLuaCoroutine : public ofxLuaBase {
	
	public:

		ofxLuaCoroutine();
		virtual ~ofxLuaCoroutine();
        
		/// init the lua state
		///
		/// set abortOnError to true if you want the lua state to be cleared
		/// when an error ocurrs
		///
		/// note: calls clear if the state has already been inited
		///
		bool init(const ofxLuaState& state, bool abortOnError=false);

		bool isThread() {return true;}
		
		/// returns true if coroutine yielded,
		/// returns false if coroutine finished (with or without error)
		bool resume();
		
		///
		int yield();
};
