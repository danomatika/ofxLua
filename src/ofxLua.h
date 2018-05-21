/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 * This project uses the following library:
 *
 * Lua, Copyright (c) 1994â2011 Lua.org, PUC-Rio using the MIT License.
 * See the file "COPYRIGHT" in src/lua.
 * See http://www.lua.org/docs.html for documentation
 *
 */
#pragma once

#include "ofConstants.h"
#include "ofEvents.h"

#include "lua.hpp"
#include "ofxLuaFileWriter.h"

// define pua_pushglobaltable for lua 5.1 api
#if LUA_VERSION_NUM < 502
	#define lua_pushglobaltable(L) lua_pushvalue(L, LUA_GLOBALSINDEX)
#endif

/// a baseclass to receieve lua error messages,
/// useful for displaying an error message on the screen, etc
class ofxLuaListener {

	public :
	
		virtual void errorReceived(string& msg) = 0;
};

///	a Lua interpreter instance
///
///	references:
///     - lua api http://www.lua.org/manual/5.1/manual.html
///		- swig and lua http://swig.org/Doc1.3/Lua.html
///
/// the read/write algos are largely derived from the Allacrost scripting system: http://allacrost.sourceforge.net/
class ofxLua {
	
	public :

		ofxLua();
		virtual ~ofxLua();
		
		/// init the lua state
		///
		/// set abortOnError to true if you want the lua state to be cleared
		/// when an error occurs
		///
		/// set openLibs to false if you don't want to load the
		/// standard lua libs (math, io, string, etc)
		///
		/// set ofBindings to false if you don't want to load the OF api lua bindings
		///
		/// note: calls clear if the state has already been inited
		///
		bool init(bool abortOnError=false, bool openLibs=true, bool ofBindings=true);
		
		/// clears current state
		///
		/// note: this also clears all loaded modules
		///
		void clear();
		
		/// is this state valid? (inited, not aborted, etc)
		bool isValid();
		
		/// get/set abort on error
		/// if abort on error is true, the state is closed when an error ocurrs
		bool getAbortOnError();
		void setAbortOnError(bool abort);
		
	/// \section Running Lua code
		
		/// run a lua string, returns false on script error
		bool doString(const string& text);
		
		/// run a lua script, returns false on script error
		///
		/// set changeDir = true to change the current working dir
		/// to the script's parent dir, use this if lua's require command
		/// cannot find local scripts
		///
		/// note: changeDir does not affect the current OF data path
		bool doScript(const string& script, bool changeDir=false);
		
	/// \section Listeners
		
		/// add a listener, ignores any duplicates
		void addListener(ofxLuaListener* listener);
		
		/// remove a listener
		void removeListener(ofxLuaListener* listener);
		
	/// \section Script Callbacks
		
		/// these are default script callbacks which call a global lua function
		/// of the same name and arguments within the current lua state
		///
		/// they fail silently if the function does not exist
		///
		void scriptSetup();
		void scriptUpdate();
		void scriptDraw();
		void scriptExit();
	
		void scriptWindowResized(int w, int h);
		void scriptKeyPressed(int key);
		void scriptKeyReleased(int key);
		void scriptMouseMoved(int x, int y );
		void scriptMouseDragged(int x, int y, int button);
		void scriptMousePressed(int x, int y, int button);
		void scriptMouseReleased(int x, int y, int button);
		void scriptMouseScrolled(int x, int y, float scrollX, float scrollY);
		void scriptMouseEntered(int x, int y);
		void scriptMouseExited(int x, int y);
	
		void scriptDragEvent(ofDragInfo dragInfo);
		void scriptGotMessage(ofMessage msg); //< sends msg contents as a string
	
		// mobile
		void scriptTouchDown(ofTouchEventArgs &touch);
		void scriptTouchMoved(ofTouchEventArgs &touch);
		void scriptTouchUp(ofTouchEventArgs &touch);
		void scriptTouchDoubleTap(ofTouchEventArgs &touch);
		void scriptTouchCancelled(ofTouchEventArgs &touch);
		
	/// \section Variables
		
		/// check if a variable exists as a certain type in the lua state
		///
		/// note: pushTable must have been called when using the table index
		
		bool isBool(const string& name);
		bool isBool(const unsigned int index);
		
		bool isNumber(const string& name);
		bool isNumber(const unsigned int index);
		
		bool isString(const string& name);
		bool isString(const unsigned int index);
		
		bool isFunction(const string& name);
		bool isFunction(const unsigned int index);
		
		bool isTable(const string& name);
		bool isTable(const unsigned int index);
		
		/// check explictly if something *dosen't* exist
		///
		/// nil is the lua equivalent of NULL
		bool isNil(const string& name);
		bool isNil(const unsigned int index);
	
