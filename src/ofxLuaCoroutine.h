/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
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

class ofxLua;

///
///	a Lua coroutine (aka lua "thread")
///
/// coroutines inherit the global state from a parent lua state
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
		bool init(const ofxLua& luaState, bool abortOnError=false);
		
		/// clears current state
		///
		/// note: this also clears all bindings, make sure to call bind()
		///		  again when reiniting
		///
		void clear();
		
		/// is this state valid? (inited, not aborted, etc)
//		bool isValid();

		bool isThread() {return true;}
		
		//void resume();
		//void yield();
		
		/// get/set abort on error
		/// if abort on error is true, the state is closed when an error ocurrs
//		bool getAbortOnError()				{return bAbortOnError;}
//		void setAbortOnError(bool abort)	{bAbortOnError = abort;}
		
		/// \section Running Lua code
		
		/// run a lua string
//		bool doString(const std::string& text);
//		
//		/// run a lua script
//		bool doScript(const std::string& script);
		
		/// \section Script Callbacks
		
		/// these are default script callbacks which call a lua function
		/// of the same name within the current lua state
		///
		/// they fail silently if the function does not exist
		///
//		void scriptSetup();
//		void scriptUpdate();
//		void scriptDraw();
//		void scriptExit();
//		
//		void scriptKeyPressed(int key);
//		void scriptMouseMoved(int x, int y );
//		void scriptMouseDragged(int x, int y, int button);
//		void scriptMousePressed(int x, int y, int button);
//		void scriptMouseReleased(int x, int y, int button);
        		
    private:

//		/// send a lua error message to ofLog and any listeners
		void errorOccurred(const std::string& msg);
//		
//		/// called when lua state panics
//		static int atPanic(lua_State *L);
//	
//		lua_State* L;							//< the lua state object
//		std::vector<ofxLuaListener*> listeners;	//< error listeners
//		bool bAbortOnError;						//< close the lua state on error?
//		std::vector<std::string> tables;		//< the currently open table names
};
