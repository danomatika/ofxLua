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

// local pointer for static functions
ofxLua* luaPtr;

namespace {
    struct LuaDebugStack {
        LuaDebugStack(lua_State* L, const char* where)
        : mLua(L)
        , mMessage(where) {
            std::cout << "+++ " << mMessage << ": stack top " << ::lua_gettop(mLua) << std::endl;
        }
        ~LuaDebugStack() {
            std::cout << "--- " << mMessage << ": stack top " << ::lua_gettop(mLua) << std::endl;
        }
    private:
        std::string mMessage;
        lua_State*   mLua;
    };
}

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
	return L != NULL ? true : false;
}

//------------------------------------------------------------------------------
bool ofxLua::doString(const string& text) {
	
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

//------------------------------------------------------------------------------
bool ofxLua::doScript(const string& script) {

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
	if(lua_pcall(L, 0, LUA_MULTRET, 0) != 0) {
		string msg = "Runtime error: "+(string) lua_tostring(L, -1);
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
	
	// global table
	if(tables.empty()) {
		lua_getglobal(L, tableName.c_str());
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't push global table \""
				<< tableName << "\"";
			return false;
		}
		tables.push_back(tableName);
	}
	
	// table in another table
	else {
		lua_pushstring(L, tableName.c_str());
		lua_gettable(L, LUA_STACK_TOP - 1);
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't push table \""
				<< tableName << "\"";
			return false;
		}
		tables.push_back(tableName);
	}
	
	return true;
}

bool ofxLua::pushTable(const unsigned int& tableIndex) {

	// global table
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Cannot push global table by index" << tableIndex;
		return false;
	}
	
	lua_pushnumber(L, tableIndex);
	lua_gettable(L, LUA_STACK_TOP - 1);
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't push table \""
			<< tableIndex << "\"";
		return false;
	}
	tables.push_back((string) lua_tostring(L, LUA_STACK_TOP));
	
	return true;
}

void ofxLua::popTable() {
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
}

unsigned int ofxLua::tableSize() {

	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't get table size, no open tables";
		return 0;
	}
	
	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
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

	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No table to print, did you push?";
		return;
	}
	
	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't print table, stack var is not a table";
	}
	
	ofLogNotice("ofxLua") << tables.back() << " table";
	printTable(o, 1);
}

void ofxLua::printTable(const string& tableName) {
	pushTable(tableName);
	printTable();
	popTable();
}

void ofxLua::clearTable() {

	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No table to clear, did you push?";
		return;
	}
	
	luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(table) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't clear table, stack var is not a table";
	}
	
	for(luabind::iterator iter(table), end; iter != end; ++iter) {
		*iter = luabind::nil;
	}
}

void ofxLua::clearTable(const string& tableName) {
	pushTable(tableName);
	clearTable();
	popTable();
}
		
//------------------------------------------------------------------------------
bool ofxLua::getBool(const string& name, bool defaultValue) {
	return read<bool>(name, defaultValue);
}

bool ofxLua::getBool(const unsigned int index, bool defaultValue) {
	return read<bool>(index, defaultValue);
}

float ofxLua::getFloat(const string& name, float defaultValue) {
	return read<float>(name, defaultValue);
}

float ofxLua::getFloat(const unsigned int index, float defaultValue) {
	return read<float>(index, defaultValue);
}

string ofxLua::getString(const string& name, const string& defaultValue) {
	return read<string>(name, defaultValue);
}

string ofxLua::getString(const unsigned int index, const string& defaultValue) {
	return read<string>(index, defaultValue);
}

void ofxLua::getBoolVector(const string& tableName, vector<bool>& v) {
	readVector<bool>(tableName, v);
}

void ofxLua::getBoolVector(const unsigned int tableIndex, vector<bool>& v) {
	readVector<bool>(tableIndex, v);
}

void ofxLua::getFloatVector(const string& tableName, vector<float>& v) {
	readVector<float>(tableName, v);
}

