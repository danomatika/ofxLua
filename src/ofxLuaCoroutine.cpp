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
#include "ofxLuaCoroutine.h"

#include "ofUtils.h"

#include "ofxLua.h"

using namespace std;

//--------------------------------------------------------------------
ofxLuaCoroutine::ofxLuaCoroutine() : ofxLuaBase() {}

//--------------------------------------------------------------------
ofxLuaCoroutine::~ofxLuaCoroutine() {
	clear();
}

//--------------------------------------------------------------------
bool ofxLuaCoroutine::init(const ofxLuaState& state, bool abortOnError) {
	
	clear();
	
	L = lua_newthread(state);
	if(L == NULL) {
		ofLogError("ofxLua") << "Error initializing lua thread";
		return false;
	}
	
	ofLogVerbose("ofxLua") << "Initialized thread";
	
	return true;
}

//--------------------------------------------------------------------	
// http://torch5.sourceforge.net/manual/LuaManual-3-7-66.html
bool ofxLuaCoroutine::resume() {

	if(L == NULL) {
		ofLogError("ofxLua") << "Cannot resume, lua coroutine not inited!";
		return false;
	}

	int ret = lua_resume(L, 0);
	if(ret == LUA_YIELD) {
		return true;
	}
	else if(ret != 0) {
		string msg = "Error resuming coroutine: "+(string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
	
	return false;
}

//--------------------------------------------------------------------
int ofxLuaCoroutine::yield() {
	if(L == NULL) {
		ofLogError("ofxLua") << "Cannot yield, lua coroutine not inited!";
		return false;
	}
	return lua_yield(L, 1);
}
