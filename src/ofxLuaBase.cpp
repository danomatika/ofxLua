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
#include "ofxLuaBase.h"

#include "ofUtils.h"

using namespace std;

// local pointer for static functions
ofxLuaBase* luaPtr;

//--------------------------------------------------------------------
ofxLuaBase::ofxLuaBase() {
	L = NULL;
	bAbortOnError = false;
	luaPtr = this;
}

//--------------------------------------------------------------------
ofxLuaBase::~ofxLuaBase() {
//	clear();
}

//--------------------------------------------------------------------
//bool ofxLuaBase::init(bool abortOnError, bool openLibs) {
//	
//	clear();
//	
//	L = luaL_newstate();
//	if(L == NULL) {
//		ofLogError("ofxLua") << "Error initializing lua";
//		return false;
//	}
//	
//	// open libs
//	if(openLibs) {
//		luaL_openlibs(L);
//	}
//	luabind::open(L);
//	
//	// set the panic function
//	lua_atpanic(L, &atPanic);
//	
//	bAbortOnError = abortOnError;
//	ofLogVerbose("ofxLua") << "Initialized";
//	
//	return true;
//}
//	
//
void ofxLuaBase::clear() {
	if(L != NULL) {
		lua_close(L);
		L = NULL;
		if(isThread()) {
			ofLogVerbose("ofxLua") << "Cleared thread";
		}
		else {
			ofLogVerbose("ofxLua") << "Cleared state";
		}
	}
}

bool ofxLuaBase::isValid() {
	return L != NULL ? true : false;
}

//--------------------------------------------------------------------
bool ofxLuaBase::doString(const std::string& text) {
	
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
bool ofxLuaBase::doScript(const std::string& script) {

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
//bool ofxLuaBase::funcExists(const std::string& name) {
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

////--------------------------------------------------------------------		
//void ofxLuaBase::addListener(ofxLuaListener& listener) {
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
//void ofxLuaBase::removeListener(ofxLuaListener& listener) {
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
//void ofxLuaBase::clearListeners() {
//	listeners.clear();
//}

//--------------------------------------------------------------------	
bool ofxLuaBase::variableExists(const std::string& name) {
	return exists(name, LUA_TNIL);
}

bool ofxLuaBase::numberExists(const std::string& name) {
	return exists(name, LUA_TNUMBER);
}

bool ofxLuaBase::boolExists(const std::string& name) {
	return exists(name, LUA_TBOOLEAN);
}

bool ofxLuaBase::intExists(const std::string& name) {
	return exists(name, LUA_TINTEGER);
}

bool ofxLuaBase::uintExists(const std::string& name) {
	return exists(name, LUA_TUINTEGER);
}

bool ofxLuaBase::floatExists(const std::string& name) {
	return exists(name, LUA_TFLOAT);
}

bool ofxLuaBase::stringExists(const std::string& name) {
	return exists(name, LUA_TSTRING);
}

bool ofxLuaBase::functionExists(const std::string& name) {
	return exists(name, LUA_TFUNCTION);
}

bool ofxLuaBase::tableExists(const std::string& name) {
	return exists(name, LUA_TTABLE);
}
		
//--------------------------------------------------------------------	
bool ofxLuaBase::pushTable(const std::string& tableName, bool isGlobal) {
	
	// global table
	if(tables.empty() || isGlobal) {
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

void ofxLuaBase::popTable() {
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No tables to pop, did you push?";
		return;
	}
	tables.pop_back();
	lua_pop(L, 1);
}


void ofxLuaBase::popAllTables() {
	while(!tables.empty()) {
		popTable();
	}
}

unsigned int ofxLuaBase::tableSize() {
	
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't get table size, no open tables";
		return 0;
	}
	
	// count manually
	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't get table size, stack var is not a table";
		return 0;
	}
	
	unsigned int size = 0;
	for(luabind::iterator iter(o), end; iter != end; ++iter) {
		size++;
	}
	return size;
}

unsigned int ofxLuaBase::tableSize(const std::string& tableName) {
	unsigned int size = 0;
	pushTable(tableName);
	size = tableSize();
	popTable();
	return size;
}

void ofxLuaBase::printTable() {
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No table to print, did you push?";
		return;
	}
	
	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't print table, stack var is not a table";
	}
	
	ofLogNotice("ofxLua") << "table: " << tables.back();
	printTable(o, 1);
}
		
//--------------------------------------------------------------------	
bool ofxLuaBase::readBool(const std::string& name, bool defaultValue) {
	return read<bool>(name, defaultValue);
}

int ofxLuaBase::readInt(const std::string& name, int defaultValue) {
	return read<int>(name, defaultValue);
}

unsigned int ofxLuaBase::readUInt(const std::string& name, unsigned int defaultValue) {
	return read<unsigned int>(name, defaultValue);
}

float ofxLuaBase::readFloat(const std::string& name, float defaultValue) {
	return read<float>(name, defaultValue);
}

std::string ofxLuaBase::readString(const std::string& name, const std::string& defaultValue) {
	return read<string>(name, defaultValue);
}

void ofxLuaBase::readBoolVector(const std::string& tableName, std::vector<bool>& v) {
	readVector<bool>(tableName, v);
}

void ofxLuaBase::readIntVector(const std::string& tableName, std::vector<int>& v) {
	readVector<int>(tableName, v);
}