void ofxLua::getFloatVector(const unsigned int tableIndex, vector<float>& v) {
	readVector<float>(tableIndex, v);
}

void ofxLua::getStringVector(const string& tableName, vector<string>& v) {
	readVector<string>(tableName, v);
}

void ofxLua::getStringVector(const unsigned int tableIndex, vector<string>& v) {
	readVector<string>(tableIndex, v);
}

//------------------------------------------------------------------------------
void ofxLua::setBool(const string& name, bool value) {
	write<bool>(name, value);
}

void ofxLua::setBool(const unsigned int index, bool value) {
	write<bool>(index, value);
}

void ofxLua::setFloat(const string& name, float value) {
	write<float>(name, value);
}

void ofxLua::setFloat(const unsigned int index, float value) {
	write<float>(index, value);
}

void ofxLua::setString(const string& name, const string value) {
	write<string>(name, value);
}

void ofxLua::setString(const unsigned int index, const string value) {
	write<string>(index, value);
}

void ofxLua::setBoolVector(const string& tableName, vector<bool>& v) {
	writeVector<bool>(tableName, v);
}

void ofxLua::setBoolVector(const unsigned int tableIndex, vector<bool>& v) {
	writeVector<bool>(tableIndex, v);
}

void ofxLua::setFloatVector(const string& tableName, vector<float>& v) {
	writeVector<float>(tableName, v);
}

void ofxLua::setFloatVector(const unsigned int tableIndex, vector<float>& v) {
	writeVector<float>(tableIndex, v);
}

void ofxLua::setStringVector(const string& tableName, vector<string>& v) {
	writeVector<string>(tableName, v);
}

void ofxLua::setStringVector(const unsigned int tableIndex, vector<string>& v) {
	writeVector<string>(tableIndex, v);
}

void ofxLua::setNil(const string& name) {
	try {
		// global variable?
		if(tables.size() == 0) {
			luabind::object table(luabind::from_stack(L, LUA_GLOBALSINDEX));
			table[name] = luabind::nil;
		}
		else { // in a table namespace
			luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
			table[name] = luabind::nil;
		}
	}
	catch(...) {
		ofLogWarning("ofxLua") << "Couldn't set unknown \"" << name << "\" to nil";
	}
}

void ofxLua::setNil(const unsigned int index) {
	try {
		// global variable?
		if(tables.empty()) {
			luabind::object table(luabind::from_stack(L, LUA_GLOBALSINDEX));
			table[index] = luabind::nil;
		}
		else { // in a table namespace
			luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
			table[index] = luabind::nil;
		}
	}
	catch(...) {
		ofLogWarning("ofxLua") << "Couldn't set unknown index " << index << " to nil";
	}
}

//------------------------------------------------------------------------------
void ofxLua::writeTable(ofxLuaFileWriter& writer, bool recursive) {

	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No table to write, did you push?";
		return;
	}
	
	// in a table namespace
	luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(table) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't write table \"" << tables.back()
			<< "\", top of stack is not a table";
		return;
	}
	
	writeTable(table, writer, recursive);
}

