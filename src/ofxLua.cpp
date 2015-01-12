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
 * Lua, Copyright (c) 1994â2011 Lua.org, PUC-Rio using the MIT License.
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
#include "ofxLuaBindings.h"

// declare the wrapped modules
extern "C" {
	int luaopen_of(lua_State* L);
}

// local pointer for static functions
ofxLua* luaPtr;

//------------------------------------------------------------------------------
ofxLua::ofxLua() {
	L = NULL;
	bAbortOnError = false;
	luaPtr = this;
}

//------------------------------------------------------------------------------
ofxLua::~ofxLua() {
	clear();
}

//------------------------------------------------------------------------------
bool ofxLua::init(bool abortOnError, bool openLibs, bool ofBindings) {
	
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
	if(ofBindings) {
		luaopen_of(L);
	}
	
	// clear stack since opening libs leaves tables on the stack
	lua_settop(L, 0);
	
	// set the panic function
	lua_atpanic(L, &atPanic);
	
	bAbortOnError = abortOnError;
	ofLogVerbose("ofxLua") << "Initialized state";
	
	return true;
}
	

void ofxLua::clear() {
	if(L != NULL) {
		lua_close(L);
		L = NULL;
		ofLogVerbose("ofxLua") << "Cleared state";
	}
	tables.clear();
	errorMessage = "";
}

bool ofxLua::isValid() {
	return (L != NULL);
}

//------------------------------------------------------------------------------
bool ofxLua::doString(const string& text) {
	
	if(!isValid()) {
		ofLogError("ofxLua") << "Cannot do string, lua state not inited!";
		return false;
	}

	if(text.length() < 40) {
		ofLogVerbose("ofxLua") << "Doing string: \"" << text << "\"";
	}
	else {
		ofLogVerbose("ofxLua") << "Doing string: \"" << text.substr(0,40) << "..." << "\"";
	}
	
	// load the string
	int ret = luaL_loadstring(L, text.c_str());
	if(ret != 0) {
		switch(ret) {
			case LUA_ERRSYNTAX: {
				string msg = (string) lua_tostring(L, LUA_STACK_TOP);
				errorOccurred(msg);
				break;
			}
			case LUA_ERRMEM: {
				string msg = "Memory error",
				errorOccurred(msg);
				break;
			}
		}
				
		return false;
	}
	
	// run the string
	ret = lua_pcall(L, 0, LUA_MULTRET, 0);
	if(ret != 0) {
		string msg = (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
		return false;
	}
	
	return true;
}

//------------------------------------------------------------------------------
bool ofxLua::doScript(const string& script) {

	if(!isValid()) {
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
			case LUA_ERRFILE: {
				string msg = (string)"Script \""+file+"\" not found or unreadable";
				errorOccurred(msg);
				break;
			}
			case LUA_ERRSYNTAX: {
				string msg = (string) lua_tostring(L, LUA_STACK_TOP);
				errorOccurred(msg);
				break;
			}
			case LUA_ERRMEM: {
				string msg = "Memory error for script \""+file+"\"";
				errorOccurred(msg);
				break;
			}
		}
		return false;
	}
	
	// run the script
	if(lua_pcall(L, 0, LUA_MULTRET, 0) != 0) {
		string msg = (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
		return false;
	}
	
	return true;
}

//------------------------------------------------------------------------------		
void ofxLua::addListener(ofxLuaListener* listener) {
	ofAddListener(errorEvent, listener, &ofxLuaListener::errorReceived);
}
		
//------------------------------------------------------------------------------		
void ofxLua::removeListener(ofxLuaListener* listener) {
	ofRemoveListener(errorEvent, listener, &ofxLuaListener::errorReceived);
}

//------------------------------------------------------------------------------
bool ofxLua::isBool(const string& name) {
	return exists(name, LUA_TBOOLEAN);
}

bool ofxLua::isBool(const unsigned int index) {
	return exists(index, LUA_TBOOLEAN);
}

bool ofxLua::isFloat(const string& name) {
	return exists(name, LUA_TNUMBER);
}

bool ofxLua::isFloat(const unsigned int index) {
	return exists(index, LUA_TNUMBER);
}

bool ofxLua::isString(const string& name) {
	return exists(name, LUA_TSTRING);
}

bool ofxLua::isString(const unsigned int index) {
	return exists(index, LUA_TSTRING);
}

bool ofxLua::isFunction(const string& name) {
	return exists(name, LUA_TFUNCTION);
}

bool ofxLua::isFunction(const unsigned int index) {
	return exists(index, LUA_TFUNCTION);
}

bool ofxLua::isTable(const string& name) {
	return exists(name, LUA_TTABLE);
}

bool ofxLua::isTable(const unsigned int index) {
	return exists(index, LUA_TTABLE);
}

bool ofxLua::isNil(const string& name) {
	return exists(name, LUA_TNIL);
}

bool ofxLua::isNil(const unsigned int index) {
	return exists(index, LUA_TNIL);
}
		
//------------------------------------------------------------------------------
bool ofxLua::pushTable(const string& tableName) {
	if(!isValid()) {
		return;
	}
	
	// global table
	if(tables.empty()) {
		lua_getglobal(L, tableName.c_str());
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't push global table \"" << tableName << "\"";
			return false;
		}
		tables.push_back(tableName);
	}
	
	// table in another table
	else {
		lua_pushstring(L, tableName.c_str());
		lua_gettable(L, LUA_STACK_TOP);
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't push table \"" << tableName << "\"";
			return false;
		}
		tables.push_back(tableName);
	}
	
	return true;
}