void ofxLuaBase::readUIntVector(const std::string& tableName, std::vector<unsigned int>& v) {
	readVector<unsigned int>(tableName, v);
}

void ofxLuaBase::readFloatVector(const std::string& tableName, std::vector<float>& v) {
	readVector<float>(tableName, v);
}

void ofxLuaBase::readStringVector(const std::string& tableName, std::vector<std::string>& v) {
	readVector<string>(tableName, v);
}

//--------------------------------------------------------------------
//void ofxLuaBase::printGlobals() {
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

//--------------------------------------------------------------------
//void ofxLuaBase::scriptSetup() {
//	if(L == NULL || !functionExists("setup"))
//		return;
//	lua_getglobal(L, "setup");
//	if(lua_pcall(L, 0, 0, 0) != 0) {
//		string msg = "Error running setup(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaBase::scriptUpdate() {
//	if(L == NULL || !functionExists("update"))
//		return;
//	lua_getglobal(L, "update");
//	if(lua_pcall(L, 0, 0, 0) != 0) {
//		string msg = "Error running update(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaBase::scriptDraw() {
//	if(L == NULL || !functionExists("draw"))
//		return;
//	lua_getglobal(L, "draw");
//	if(lua_pcall(L, 0, 0, 0) != 0) {			
//		string msg = "Error running draw(): " + (string) lua_tostring(L, -1);
//		errorOccurred(msg);
//	}
//}
//
//void ofxLuaBase::scriptExit() {
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
//void ofxLuaBase::scriptKeyPressed(int key) {
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
//void ofxLuaBase::scriptMouseMoved(int x, int y ) {
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
//void ofxLuaBase::scriptMouseDragged(int x, int y, int button) {
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
//void ofxLuaBase::scriptMousePressed(int x, int y, int button) {
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
//void ofxLuaBase::scriptMouseReleased(int x, int y, int button) {
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

// PRIVATE

//--------------------------------------------------------------------
bool ofxLuaBase::exists(const std::string& name, int type) {
	
	// global variable
	if(tables.empty()) {
		lua_getglobal(L, name.c_str());
		luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
		return checkType(type, o);
	}
	
	// table variable
	else {
		luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(o) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Coudln't check existence of \"" << name
				<< "\", top of stack is not a table";
			return false;
		}
		luabind::object object(o[name]);
		return checkType(type, object);
	}
}

//--------------------------------------------------------------------
bool ofxLuaBase::checkType(int type, luabind::object& object) {
	
	if(!object.is_valid())
		return false;
	
	int objectType = luabind::type(object);
	
	if(type == LUA_TNIL) {
		return true;
	}
	
	// non numeric types
	else if(objectType == type) {
		return true;
	}
		
	// do brute force cast check to find number type
	else if(objectType == LUA_TNUMBER) {
		if(type == LUA_TINTEGER) {
			try {
				luabind::object_cast<int>(object);
				return true;
			}
			catch(...) {
				return false;
			}
		}
		else if(type == LUA_TUINTEGER) {
			try {
				luabind::object_cast<unsigned int>(object);
				return true;
			}
			catch(...) {
				return false;
			}
		}
		else if(type == LUA_TFLOAT) {
			try {
				luabind::object_cast<float>(object);
				return true;
			}
			catch(...) {
				return false;
			}
		}
	}
	
	return false;
}

//--------------------------------------------------------------------
void ofxLuaBase::printTable(luabind::object table, int numTabs) {
	
	string tabs;
	for(int i = 0; i < numTabs; ++i) {
		tabs += "\t";
	}
	
	stringstream line;
	for(luabind::iterator iter(table), end; iter != end; ++iter) {
		line << tabs << " "
			<< (string) lua_typename(L, luabind::type(*iter)) << ": "
			<< iter.key();
		if(luabind::type(*iter) == LUA_TTABLE) {
			ofLogNotice("ofxLua") << line.str();
			printTable(luabind::object(*iter), numTabs+1);
		}
		else {
			// only print valid values
			switch(luabind::type(*iter)) {
				case LUA_TBOOLEAN:
				case LUA_TNUMBER:
				case LUA_TSTRING:
					ofLogNotice("ofxLua") << line.str() << " " << (*iter);
					break;
				default:
					ofLogNotice("ofxLua") << line.str();
					break;
			}
		}
		line.str("");
	}
}

//--------------------------------------------------------------------
void ofxLuaBase::errorOccurred(const std::string& msg) {
	
//	// print
//	for(int i = 0; i < listeners.size(); ++i) {
//		listeners[i]->errorReceived(msg);
//	}
	ofLogError("ofxLua") << msg;
	
	// close the state?
	if(bAbortOnError) {
		if(isThread()) {
			ofLogError("ofxLua") << "Closing thread";
		}
		else {
			ofLogError("ofxLua") << "Closing state";
		}
		clear();
	}
}

//--------------------------------------------------------------------
int ofxLuaBase::atPanic(lua_State *L) {
	ofLogError("ofxLua") << "Lua panic ocurred! : " << lua_tostring(L, -1);
	if(luaPtr->isThread()) {
		ofLogError("ofxLua") << "Closing thread";
	}
	else {
		ofLogError("ofxLua") << "Closing state";
	}
	luaPtr->clear();
	return 0;
}