void ofxLua::writeTable(const string& tableName, ofxLuaFileWriter& writer, bool recursive) {
	if(!pushTable(tableName)) {
		return;
	}
	writeTable(writer, recursive);
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

//--------------------------------------------------------------------
void ofxLua::printGlobals() {
	luabind::object o(luabind::from_stack(L, LUA_GLOBALSINDEX));
	for(luabind::iterator iter(o), end; iter != end; ++iter) {
		if(iter.key() != "_G" && iter.key() != "package") {
			
			// only print valid values
			switch(luabind::type(*iter)) {
				case LUA_TBOOLEAN:
				case LUA_TNUMBER:
				case LUA_TSTRING:
					ofLogNotice("ofxLua") << "\t"
						<< (string) lua_typename(L, luabind::type(*iter)) << ": "
						<< iter.key() << " " << (*iter);
					break;
				default:
					ofLogNotice("ofxLua") << "\t"
						<< (string) lua_typename(L, luabind::type(*iter)) << ": "
						<< iter.key();
					break;
			}
				
			if(luabind::type(*iter) == LUA_TTABLE) {
					printTable(luabind::object(*iter), 2);
			}
		}
	}
}

//--------------------------------------------------------------------
void ofxLua::scriptSetup() {
	if(L == NULL || !isFunction("setup"))
		return;
	lua_getglobal(L, "setup");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running setup(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptUpdate() {
	if(L == NULL || !isFunction("update"))
		return;
	lua_getglobal(L, "update");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running update(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptDraw() {
	if(L == NULL || !isFunction("draw"))
		return;
	lua_getglobal(L, "draw");
	if(lua_pcall(L, 0, 0, 0) != 0) {			
		string msg = "Error running draw(): " + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptExit() {
	if(L == NULL || !isFunction("exit"))
		return;
	lua_getglobal(L, "exit");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running exit(): " + (string) lua_tostring(L, -1);
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
					 + (string) lua_tostring(L, -1);
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
					 + (string) lua_tostring(L, -1);
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
					 + (string) lua_tostring(L, -1);
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
					 + (string) lua_tostring(L, -1);
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
					 + (string) lua_tostring(L, -1);
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
					 + (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}


//--------------------------------------------------------------
// calling lua functions with objects:
// http://www.nuclex.org/articles/cxx/1-quick-introduction-to-luabind
void ofxLua::scriptTouchDown(ofTouchEventArgs &touch) {
	if(L == NULL) return;
	ofxLuaTouchEvent touchEvent(touch); // convert to wrapper with copy operator
	try {
		luabind::call_function<bool>(L, "touchDown", boost::ref(touchEvent));
	}
	catch(exception& e) {}
}

void ofxLua::scriptTouchMoved(ofTouchEventArgs &touch) {
	if(L == NULL) return;
	ofxLuaTouchEvent touchEvent(touch);
	try {
		luabind::call_function<bool>(L, "touchMoved", boost::ref(touchEvent));
	}
	catch(exception& e) {}
}

void ofxLua::scriptTouchUp(ofTouchEventArgs &touch) {
	if(L == NULL) return;
	ofxLuaTouchEvent touchEvent(touch);
	try {
		luabind::call_function<bool>(L, "touchUp", boost::ref(touchEvent));
	}
	catch(exception& e) {}
}

void ofxLua::scriptTouchDoubleTap(ofTouchEventArgs &touch) {
	if(L == NULL) return;
	ofxLuaTouchEvent touchEvent(touch);
	try {
		luabind::call_function<bool>(L, "touchDoubleTap", boost::ref(touchEvent));
	}
	catch(exception& e) {}
}

void ofxLua::scriptTouchCancelled(ofTouchEventArgs &touch) {
	if(L == NULL) return;
	ofxLuaTouchEvent touchEvent(touch);
	try {
		luabind::call_function<bool>(L, "touchCancelled", boost::ref(touchEvent));
	}
	catch(exception& e) {}
}

// PRIVATE

//------------------------------------------------------------------------------
bool ofxLua::exists(const string& name, int type) {

	// global variable

	bool ret = false;
	if(tables.empty()) {
		lua_getglobal(L, name.c_str());
		luabind::object object(luabind::from_stack(L, LUA_STACK_TOP));
		ret = checkType(type, object);
		::lua_pop(L, 1);
	}
	
	// table variable
	else {
		luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(table) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Couldn't check existence of \"" << name
				<< "\", top of stack is not a table";
			ret = false;
		}
		else {
			luabind::object object(table[name]);
			ret = checkType(type, object);
		}
	}
	return ret;
}

//------------------------------------------------------------------------------
bool ofxLua::exists(const unsigned int index, int type) {
	
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Cannot check existence of global var by index" << index;
		ofLogWarning("ofxLua") << "Did you forget to push a table?" << index;
		return false;
	}
	
	// table variable
	else {
		luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(table) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Couldn't check existence of index " << index
				<< ", top of stack is not a table";
			return false;
		}
		luabind::object object(table[index]);
		return checkType(type, object);
	}
}

//------------------------------------------------------------------------------
bool ofxLua::checkType(int type, luabind::object& object) {
	
	if(!object.is_valid())
		return false;

	if(luabind::type(object) == type)
		return true;
	return false;
}

//------------------------------------------------------------------------------
void ofxLua::printTable(luabind::object table, int numTabs) {
	
	string tabs;
	for(int i = 0; i < numTabs; ++i) {
		tabs += "\t";
	}
	
	stringstream line;
	for(luabind::iterator iter(table), end; iter != end; ++iter) {
		line << tabs << iter.key() << " "
			 << (string) lua_typename(L, luabind::type(*iter));
		if(luabind::type(*iter) == LUA_TTABLE) {
			ofLogNotice("ofxLua") << line.str();
			printTable(luabind::object(*iter), numTabs+1);
		}
		else {
			// only print valid values
			switch(luabind::type(*iter)) {
				case LUA_TBOOLEAN:
					ofLogNotice("ofxLua") << line.str() << ": " << (bool) (*iter);
					break;
				case LUA_TNUMBER:
					ofLogNotice("ofxLua") << line.str() << ": " << (*iter);
					break;
				case LUA_TSTRING:
					ofLogNotice("ofxLua") << line.str() << ": \"" << (*iter) << "\"";
					break;
				default:
					ofLogNotice("ofxLua") << line.str();
					break;
			}
		}
		line.str("");
	}
}

//------------------------------------------------------------------------------
void ofxLua::writeTable(luabind::object table, ofxLuaFileWriter& writer, bool recursive) {
	
	for(luabind::iterator iter(table), end; iter != end; ++iter) {
		if(luabind::type(*iter) == LUA_TTABLE) {
			if(recursive) {
				writer.beginTable(luabind::object_cast<string>(iter.key()));
				writeTable(luabind::object(*iter), writer, true);
				writer.endTable();
			}
		}
		else {
			// only print valid values
			switch(luabind::type(*iter)) {
				
				case LUA_TBOOLEAN:
				{
					// try with key as name
					try {
						string name = luabind::object_cast<string>(iter.key());
						writer.writeBool(name, (bool) (*iter));
						
					}
					catch(...) { // key as index
						unsigned int index = luabind::object_cast<unsigned int>(iter.key());
						writer.writeBool(index, (bool) (*iter));
					}
					break;
				}
				
				case LUA_TNUMBER:
				{
					// try with key as name
					try {
						string name = luabind::object_cast<string>(iter.key());
						writer.writeFloat(name, luabind::object_cast<float>(*iter));
						
					}
					catch(...) { // key as index
						unsigned int index = luabind::object_cast<unsigned int>(iter.key());
						writer.writeFloat(index, luabind::object_cast<float>(*iter));
					}
					break;
				}
				case LUA_TSTRING:
				{
					// try with key as name
					try {
						string name = luabind::object_cast<string>(iter.key());
						writer.writeString(name, luabind::object_cast<string>(*iter));
						
					}
					catch(...) { // key as index
						unsigned int index = luabind::object_cast<unsigned int>(iter.key());
						writer.writeString(index, luabind::object_cast<string>(*iter));
					}
					break;
				}
				default:
					break;
			}
		}
	}
}

//------------------------------------------------------------------------------
void ofxLua::errorOccurred(string& msg) {
	
	errorMessage = msg;
	
	// send to listeners
	ofNotifyEvent(errorEvent, msg, this);
	
	// comment this for now, better to let user handle it
	//ofLogError("ofxLua") << msg;
	
	// close the state?
	if(bAbortOnError) {
		clear();
	}
}

//------------------------------------------------------------------------------
int ofxLua::atPanic(lua_State *L) {
	ofLogError("ofxLua") << "Lua panic ocurred! : " << lua_tostring(L, -1);
	ofLogError("ofxLua") << "Closing state";
	luaPtr->clear();
	return 0;
}
