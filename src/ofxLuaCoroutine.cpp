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
#include "ofxLuaCoroutine.h"

#include "ofUtils.h"

#include "ofxLua.h"

using namespace std;

// local pointer for static functions
//ofxLua* luaPtr;

//--------------------------------------------------------------------
ofxLuaCoroutine::ofxLuaCoroutine() : ofxLuaBase() {
//	L = NULL;
//	bAbortOnError = false;

//	luaPtr = this;
}

//--------------------------------------------------------------------
ofxLuaCoroutine::~ofxLuaCoroutine() {
	clear();
}

//--------------------------------------------------------------------
bool ofxLuaCoroutine::init(const ofxLua& luaState, bool abortOnError) {
	
	clear();
	
	L = lua_newthread(luaState);
	if(L == NULL) {
		ofLogError("ofxLua") << "Error initializing lua thread";
		return false;
	}
	
	ofLogVerbose("ofxLua") << "Initialized thread";
	
	return true;
}
	

//void ofxLuaCoroutine::clear() {
//	if(L != NULL) {
//		lua_close(L);
//		L = NULL;
//		ofLogVerbose("ofxLua") << "Cleared thread";
//	}
//}



//--------------------------------------------------------------------		
//bool ofxLuaCoroutine::funcExists(const std::string& name) {
//	
//	if(L == NULL) {
//		ofLogError("ofxLua") << "Cannot check func, lua state not inited!";
//		return false;
//	}
//		
//	using namespace luabind;
//
//	object g = globals(L);
//	object func = g[name];
//
//	if(func) {
//		if(type(func) == LUA_TFUNCTION)
//			return true;
//	}
//	return false;
//}

//--------------------------------------------------------------------		
//void ofxLuaCoroutine::addListener(ofxLuaListener& listener) {
//	// exists?
//	for(int i = 0; i < listeners.size(); ++i) {
//		if(listeners[i] == &listener) {
//			ofLogWarning("ofxLua") << "addListener(): ignoring duplicate listener";
//			return;
//		}
//	}
//	listeners.push_back(&listener);
//}
//		
////--------------------------------------------------------------------		
//void ofxLuaCoroutine::removeListener(ofxLuaListener& listener) {
//	for(int i = 0; i < listeners.size(); ++i) {
//		if(listeners[i] == &listener) {
//			listeners.erase(listeners.begin()+i);
//			return;
//		}
//	}
//	ofLogWarning("ofxLua") << "removeListener(): listener not found";
//}
//		
////--------------------------------------------------------------------		
//void ofxLuaCoroutine::clearListeners() {
//	listeners.clear();
//}