bool ofxLua::pushTable(const unsigned int& tableIndex) {
	if(!isValid()) {
		return;
	}

	// global table
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Cannot push global table by index" << tableIndex;
		return false;
	}
	
	lua_pushinteger(L, tableIndex);
	lua_gettable(L, LUA_STACK_TOP);
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't push table \"" << tableIndex << "\"";
		return false;
	}
	tables.push_back((string) lua_tostring(L, LUA_STACK_TOP));
	
	return true;
}

void ofxLua::popTable() {
	if(!isValid()) {
		return;
	}
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No tables to pop, did you push?";
		return;
	}
	tables.pop_back();
	lua_pop(L, 1);
}


void ofxLua::popAllTables() {
	while(!tables.empty()) {
		popTable();
	}
	lua_settop(L, 0); // clear stack just in case
}

unsigned int ofxLua::tableSize() {
	if(!isValid()) {
		return 0;
	}
	
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't get table size, no open tables";
		return 0;
	}
	
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't get table size, stack var is not a table";
		return 0;
	}
	
	return lua_objlen(L, LUA_STACK_TOP);
}

unsigned int ofxLua::tableSize(const string& tableName) {
	unsigned int size = 0;
	pushTable(tableName);
	size = tableSize();
	popTable();
	return size;
}

void ofxLua::printTable() {
	if(!isValid()) {
		return;
	}

	if(tables.empty()) {
		ofLogNotice("ofxLua") << "global table";
		printTable(LUA_GLOBALSINDEX, 1);
		return;
	}
	
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't print table, stack var is not a table";
		return;
	}
	
	ofLogNotice("ofxLua") <<  "table " << tables.back();
	printTable(LUA_STACK_TOP, 1);
}

void ofxLua::printTable(const string& tableName) {
	if(!pushTable(tableName)) {
		return;
	}
	printTable();
	popTable();
}

void ofxLua::clearTable() {
	if(!isValid()) {
		return false;
	}
	
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No table to clear, did you push?";
		return;
	}
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't clear table, stack var is not a table";
	}
	
	// clears all elements by setting them to nil, this way the original table
	// pointer is preserved
	lua_pushvalue(L, LUA_STACK_TOP); // stack: -1 => table
	lua_pushnil(L); // stack: -1 => table; -2 => nil
	
	while(lua_next(L, -2)) {
		// stack: -3 => table; -2 => key; -1 => value
		lua_pop(L, 1); // stack: -2 => table; -1 => key
		
		lua_pushvalue(L, -1);
		lua_pushnil(L);
		lua_settable(L, -4); // stack: -2 => table; -1 => key
	}
	
	// stack: -1 => table
	lua_pop(L, 1); // stack:
}