	/// \section Table Operations
	
		/// create a new table
		void newTable(const string& tableName);
		void newTable(const unsigned int& tableIndex); // must pushTable first
	
		/// push table one level
		bool pushTable(const string& tableName);
		bool pushTable(const unsigned int& tableIndex); // must pushTable first
		void popTable(); //< pop table one level
		void popAllTables(); //< pop all table levels
		
		/// get the size of a table
		/// undefined if the table is not a sequence aka has a nil value somewhere
		unsigned int tableSize(); //< current table
		unsigned int tableSize(const string& tableName); //< table in current table
		unsigned int tableSize(const unsigned int& tableIndex); //< table in current table
		
		/// print a table
		void printTable(); //< current table
		void printTable(const string& tableName); //< table in current table
		void printTable(const unsigned int& tableIndex); //< table in current table
		
		/// clear a table, removes all objects in the table
		void clearTable(); //< current table
		void clearTable(const string& tableName); //< table in current table
		void clearTable(const unsigned int& tableIndex); //< table in current table
	
	/// \section Reading
		
		/// note: integer indices start with 1!
		
		/// get variables
		bool getBool(const string& name, bool defaultValue=false);
		bool getBool(const unsigned int index, bool defaultValue=false);
		
		lua_Number getNumber(const string& name, lua_Number devaultValue=0);
		lua_Number getNumber(const unsigned int index, lua_Number devaultValue=0);
		
		string getString(const string& name, const string& defaultValue="");
		string getString(const unsigned int index, const string& defaultValue="");
		
		/// get a vector from a table, prints warnings on wrong type
		///
		/// note: clears given vector before reading lua vars
		void getBoolVector(const string& tableName, vector<bool>& v);
		void getBoolVector(const unsigned int tableIndex, vector<bool>& v);
		
		void getNumberVector(const string& tableName, vector<lua_Number>& v);
		void getNumberVector(const unsigned int tableIndex, vector<lua_Number>& v);
		
		void getStringVector(const string& tableName, vector<string>& v);
		void getStringVector(const unsigned int tableIndex, vector<string>& v);
	
	/// \section Writing
		
		/// note: integer indices start with 1!
		
		/// set variables, creates if not existing
		void setBool(const string& name, bool value);
		void setBool(const unsigned int index, bool value);
		
		void setNumber(const string& name, lua_Number value);
		void setNumber(const unsigned int index, lua_Number value);
		
		void setString(const string& name, const string value);
		void setString(const unsigned int index, const string value);

		/// set a table from a vector, table must exist
		void setBoolVector(const string& tableName, vector<bool>& v);
		void setBoolVector(const unsigned int tableIndex, vector<bool>& v);
		
		void setNumberVector(const string& tableName, vector<lua_Number>& v);
		void setNumberVector(const unsigned int tableIndex, vector<lua_Number>& v);
		
		void setStringVector(const string& tableName, vector<string>& v);
		void setStringVector(const unsigned int tableIndex, vector<string>& v);
	
		/// set a variable or table to nil, essentially deleting it from the state
		void setNil(const string& name);
		void setNil(const unsigned int index);
	
	/// \section Writing to a File
	
		/// write simple variables and tables to a text file
		///
		/// this does not save actual scripts or the current state, only data in
		/// a given table
		///
		/// note: cannot save the global table, you must call pushTable if you
		/// don't save using a tableName
		///
		/// set recursive = false to only write data in the current level aka
		/// lower level tables are ignored
	
		/// write the current table to a given file writer
		void writeTable(ofxLuaFileWriter& writer, bool recursive=true);
		void writeTable(const string& tableName, ofxLuaFileWriter& writer, bool recursive=true);
		
		bool writeTableToFile(const string& filename, bool recursive=true);
		bool writeTableToFile(const string& tableName, const string& filename, bool recursive=true);
	
	/// \section Util
	
		/// send a lua error message to any listeners and clear lua state
		/// if abortOnError is set
		virtual void errorOccurred(string& msg);
	
		/// get the current error message, an alternative to ofxLuaListener
		string getErrorMessage();
	
		/// print current stack length and contents
		/// from left to right, useful for debugging
		void printStack();
	
		/// get the raw lua state, useful for custom lua api code
		///
		/// example, call "myFunction(x, y)" in the lua state:
		///
		///     int x = 20, y = 10;
		///     ofxLua lua;
		///     lua.init();
		///     
		///     lua_getglobal(lua, "myFunction");
		///     lua_pushinteger(lua, x);
		///     lua_pushinteger(lua, y);
		///     if(lua_pcall(lua, 2, 0, 0) != 0) {
		///         cout << "error running myFunction" << endl;
		///     }
		///
		///	note: make sure to call lua.init() before using the lua state!
		///
		operator lua_State*() const {return L;}
	
