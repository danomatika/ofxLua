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
#include "ofxLua.h"

#include "ofUtils.h"

using namespace std;

// local pointer for static functions
ofxLua* luaPtr;

//--------------------------------------------------------------------
ofxLua::ofxLua()
{
	L = NULL;
	bAbortOnError = false;

	luaPtr = this;
}

//--------------------------------------------------------------------
ofxLua::~ofxLua() {
	clear();
}

//--------------------------------------------------------------------
bool ofxLua::init(bool abortOnError, bool openLibs) {
	
	clear();
	
	L = luaL_newstate();
	if(L == NULL) {
		ofLogError("ofxLua") << "Error initializing lua";
		return false;
	}
	
	// open libs
	if(openLibs) {
		luaL_openlibs(L);
	}
	luabind::open(L);
	
	// set the panic function
	lua_atpanic(L, &atPanic);
	
	bAbortOnError = abortOnError;
	ofLogVerbose("ofxLua") << "Initialized";
	
	return true;
}
	

void ofxLua::clear() {
	if(L != NULL) {
		lua_close(L);
		L = NULL;
		ofLogVerbose("ofxLua") << "Cleared";
	}
}

bool ofxLua::isValid() {
	return L != NULL ? true : false;
}

//--------------------------------------------------------------------
bool ofxLua::doString(const std::string& text) {
	
	if(L == NULL) {
		ofLogError("ofxLua") << "Cannot do string, lua state not inited!";
		return false;
	}

	ofLogVerbose("ofxLua") << "Doing string: \"" << text.substr(0,40) << "\"";
	
	// load the string
	int ret = luaL_loadstring(L, text.c_str());
	if(ret != 0) {
		switch(ret) {
			case LUA_ERRSYNTAX:
			{
				string msg = "Syntax error in string \""
					 +text.substr(0,40)+"\": "
					 +(string) lua_tostring(L, -1);
				errorOccurred(msg);
				break;
			}
			case LUA_ERRMEM:
			{
				string msg = "String \""+text.substr(0,40)+"\" memory error",
				errorOccurred(msg);
				break;
			}
		}
				
		return false;
	}
	
	// run the string
	ret = lua_pcall(L, 0, LUA_MULTRET, 0);
	if(ret != 0) {
		string msg = "Runtime error in string \""+text.substr(0,40)+"\": "
					 +(string) lua_tostring(L, -1);
		errorOccurred(msg);
		return false;
	}
	
	return true;
}

//--------------------------------------------------------------------
bool ofxLua::doScript(const std::string& script) {

	if(L == NULL) {
		ofLogError("ofxLua") << "Cannot do script, lua state not inited!";
		return false;
	}
	
	string fullpath = ofFilePath::getAbsolutePath(ofToDataPath(script));
	string file = ofFilePath::getFileName(fullpath);
	string folder = ofFilePath::getEnclosingDirectory(fullpath);
	
	// trim the trailing slash Poco::Path always adds ... blarg
	if(folder.size() > 0 && folder.at(folder.size()-1) == '/') {
		folder.erase(folder.end()-1);
	}
	
	ofLogVerbose("ofxLua") << "Doing script: \"" << file << "\" path: \"" << folder << "\"";

	// load the script
	int ret = luaL_loadfile(L, fullpath.c_str());
	if(ret != 0) {
		switch(ret) {
			case LUA_ERRFILE:
			{
				string msg = (string)"Script \""+file+"\" not found or unreadable";
				errorOccurred(msg);
				break;
			}
			case LUA_ERRSYNTAX:
			{
				string msg = "Syntax error: "+(string) lua_tostring(L, -1);
				errorOccurred(msg);
				break;
			}
			case LUA_ERRMEM:
			{
				string msg = "Script \""+file+"\" memory error";
				errorOccurred(msg);
				break;
			}
		}
		return false;
	}
	
	// run the script
	ret = lua_pcall(L, 0, LUA_MULTRET, 0);
	if(ret != 0) {			
		string msg = "Runtime error: "+(string) lua_tostring(L, -1);
		errorOccurred(msg);
		return false;
	}
	
	return true;
}