void ofxLua::clearTable(const string& tableName) {
	if(!pushTable(tableName)) {
		return;
	}
	clearTable();
	popTable();
}
		
//------------------------------------------------------------------------------
bool ofxLua::getBool(const string& name, bool defaultValue) {
	return read<bool>(name, LUA_TBOOLEAN, defaultValue);
}

bool ofxLua::getBool(const unsigned int index, bool defaultValue) {
	return read<bool>(index, LUA_TBOOLEAN, defaultValue);
}

float ofxLua::getFloat(const string& name, float defaultValue) {
	return read<float>(name, LUA_TNUMBER, defaultValue);
}

float ofxLua::getFloat(const unsigned int index, float defaultValue) {
	return read<float>(index, LUA_TNUMBER, defaultValue);
}

string ofxLua::getString(const string& name, const string& defaultValue) {
	return read<string>(name, LUA_TSTRING, defaultValue);
}

string ofxLua::getString(const unsigned int index, const string& defaultValue) {
	return read<string>(index, LUA_TSTRING, defaultValue);
}

void ofxLua::getBoolVector(const string& tableName, vector<bool>& v) {
	readVector<bool>(tableName, v, LUA_TBOOLEAN, false);
}

void ofxLua::getBoolVector(const unsigned int tableIndex, vector<bool>& v) {
	readVector<bool>(tableIndex, v, LUA_TBOOLEAN, false);
}

void ofxLua::getFloatVector(const string& tableName, vector<float>& v) {
	readVector<float>(tableName, v, LUA_TNUMBER, 0.0f);
}

void ofxLua::getFloatVector(const unsigned int tableIndex, vector<float>& v) {
	readVector<float>(tableIndex, v, LUA_TNUMBER, 0.0f);
}

void ofxLua::getStringVector(const string& tableName, vector<string>& v) {
	readVector<string>(tableName, v, LUA_TSTRING, "");
}

void ofxLua::getStringVector(const unsigned int tableIndex, vector<string>& v) {
	readVector<string>(tableIndex, v, LUA_TSTRING, "");
}

//------------------------------------------------------------------------------
void ofxLua::setBool(const string& name, bool value) {
	write<bool>(name, LUA_TBOOLEAN, value);
}

void ofxLua::setBool(const unsigned int index, bool value) {
	write<bool>(index, LUA_TBOOLEAN, value);
}

void ofxLua::setFloat(const string& name, float value) {
	write<float>(name, LUA_TNUMBER, value);
}

void ofxLua::setFloat(const unsigned int index, float value) {
	write<float>(index, LUA_TNUMBER, value);
}

void ofxLua::setString(const string& name, const string value) {
	write<string>(name, LUA_TSTRING, value);
}

void ofxLua::setString(const unsigned int index, const string value) {
	write<string>(index, LUA_TSTRING, value);
}

void ofxLua::setBoolVector(const string& tableName, vector<bool>& v) {
	writeVector<bool>(tableName, LUA_TBOOLEAN, v);
}

void ofxLua::setBoolVector(const unsigned int tableIndex, vector<bool>& v) {
	writeVector<bool>(tableIndex, LUA_TBOOLEAN, v);
}

void ofxLua::setFloatVector(const string& tableName, vector<float>& v) {
	writeVector<float>(tableName, LUA_TNUMBER, v);
}

void ofxLua::setFloatVector(const unsigned int tableIndex, vector<float>& v) {
	writeVector<float>(tableIndex, LUA_TNUMBER, v);
}

void ofxLua::setStringVector(const string& tableName, vector<string>& v) {
	writeVector<string>(tableName, LUA_TSTRING, v);
}

void ofxLua::setStringVector(const unsigned int tableIndex, vector<string>& v) {
	writeVector<string>(tableIndex, LUA_TSTRING, v);
}

void ofxLua::setNil(const string& name) {
	if(!isValid()) {
		return;
	}

	// global variable?
	if(tables.empty()) {
		lua_pushvalue(L, LUA_GLOBALSINDEX);
		lua_pushnil(L);
		lua_setfield(L, -2, name.c_str());
		lua_pop(L, 1);
	}
	
	// in a table namespace
	else {
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't set unknown var \"" << name << "\" to nil";
			return;
		}
		lua_pushstring(L, name.c_str());
		lua_pushnil(L);
		lua_settable(L, -3);
	}
}