		/// push a custom wrapped SWIG object pointer onto the stack,
		/// similar to lua_pushinteger, lua_pushstring, etc
		///
		/// typeName: name of the wrapped *orginal* C/C++ type as a string
		/// object: the pointer
		/// manageMemory: set to true if you want the lua garbage collector to
		///               manage the memory pointed to
		///
		/// returns true if the pointer type was found and pushed
		///
		/// example, call a global lua function "touchDown" with a touch event
		///
		///     ofTouchEventArgs *t = new ofTouchEventArgs(touch);
		///     lua_getglobal(lua, "touchDown");
		///     lua.pushobject("ofTouchArgEvents", t, true); // true: let lua delete it
		///     lua_pcall(lua, 1, 0, 0);
		///
		bool pushobject(const string &typeName, void *object, bool manageMemory=true);
	
    protected:
		
		/// lua stack top index
		static const int LUA_STACK_TOP = -1;
		
		/// returns true if an object exists
		bool exists(const string& name, int type);
		bool exists(const unsigned int index, int type);
		
		/// returns true is an object is of a certain type
		bool checkType(int stackIndex, int type);
	
		/// try to get value of a given type off of the top of the stack
		template <class T> T totype(int stackIndex, int type, T defaultValue);
	
		/// read a value from the state
		template <class T> T read(const string& name, int type, T defaultVal);
		template <class T> T read(const unsigned int index, int type, T defaultVal);

		/// read a table into a vector
		template <class T> void readVector(const string& name, vector<T>& v, int type, T defaultValue);
		template <class T> void readVector(const unsigned int index, vector<T>& v, int type, T defaultValue);
		template <class T> void readVectorHelper(vector<T>& v, int type, T defaultValue);
	
		/// set a value of a given type
		template <class T> void settype(const string& name, int type, T value);
		template <class T> void settype(unsigned int index, int type, T value);
	
		/// write a value to the state
		template <class T> void write(const string& name, int type, T value);
		template <class T> void write(const unsigned int index, int type, T value);
		
		/// write a vector into a table
		template <class T> void writeVector(const string& name, int type, vector<T>& v);
		template <class T> void writeVector(const unsigned int index, int type, vector<T>& v);
		template <class T> void writeVectorHelper(int type, vector<T>& v);
	
		/// print a table
		void printTable(int stackIndex, int numTabs);
		
		/// writer a table to a buffer (values only)
		void writeTable(int stackIndex, ofxLuaFileWriter& writer, bool recursive);
	
		/// called when lua state panics (hard crash)
		static int atPanic(lua_State *L);
	
		lua_State* L = NULL;       //< the lua state object
		bool abortOnError = false; //< close the lua state on error?
	
		struct TableIndex {
			int type;           //< LUA_TSTRING or LUA_TNUMBER
			string name;        //< name index
			unsigned int index; //< number index
			operator string() {
				if(type == LUA_TNUMBER) {
					return to_string(index);
				}
				return name;
			}
		};
		vector<TableIndex> tables;  //< the currently open table stack
	
		ofEvent<string> errorEvent; //< error event object, string is error msg
		string errorMessage = "";   //< current error message
};

// TEMPLATE FUNCTIONS

// TYPES

template <class T>
T ofxLua::totype(int stackIndex, int type, T defaultValue) { return defaultValue; }

template <class T>
void ofxLua::settype(const string& name, int type, T value) {}

template <class T>
void ofxLua::settype(unsigned int index, int type, T value) {}

// READ

template <class T>
T ofxLua::read(const string& name, int type, T defaultValue) {
	if(!isValid()) {
		return defaultValue;
	}
	
	// global variable?
	T ret = defaultValue;
	if(tables.size() == 0) {
		lua_getglobal(L, name.c_str());
		if(lua_type(L, LUA_STACK_TOP) == type) {
			ret = totype(LUA_STACK_TOP, type, defaultValue);
		}
		else {
			ofLogWarning("ofxLua") << "Couldn't read global var: \"" << name << "\"";
		}
		lua_pop(L, 1);
	}
	
	// in a table namespace
	else {
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't read var: \"" << name << "\""
				<< ", top of stack is not a table";
			return ret;
		}
		lua_getfield(L, LUA_STACK_TOP, name.c_str());
		if(lua_type(L, LUA_STACK_TOP) == type) {
			ret = totype(LUA_STACK_TOP, type, defaultValue);
		}
		else {
			ofLogWarning("ofxLua") << "Couldn't read table var: \"" << name << "\"";
		}
		lua_pop(L, 1);
	}
	
	return ret;
}