//--------------------------------------------------------------------		
bool ofxLua::funcExists(const std::string& name) {
	
	if(L == NULL) {
		ofLogError("ofxLua") << "Cannot check func, lua state not inited!";
		return false;
	}
		
	using namespace luabind;

	object g = globals(L);
	object func = g[name];

	if(func) {
		if(type(func) == LUA_TFUNCTION)
			return true;
	}
	return false;
}

//--------------------------------------------------------------------		
void ofxLua::addListener(ofxLuaListener& listener) {
	// exists?
	for(int i = 0; i < listeners.size(); ++i) {
		if(listeners[i] == &listener) {
			ofLogWarning("ofxLua") << "addListener(): ignoring duplicate listener";
			return;
		}
	}
	listeners.push_back(&listener);
}
		
//--------------------------------------------------------------------		
void ofxLua::removeListener(ofxLuaListener& listener) {
	for(int i = 0; i < listeners.size(); ++i) {
		if(listeners[i] == &listener) {
			listeners.erase(listeners.begin()+i);
			return;
		}
	}
	ofLogWarning("ofxLua") << "removeListener(): listener not found";
}
		
//--------------------------------------------------------------------		
void ofxLua::clearListeners() {
	listeners.clear();
}

//--------------------------------------------------------------------		
void ofxLua::scriptSetup() {
	if(L == NULL || !funcExists("setup"))
		return;
	lua_getglobal(L, "setup");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running setup(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptUpdate() {
	if(L == NULL || !funcExists("update"))
		return;
	lua_getglobal(L, "update");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running update(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptDraw() {
	if(L == NULL || !funcExists("draw"))
		return;
	lua_getglobal(L, "draw");
	if(lua_pcall(L, 0, 0, 0) != 0) {			
		string msg = "Error running draw(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptExit() {
	if(L == NULL || !funcExists("exit"))
		return;
	lua_getglobal(L, "exit");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running exit(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

//--------------------------------------------------------------------
void ofxLua::scriptKeyPressed(int key) {
	if(L == NULL || !funcExists("keyPressed"))
		return;
	lua_getglobal(L, "keyPressed");
	lua_pushinteger(L, key);
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running keyPressed(): "
					 + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseMoved(int x, int y ) {
	if(L == NULL || !funcExists("mouseMoved"))
		return;
	lua_getglobal(L, "mouseMoved");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	if(lua_pcall(L, 2, 0, 0) != 0) {
		string msg = "Error running mouseMoved(): "
					 + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseDragged(int x, int y, int button) {
	if(L == NULL || !funcExists("mouseDragged"))
		return;
	lua_getglobal(L, "mouseDragged");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {
		string msg = "Error running mouseDragged(): "
					 + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMousePressed(int x, int y, int button) {
	if(L == NULL || !funcExists("mousePressed"))
		return;
	lua_getglobal(L, "mousePressed");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {			
		string msg = "Error running mousePressed(): "
					 + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseReleased(int x, int y, int button) {
	if(L == NULL || !funcExists("mouseReleased"))
		return;
	lua_getglobal(L, "mouseReleased");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {
		string msg = "Error running mouseReleased(): "
					 + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

//--------------------------------------------------------------------
void ofxLua::errorOccurred(const std::string& msg) {
	
	// print
	for(int i = 0; i < listeners.size(); ++i) {
		listeners[i]->errorReceived(msg);
	}
	ofLogError("ofxLua") << msg;
	
	// close the state?
	if(bAbortOnError) {
		ofLogError("ofxLua") << "Closing state";
		clear();
	}
}

//--------------------------------------------------------------------
int ofxLua::atPanic(lua_State *L) {
	ofLogError("ofxLua") << "Lua panic ocurred! : " << lua_tostring(L, -1);
	ofLogError("ofxLua") << "Closing state";
	luaPtr->clear();
	return 0;
}