void ofxLua::setNil(const unsigned int index) {
	if(!isValid()) {
		return;
	}
	
	// global variable?
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write global var by index, no open tables";
		return;
	}
	
	// in a table namespace
	else {
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't set unknown index " << index << " to nil";
			return;
		}
		lua_pushinteger(L, index);
		lua_pushnil(L);
		lua_settable(L, -3);
	}
}

//------------------------------------------------------------------------------
void ofxLua::writeTable(ofxLuaFileWriter& writer, bool recursive) {
	if(!isValid()) {
		return false;
	}

	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No table to write, did you push?";
		return;
	}
	
	// in a table namespace
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't write table \"" << tables.back()
			<< "\", top of stack is not a table";
		return;
	}
	
	writeTable(LUA_STACK_TOP, writer, recursive);
}

void ofxLua::writeTable(const string& tableName, ofxLuaFileWriter& writer, bool recursive) {
	if(!pushTable(tableName)) {
		return;
	}
	writer.beginTable(tableName);
	writeTable(writer, recursive);
	writer.endTable();
	popTable();
}

bool ofxLua::writeTableToFile(const string& filename, bool recursive) {
	ofxLuaFileWriter writer;
	writeTable(writer, recursive);
	return writer.saveToFile(filename);
}

bool ofxLua::writeTableToFile(const string& tableName, const string& filename, bool recursive) {
	ofxLuaFileWriter writer;
	writeTable(tableName, writer, recursive);
	return writer.saveToFile(filename);
}

// from http://www.lua.org/pil/24.2.3.html
void ofxLua::printStack() {
	if(!isValid()) {
		return;
	}
	
	stringstream line;
	line << "stack " << lua_gettop(L);

	int top = lua_gettop(L);
	if(top > 0) {
		line << ":";
	}
	for(int i = 1; i <= top; i++) {
		int type = lua_type(L, i);
		switch(type) {

			case LUA_TSTRING:
				line << " \"" << lua_tostring(L, i) << "\"";
				break;

			case LUA_TBOOLEAN:
				line << " " << lua_toboolean(L, i) ? "true" : "false";
				break;

			case LUA_TNUMBER:
				line << " " << lua_tonumber(L, i);
				break;

			default:
				line << " " << lua_typename(L, type);
				break;

		}
		if(i != top) {
			line << " ";
		}
	}
	ofLogNotice("ofxLua") << line.str();
}