template <class T>
T ofxLua::read(const unsigned int index, int type, T defaultValue) {
	if(!isValid()) {
		return defaultValue;
	}
	
	// global variable?
	T ret = defaultValue;
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't read var by index, no open tables";
		return defaultValue;
	}
	
	// in a table namespace
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't read var " << index
			<< ", top of stack is not a table";
		return defaultValue;
	}
	lua_pushinteger(L, index);
	lua_gettable(L, LUA_STACK_TOP-1);
	if(lua_type(L, LUA_STACK_TOP) == type) {
		ret = totype(LUA_STACK_TOP, type, defaultValue);
	}
	else {
		ofLogWarning("ofxLua") << "Couldn't read table var " << index;
	}
	lua_pop(L, 1);
	
	return ret;
}

template <class T>
void ofxLua::readVector(const string& name, vector<T>& v, int type, T defaultValue) {
	if(!pushTable(name)) {
		return;
	}
	readVectorHelper(v, type, defaultValue);
	popTable();
}

template <class T>
void ofxLua::readVector(const unsigned int index, vector<T>& v, int type, T defaultValue) {
	if(!pushTable(index)) {
		return;
	}
	readVectorHelper(v, type, defaultValue);
	popTable();
}

template <class T>
void ofxLua::readVectorHelper(vector<T>& v, int type, T defaultValue) {
	if(!isValid()) {
		return;
	}
	
	v.clear();
	
	if(!lua_istable(L, LUA_STACK_TOP)) {
		string tname = "unknown";
		if(!tables.empty()) {
			tname = tables.back();
		}
		ofLogWarning("ofxLua") << "Couldn't read table \"" << tname << "\", stack var is not a table";
		ofLogWarning("ofxLua") << "Did you forget to call pushTable()?";
	}
	
	// push temp key & value onto the stack since lua_next will overwrite them
	lua_pushvalue(L, LUA_STACK_TOP); // stack: -1 => table
	lua_pushnil(L); // stack : -2 => table; -1 => nil;
	
	// iterate through elements, pushes key and value onto stack
	// stack: -3 => table; -2 => key; -1 => value
	while(lua_next(L, -2)) {
		if(lua_type(L, -1) == type) {
			v.push_back(totype(-1, type, defaultValue));
		}
		else {
			string tname = "unknown";
			if(!tables.empty()) {
				tname = tables.back();
			}
			ofLogWarning("ofxLua") << "Couldn't convert type when reading table \"" << tname << "\"";
		}
		lua_pop(L, 1); // stack: -2 => table; -1 => key
	}
	
	// stack: -1 => table
	lua_pop(L, 1); // stack:
}

// WRITE

template <class T>
void ofxLua::write(const string& name, int type, T value) {
	if(!isValid()) {
		return;
	}
	
	// global variable?
	if(tables.empty()) {
		lua_pushglobaltable(L);
		settype<T>(name, type, value);
		lua_pop(L, 1);
	}
	
	// in a table namespace
	else {
		if(!lua_istable(L, LUA_STACK_TOP)) {
			ofLogWarning("ofxLua") << "Couldn't write var: \"" << name << "\""
				<< ", top of stack is not a table";
			return;
		}
		settype<T>(name, type, value);
	}
}

template <class T>
void ofxLua::write(const unsigned int index, int type, T value) {
	
	// global variable?
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write global var by index, no open tables";
		return;
	}
	
	// in a table namespace
	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't write var at index " << index
			<< ", top of stack is not a table";
		return;
	}
	
	settype<T>(index, type, value);
}

template <class T>
void ofxLua::writeVector(const string& name, int type, vector<T>& v) {
	if(!pushTable(name)) {
		return;
	}
	writeVectorHelper(type, v);
	popTable();
}

template <class T>
void ofxLua::writeVector(const unsigned int index, int type, vector<T>& v) {
	if(!pushTable(index)) {
		return;
	}
	writeVectorHelper(type, v);
	popTable();
}

template <class T>
void ofxLua::writeVectorHelper(int type, vector<T>& v) {

	// global variable?
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write table vector, no open tables";
		return;
	}
	string tname = tables.back();
	
	if(v.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write table \"" << tname << "\", vector is empty";
		return;
	}

	if(!lua_istable(L, LUA_STACK_TOP)) {
		ofLogWarning("ofxLua") << "Couldn't write table \"" << tname << "\", stack var is not a table";
	}
	
	// remove all elements
	clearTable();
	
	// add new variables
	for(size_t i = 0; i < v.size(); ++i) {
		settype<T>(i+1, type, v[i]);
	}
}
