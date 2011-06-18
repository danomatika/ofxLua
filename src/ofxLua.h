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

#include <string>

// make sure these 2 macros are not defined
// (I'm looking at you, Mac OS AssertMacros.h!)
#ifdef check
	#undef check
#endif
#ifdef nil
	#undef nil
#endif

#include <lua/lua.hpp>
#include <luabind/luabind.hpp>

///
/// a baseclass to receieve lua error messages,
/// useful for displaying an error message on the screen, etc
///
class ofxLuaListener {

	public :
	
		virtual void errorReceived(const std::string& msg) = 0;
};

///
///	a Lua interpreter instance
///
///	references:
///		- lua api http://pgl.yoyo.org/luai/i/_
///		- luabind docs http://www.rasterbar.com/products/luabind/docs.html
///		- luabind C++ tutorial http://www.gandogames.com/2011/01/tutorial-using-luabind-to-integrate-lua-with-cc-pt-2/
///		- call a lua func from C++ http://cc.byexamples.com/2008/07/15/calling-lua-function-from-c/
///		- bindling lua and ogre3d http://www.codeproject.com/KB/graphics/luabindLuaAndOgre3d.aspx
///
class ofxLua {
	
	public :

		ofxLua();
		virtual ~ofxLua();
        
		/// init the lua state
		///
		/// set abortOnError to true if you want the lua state to be cleared
		/// when an error ocurrs
		///
		/// set openLibs to false if you don't want to load the
		/// standard lua libs (math, io, string, etc)
		///
		/// note: calls clear if the state has already been inited
		///
		bool init(bool abortOnError=false, bool openLibs=true);
		
		/// clears current state
		///
		/// note: this also clears all bindings, make sure to call bind()
		///		  again when reiniting
		///
		void clear();
		
		/// is this state valid? (inited, not aborted, etc)
		bool isValid();
		
		/// get/set abort on error
		/// if abort on error is true, the state is closed when an error ocurrs
		bool getAbortOnError()				{return bAbortOnError;}
		void setAbortOnError(bool abort)	{bAbortOnError = abort;}
		
		/// \section Running Lua code
		
		/// run a lua string
		bool doString(const std::string& text);
		
		/// run a lua script
		bool doScript(const std::string& script);
		
		/// \section C++ Binding
		
		/// bind C++ functions and objects to lua
		/// this allows lua scripts to call C++ entities
		///
		/// see the luabind docs for syntax:
		///  http://www.rasterbar.com/products/luabind/docs.html
		///
		///
		///	create a static function in your class which contains the luabind
		///	definitions:
		///
		///	class ofWrapper {
		///
		///		public:
		///
		///			static void bind(ofxLua& lua) {
		///
		///				using namespace luabind;
		///	
		///				module(lua, "of")	// create "of" lib namespace
		///				[
		///					// bind a function
		///					def("sin", &std::sin),
		///
		///					// bind an overloaded function by specifying the 
		///					// function pointer type
		///					def("setColor", (void(*)(int)) &ofSetColor)
		///				];
		///			}
		///		};
		///
		///	see ofWrapper.h for a more detailed example
		///
		template<typename T>
		void bind() {T::bind(*this);}
		
		/// get the raw lua state, useful for custom lua api or luabind code
		///
		/// example, call "myFunction(x, y)" in the lua state:
		///
		///		int x = 20, y = 10;
		/// 	ofxLua lua;
		/// 	lua.init();
		/// 	
		///		lua_getglobal(lua, "myFunction");
		///		lua_pushinteger(lua, x);
		///		lua_pushinteger(lua, y);
		///		if(lua_pcall(lua, 2, 0, 0) != 0) {
		///			cout << "error running myFunction" << endl;
		///		}
		///
		///	note: make sure to call lua.init() before using the lua state!
		///	
		operator lua_State*() const {return L;}
		
		/// check if a function exists in the lua state
		bool funcExists(const std::string& name);
		
		/// \section Listeners
		
		/// add a listener, ignores any duplicates
		void addListener(ofxLuaListener& listener);
		
		/// remove a listener
		void removeListener(ofxLuaListener& listener);
		
		/// clear all listeners
		void clearListeners();
		
		/// \section Script Callbacks
		
		/// these are default script callbacks which call a lua function
		/// of the same name within the current lua state
		///
		/// they fail silently if the function does not exist
		///
		void scriptSetup();
		void scriptUpdate();
		void scriptDraw();
		void scriptExit();
		
		void scriptKeyPressed(int key);
		void scriptMouseMoved(int x, int y );
		void scriptMouseDragged(int x, int y, int button);
		void scriptMousePressed(int x, int y, int button);
		void scriptMouseReleased(int x, int y, int button);
        		
    private:
		
		/// send a lua error message to ofLog and any listeners
		void errorOccurred(const std::string& msg);
		
		/// called when lua state panics
		static int atPanic(lua_State *L);
	
		lua_State* L;							//< the lua state object
		std::vector<ofxLuaListener*> listeners;	//< error listeners
		bool bAbortOnError;						//< close the lua state on error?
};