//--------------------------------------------------------------------
void ofxLua::scriptSetup() {
	if(L == NULL || !isFunction("setup"))
		return;
	lua_getglobal(L, "setup");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running setup(): " + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptUpdate() {
	if(L == NULL || !isFunction("update"))
		return;
	lua_getglobal(L, "update");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running update(): " + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptDraw() {
	if(L == NULL || !isFunction("draw"))
		return;
	lua_getglobal(L, "draw");
	if(lua_pcall(L, 0, 0, 0) != 0) {			
		string msg = "Error running draw(): " + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptExit() {
	if(L == NULL || !isFunction("exit"))
		return;
	lua_getglobal(L, "exit");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running exit(): " + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

//--------------------------------------------------------------------
void ofxLua::scriptKeyPressed(int key) {
	if(L == NULL || !isFunction("keyPressed"))
		return;
	lua_getglobal(L, "keyPressed");
	lua_pushinteger(L, key);
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running keyPressed(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptKeyReleased(int key) {
	if(L == NULL || !isFunction("keyReleased"))
		return;
	lua_getglobal(L, "keyReleased");
	lua_pushinteger(L, key);
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running keyReleased(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseMoved(int x, int y ) {
	if(L == NULL || !isFunction("mouseMoved"))
		return;
	lua_getglobal(L, "mouseMoved");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	if(lua_pcall(L, 2, 0, 0) != 0) {
		string msg = "Error running mouseMoved(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseDragged(int x, int y, int button) {
	if(L == NULL || !isFunction("mouseDragged"))
		return;
	lua_getglobal(L, "mouseDragged");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {
		string msg = "Error running mouseDragged(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMousePressed(int x, int y, int button) {
	if(L == NULL || !isFunction("mousePressed"))
		return;
	lua_getglobal(L, "mousePressed");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {			
		string msg = "Error running mousePressed(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseReleased(int x, int y, int button) {
	if(L == NULL || !isFunction("mouseReleased"))
		return;
	lua_getglobal(L, "mouseReleased");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {
		string msg = "Error running mouseReleased(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

//--------------------------------------------------------------
// create copy of touch events to push to Lua usin SWIG helper function,
// from http://stackoverflow.com/questions/9455552/swiglua-passing-a-c-instance-as-a-lua-function-parameter
void ofxLua::scriptTouchDown(ofTouchEventArgs &touch) {
	if(L == NULL || !isFunction("touchDown")) return;
	lua_getglobal(L, "touchDown");
	swig_type_info *type = SWIG_TypeQuery(L, "ofTouchEventArgs *");
	ofTouchEventArgs *t = new ofTouchEventArgs(touch);
	SWIG_NewPointerObj(L, t, type, 1); // pushes pointer onto stack, 1 = Lua manages this memory
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running touchDown(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptTouchMoved(ofTouchEventArgs &touch) {
	if(L == NULL || !isFunction("touchDown")) return;
	lua_getglobal(L, "touchDown");
	swig_type_info *type = SWIG_TypeQuery(L, "ofTouchEventArgs *");
	ofTouchEventArgs *t = new ofTouchEventArgs(touch);
	SWIG_NewPointerObj(L, t, type, 1); // pushes pointer onto stack, 1 = Lua manages this memory
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running touchDown(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptTouchUp(ofTouchEventArgs &touch) {
	if(L == NULL || !isFunction("touchDown")) return;
	lua_getglobal(L, "touchDown");
	swig_type_info *type = SWIG_TypeQuery(L, "ofTouchEventArgs *");
	ofTouchEventArgs *t = new ofTouchEventArgs(touch);
	SWIG_NewPointerObj(L, t, type, 1); // pushes pointer onto stack, 1 = Lua manages this memory
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running touchDown(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptTouchDoubleTap(ofTouchEventArgs &touch) {
	if(L == NULL || !isFunction("touchDown")) return;
	lua_getglobal(L, "touchDown");
	swig_type_info *type = SWIG_TypeQuery(L, "ofTouchEventArgs *");
	ofTouchEventArgs *t = new ofTouchEventArgs(touch);
	SWIG_NewPointerObj(L, t, type, 1); // pushes pointer onto stack, 1 = Lua manages this memory
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running touchDown(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

void ofxLua::scriptTouchCancelled(ofTouchEventArgs &touch) {
	if(L == NULL || !isFunction("touchDown")) return;
	lua_getglobal(L, "touchDown");
	swig_type_info *type = SWIG_TypeQuery(L, "ofTouchEventArgs *");
	ofTouchEventArgs *t = new ofTouchEventArgs(touch);
	SWIG_NewPointerObj(L, t, type, 1); // pushes pointer onto stack, 1 = Lua manages this memory
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running touchDown(): "
					 + (string) lua_tostring(L, LUA_STACK_TOP);
		errorOccurred(msg);
	}
}

// UTIL

//------------------------------------------------------------------------------
void ofxLua::errorOccurred(string& msg) {
	
	errorMessage = msg;
	
	// send to listeners
	ofNotifyEvent(errorEvent, msg, this);
	
	// close the state?
	if(bAbortOnError) {
		clear();
	}
}

// PRIVATE

//------------------------------------------------------------------------------
// type specific implementations
template<> bool ofxLua::totype<bool>(int stackIndex, int type, bool defaultValue) {
	if(lua_type(L, stackIndex) != type) {
		return defaultValue;
	}
	switch(type) {
		case LUA_TBOOLEAN:
			return lua_toboolean(L, stackIndex);
		default:
			return defaultValue;
	}
}

template<> float ofxLua::totype<float>(int stackIndex, int type, float defaultValue) {
	if(lua_type(L, stackIndex) != type) {
		return defaultValue;
	}
	switch(type) {
		case LUA_TNUMBER:
			return lua_tonumber(L, stackIndex);
		default:
			return defaultValue;
	}
}

template<> string ofxLua::totype<string>(int stackIndex, int type, string defaultValue) {
	if(lua_type(L, stackIndex) != type) {
		return defaultValue;
	}
	switch(type) {
		case LUA_TSTRING:
			return lua_tostring(L, stackIndex);
		default:
			return defaultValue;
	}
}

//------------------------------------------------------------------------------
template <> void ofxLua::settype<bool>(const string& name, int type, bool value) {
	if(type == LUA_TBOOLEAN) {
		lua_pushboolean(L, value);
		lua_setfield(L, -2, name.c_str());
	}
}

template <> void ofxLua::settype<bool>(unsigned int index, int type, bool value) {
	if(type == LUA_TBOOLEAN) {
		lua_pushinteger(L, index);
		lua_pushboolean(L, value);
		lua_settable(L, -3);
	}
}

template <> void ofxLua::settype<float>(const string& name, int type, float value) {
	if(type == LUA_TNUMBER) {
		lua_pushnumber(L, value);
		lua_setfield(L, -2, name.c_str());
	}
}

template <> void ofxLua::settype<float>(unsigned int index, int type, float value) {
	if(type == LUA_TNUMBER) {
		lua_pushinteger(L, index);
		lua_pushnumber(L, value);
		lua_settable(L, -3);
	}
}

template <> void ofxLua::settype<string>(const string& name, int type, string value) {
	if(type == LUA_TSTRING) {
		lua_pushstring(L, value.c_str());
		lua_setfield(L, -2, name.c_str());
	}
}

template <> void ofxLua::settype<string>(unsigned int index, int type, string value) {
	if(type == LUA_TSTRING) {
		lua_pushinteger(L, index);
		lua_pushstring(L, value.c_str());
		lua_settable(L, -3);
	}
}

//------------------------------------------------------------------------------
bool ofxLua::exists(const string& name, int type) {
	if(!isValid()) {
		return false;
	}

	// global variable
	bool ret = false;
	if(tables.empty()) {
		lua_getglobal(L, name.c_str());
		ret = checkType(LUA_STACK_TOP, type);
		lua_pop(L, 1);
	}
	
	// table variable
	else {
		lua_getfield(L, LUA_STACK_TOP, name.c_str());
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't check existence of \"" << name
				<< "\", top of stack is not a table";
			ret = false;
		}
		else {
			ret = checkType(LUA_STACK_TOP, type);
		}
		lua_pop(L, 1);
	}
	return ret;
}

//------------------------------------------------------------------------------
bool ofxLua::exists(const unsigned int index, int type) {
	if(!isValid()) {
		return false;
	}
	
	bool ret = false;
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Cannot check existence of global var by index " << index;
		ofLogWarning("ofxLua") << "Did you forget to push a table? ";
		return false;
	}
	
	// table variable
	else {
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't check existence of index " << index
				<< ", top of stack is not a table";
			ret = false;
		}
		else {
			lua_pushinteger(L, index);
			lua_gettable(L, LUA_STACK_TOP-1);
			ret = checkType(LUA_STACK_TOP, type);
			lua_pop(L, 1);
		}
	}
	return ret;
}

//------------------------------------------------------------------------------
bool ofxLua::checkType(int stackIndex, int type) {
	return lua_type(L, stackIndex) == type;
}

//------------------------------------------------------------------------------
// from http://stackoverflow.com/questions/6137684/iterate-through-lua-table
void ofxLua::printTable(int stackIndex, int numTabs) {
	
	string tabs;
	for(int i = 0; i < numTabs; ++i) {
		tabs += "\t";
	}
	
	bool global = (stackIndex == LUA_GLOBALSINDEX);
	lua_pushvalue(L, stackIndex); // stack: -1 => table
	lua_pushnil(L); // stack : -2 => table; -1 => nil
	
	stringstream line;
	while(lua_next(L, -2)) {
	
		// stack: -3 => table; -2 => key; -1 => value
		lua_pushvalue(L, -2);
		// stack: -4 => table; -3 => key; -2 => value; -1 => key
	
		// ignore global packages, etc
		string name = (string) lua_tostring(L, -1);
		if(global && (name == "_G" || name == "package")) {
			line.str("");
			lua_pop(L, 2);
			continue;
		}
	
		// print value type and key
		line << tabs << (string) lua_typename(L, lua_type(L, -2)) << " " << name;
		
		// recurse if a table
		if(lua_istable(L, -2)) {
			ofLogNotice("ofxLua") << line.str();
			printTable(-2, numTabs+1);
		}
		else { // print values
			switch(lua_type(L, -2)) {
				case LUA_TBOOLEAN:
					ofLogNotice("ofxLua") << line.str() << ": " << ((bool)lua_toboolean(L, -2) ? "true" : "false");
					break;
				case LUA_TNUMBER:
					ofLogNotice("ofxLua") << line.str() << ": " << lua_tonumber(L, -2);
					break;
				case LUA_TSTRING:
					ofLogNotice("ofxLua") << line.str() << ": \"" << lua_tostring(L, -2) << "\"";
					break;
				default:
					ofLogNotice("ofxLua") << line.str();
					break;
			}
		}
		line.str("");
		lua_pop(L, 2); // stack: -2 => table; -1 => key
	}
	
	// stack: -1 => table
	lua_pop(L, 1); // stack:
}

//------------------------------------------------------------------------------
void ofxLua::writeTable(int stackIndex, ofxLuaFileWriter& writer, bool recursive) {
	
	lua_pushvalue(L, stackIndex); // stack: -1 => table
	lua_pushnil(L); // stack: -2 => table; -1 => nil
	
	stringstream line;
	while(lua_next(L, -2)) {

		// stack: -3 => table; -2 => key; -1 => value
		lua_pushvalue(L, -2);
		// stack: -4 => table; -3 => key; -2 => value; -1 => key
	
		// recurse if a table
		if(lua_istable(L, -2)) {
			if(recursive) {
				writer.beginTable(lua_tostring(L, -1));
				writeTable(-2, writer, true);
				writer.endTable();
			}
		}
		else { // print write values based on the key type
			switch(lua_type(L, -2)) {
				case LUA_TBOOLEAN:
					if(lua_isnumber(L, -1)) {
						writer.writeBool(lua_tonumber(L, -1), (bool)lua_toboolean(L, -2));
					}
					else if(lua_isstring(L, -1)) {
						writer.writeBool((string) lua_tostring(L, -1), (bool)lua_toboolean(L, -2));
					}
					else {
						ofLogWarning("ofxLua") << "unknown key type when writing table";
					}
					break;
				case LUA_TNUMBER:
					if(lua_isnumber(L, -1)) {
						writer.writeFloat(lua_tonumber(L, -1), lua_tonumber(L, -2));
					}
					else if(lua_isstring(L, -1)) {
						writer.writeFloat((string) lua_tostring(L, -1), lua_tonumber(L, -2));
					}
					else {
						ofLogWarning("ofxLua") << "unknown key type when writing table";
					}
					break;
				case LUA_TSTRING:
					if(lua_isnumber(L, -1)) {
						writer.writeString(lua_tonumber(L, -1), lua_tostring(L, -2));
					}
					else if(lua_isstring(L, -1)) {
						writer.writeString((string) lua_tostring(L, -1), lua_tostring(L, -2));
					}
					else {
						ofLogWarning("ofxLua") << "unknown key type when writing table";
					}
					break;
				default:
					break;
			}
		}
		line.str("");
		lua_pop(L, 2); // stack: -2 => table; -1 => key
	}
	
	// stack: -1 => table
	lua_pop(L, 1); // stack:
}

//------------------------------------------------------------------------------
int ofxLua::atPanic(lua_State *L) {
	ofLogError("ofxLua") << "Lua panic ocurred! : " << lua_tostring(L, LUA_STACK_TOP);
	ofLogError("ofxLua") << "Closing state";
	luaPtr->clear();
	return 0;
}