//--------------------------------------------------------------------	
//bool ofxLuaCoroutine::variableExists(const std::string& name) {
//	return exists(name, LUA_TNIL);
//}
//
//bool ofxLuaCoroutine::numberExists(const std::string& name) {
//	return exists(name, LUA_TNUMBER);
//}
//
//bool ofxLuaCoroutine::boolExists(const std::string& name) {
//	return exists(name, LUA_TBOOLEAN);
//}
//
//bool ofxLuaCoroutine::intExists(const std::string& name) {
//	return exists(name, LUA_TINTEGER);
//}
//
//bool ofxLuaCoroutine::uintExists(const std::string& name) {
//	return exists(name, LUA_TUINTEGER);
//}
//
//bool ofxLuaCoroutine::floatExists(const std::string& name) {
//	return exists(name, LUA_TFLOAT);
//}
//
//bool ofxLuaCoroutine::stringExists(const std::string& name) {
//	return exists(name, LUA_TSTRING);
//}
//
//bool ofxLuaCoroutine::functionExists(const std::string& name) {
//	return exists(name, LUA_TFUNCTION);
//}
//
//bool ofxLuaCoroutine::tableExists(const std::string& name) {
//	return exists(name, LUA_TTABLE);
//}
//		
////--------------------------------------------------------------------	
//bool ofxLuaCoroutine::pushTable(const std::string& tableName, bool isGlobal) {
//	
//	// global table
//	if(tables.empty() || isGlobal) {
//		lua_getglobal(L, tableName.c_str());
//		if(!lua_istable(L, LUA_STACK_TOP)) {
//			ofLogWarning("ofxLua") << "Couldn't push global table \""
//				<< tableName << "\"";
//			return false;
//		}
//		tables.push_back(tableName);
//	}
//	
//	// table in another table
//	else {
//		lua_pushstring(L, tableName.c_str());
//		lua_gettable(L, LUA_STACK_TOP - 1);
//		if(!lua_istable(L, LUA_STACK_TOP)) {
//			ofLogWarning("ofxLua") << "Couldn't push table \""
//				<< tableName << "\"";
//			return false;
//		}
//		tables.push_back(tableName);
//	}
//	
//	return true;
//}
//
//void ofxLuaCoroutine::popTable() {
//	if(tables.empty()) {
//		ofLogWarning("ofxLua") << "No tables to pop, did you push?";
//		return;
//	}
//	tables.pop_back();
//	lua_pop(L, 1);
//}
//
//
//void ofxLuaCoroutine::popAllTables() {
//	while(!tables.empty()) {
//		popTable();
//	}
//}
//
//unsigned int ofxLuaCoroutine::tableSize() {
//	
//	if(tables.empty()) {
//		ofLogWarning("ofxLua") << "Couldn't get table size, no open tables";
//		return 0;
//	}
//	
//	// count manually
//	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
//	if(luabind::type(o) != LUA_TTABLE) {
//		ofLogWarning("ofxLua") << "Couldn't get table size, stack var is not a table";
//		return 0;
//	}
//	
//	unsigned int size = 0;
//	for(luabind::iterator iter(o), end; iter != end; ++iter) {
//		size++;
//	}
//	return size;
//}
//
//unsigned int ofxLuaCoroutine::tableSize(const std::string& tableName) {
//	unsigned int size = 0;
//	pushTable(tableName);
//	size = tableSize();
//	popTable();
//	return size;
//}
//
//void ofxLuaCoroutine::printTable() {
//	if(tables.empty()) {
//		ofLogWarning("ofxLua") << "No table to print, did you push?";
//		return;
//	}
//	
//	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
//	if(luabind::type(o) != LUA_TTABLE) {
//		ofLogWarning("ofxLua") << "Couldn't print table, stack var is not a table";
//	}
//	
//	ofLogNotice("ofxLua") << "table: " << tables.back();
//	printTable(o, 1);
//}
//		
////--------------------------------------------------------------------	
//bool ofxLuaCoroutine::readBool(const std::string& name, bool defaultValue) {
//	return read<bool>(name, defaultValue);
//}
//
//int ofxLuaCoroutine::readInt(const std::string& name, int defaultValue) {
//	return read<int>(name, defaultValue);
//}
//
//unsigned int ofxLuaCoroutine::readUInt(const std::string& name, unsigned int defaultValue) {
//	return read<unsigned int>(name, defaultValue);
//}
//
//float ofxLuaCoroutine::readFloat(const std::string& name, float defaultValue) {
//	return read<float>(name, defaultValue);
//}
//
//std::string ofxLuaCoroutine::readString(const std::string& name, const std::string& defaultValue) {
//	return read<string>(name, defaultValue);
//}
//
//void ofxLuaCoroutine::readBoolVector(const std::string& tableName, std::vector<bool>& v) {
//	readVector<bool>(tableName, v);
//}
//
//void ofxLuaCoroutine::readIntVector(const std::string& tableName, std::vector<int>& v) {
//	readVector<int>(tableName, v);
//}
//
//void ofxLuaCoroutine::readUIntVector(const std::string& tableName, std::vector<unsigned int>& v) {
//	readVector<unsigned int>(tableName, v);
//}
//
//void ofxLuaCoroutine::readFloatVector(const std::string& tableName, std::vector<float>& v) {
//	readVector<float>(tableName, v);
//}
//
//void ofxLuaCoroutine::readStringVector(const std::string& tableName, std::vector<std::string>& v) {
//	readVector<string>(tableName, v);
//}
//
////--------------------------------------------------------------------
//void ofxLuaCoroutine::printGlobals() {
//	luabind::object o(luabind::from_stack(L, LUA_GLOBALSINDEX));
//	for(luabind::iterator iter(o), end; iter != end; ++iter) {
//		if(iter.key() != "_G" && iter.key() != "package") {
//			
//			// only print valid values
//			switch(luabind::type(*iter)) {
//				case LUA_TBOOLEAN:
//				case LUA_TNUMBER:
//				case LUA_TSTRING:
//					ofLogNotice("ofxLua") << "\t"
//						<< (string) lua_typename(L, luabind::type(*iter)) << ": "
//						<< iter.key() << " " << (*iter);
//					break;
//				default:
//					ofLogNotice("ofxLua") << "\t"
//						<< (string) lua_typename(L, luabind::type(*iter)) << ": "
//						<< iter.key();
//					break;
//			}
//				
//			if(luabind::type(*iter) == LUA_TTABLE) {
//					printTable(luabind::object(*iter), 2);
//			}
//		}
//	}
//}
//
////--------------------------------------------------------------------
//void ofxLuaCoroutine::scriptSetup() {
//	if(L == NULL || !functionExists("setup"))
//		return;
//	lua_getglobal(L, "setup");
//	if(lua_pcall(L, 0, 0, 0) != 0) {
//		string msg = "Error running setup(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptUpdate() {
//	if(L == NULL || !functionExists("update"))
//		return;
//	lua_getglobal(L, "update");
//	if(lua_pcall(L, 0, 0, 0) != 0) {
//		string msg = "Error running update(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptDraw() {
//	if(L == NULL || !functionExists("draw"))
//		return;
//	lua_getglobal(L, "draw");
//	if(lua_pcall(L, 0, 0, 0) != 0) {			
//		string msg = "Error running draw(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptExit() {
//	if(L == NULL || !functionExists("exit"))
//		return;
//	lua_getglobal(L, "exit");
//	if(lua_pcall(L, 0, 0, 0) != 0) {
//		string msg = "Error running exit(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
////--------------------------------------------------------------------
//void ofxLuaCoroutine::scriptKeyPressed(int key) {
//	if(L == NULL || !functionExists("keyPressed"))
//		return;
//	lua_getglobal(L, "keyPressed");
//	lua_pushinteger(L, key);
//	if(lua_pcall(L, 1, 0, 0) != 0) {
//		string msg = "Error running keyPressed(): "
//					 + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptMouseMoved(int x, int y ) {
//	if(L == NULL || !functionExists("mouseMoved"))
//		return;
//	lua_getglobal(L, "mouseMoved");
//	lua_pushinteger(L, x);
//	lua_pushinteger(L, y);
//	if(lua_pcall(L, 2, 0, 0) != 0) {
//		string msg = "Error running mouseMoved(): "
//					 + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptMouseDragged(int x, int y, int button) {
//	if(L == NULL || !functionExists("mouseDragged"))
//		return;
//	lua_getglobal(L, "mouseDragged");
//	lua_pushinteger(L, x);
//	lua_pushinteger(L, y);
//	lua_pushinteger(L, button);
//	if(lua_pcall(L, 3, 0, 0) != 0) {
//		string msg = "Error running mouseDragged(): "
//					 + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptMousePressed(int x, int y, int button) {
//	if(L == NULL || !functionExists("mousePressed"))
//		return;
//	lua_getglobal(L, "mousePressed");
//	lua_pushinteger(L, x);
//	lua_pushinteger(L, y);
//	lua_pushinteger(L, button);
//	if(lua_pcall(L, 3, 0, 0) != 0) {			
//		string msg = "Error running mousePressed(): "
//					 + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaCoroutine::scriptMouseReleased(int x, int y, int button) {
//	if(L == NULL || !functionExists("mouseReleased"))
//		return;
//	lua_getglobal(L, "mouseReleased");
//	lua_pushinteger(L, x);
//	lua_pushinteger(L, y);
//	lua_pushinteger(L, button);
//	if(lua_pcall(L, 3, 0, 0) != 0) {
//		string msg = "Error running mouseReleased(): "
//					 + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
