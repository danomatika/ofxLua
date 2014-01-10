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
#pragma once

#include "ofConstants.h"
#include "ofEvents.h"

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

#include "ofxLuaFileWriter.h"
#include "ofxLuaTouchEvent.h"

///
/// a baseclass to receieve lua error messages,
/// useful for displaying an error message on the screen, etc
///
class ofxLuaListener {

	public :
	
		virtual void errorReceived(string& msg) = 0;
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
/// the read/write algos are largely derived from the Allacrost scripting system: http://allacrost.sourceforge.net/
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
		
		/// run a lua string, returns false on script error
		bool doString(const string& text);
		
		/// run a lua script, returns false on script error
		bool doScript(const string& script);
		
		/// get the current error message, an alternative to ofxLuaListener
		string getErrorMessage() {return errorMessage;}
		
	/// \section C++ Binding
		
		/// bind C++ functions and objects to lua
		/// this allows lua scripts to call C++ entities
		///
		/// see the luabind docs for syntax:
		///  http://www.rasterbar.com/products/luabind/docs.html
		///
		///
		///	create a static bind function in your class which contains the
		///	luabind definitions:
		///
		///	class ofWrapper {
		///
		///		public:
		///
		///			static void bind(ofxLua& lua) {
		///
		///				using namespace luabind;
		///	
		///				module(lua, "of")	// create an "of" table namespace
		///				[
		///					// bind a function
		///					def("sin", &std::sin),
		///
		///					// bind an overloaded function by specifying the 
		///					// function pointer type
		///					def("setColor", (void(*)(int)) &ofSetColor)
		///
		///					// bind a class
		///					class_<ofRectangle>("rectangle")
		///					.def(constructor<>())
		///					.def(constructor<const ofRectangle&>())
		///					.def(constructor<float,float,float,float>())
		///					.def("set", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::set)
		///					.def("set", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::set)
		///					.def_readwrite("x", &ofRectangle::x)
		///					.def_readwrite("y", &ofRectangle::y)
		///					.def_readwrite("width", &ofRectangle::width)
		///					.def_readwrite("height", &ofRectangle::height),
		///				];
		///			}
		///		};
		///
		///
		/// your class bind function will be called automatically when using the
		/// ofxLua bind function:
		///
		/// lua.bind<ofWrapper>();
		///
		///	see bindings/ofxLuaBindings.h for a much more detailed example
		///
		template<typename T> void bind() {T::bind(*this);}
		
	/// \section Listeners
		
		/// add a listener, ignores any duplicates
		void addListener(ofxLuaListener* listener);
		
		/// remove a listener
		void removeListener(ofxLuaListener* listener);
		
	/// \section Util
		
		/// print the tables in the global scope
		void printGlobals();
		
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
		void scriptKeyReleased(int key);
		void scriptMouseMoved(int x, int y );
		void scriptMouseDragged(int x, int y, int button);
		void scriptMousePressed(int x, int y, int button);
		void scriptMouseReleased(int x, int y, int button);
	
		// mobile
		void scriptTouchDown(ofTouchEventArgs &touch);
		void scriptTouchMoved(ofTouchEventArgs &touch);
		void scriptTouchUp(ofTouchEventArgs &touch);
		void scriptTouchDoubleTap(ofTouchEventArgs &touch);
		void scriptTouchCancelled(ofTouchEventArgs &touch);
		
	/// \section Variables
		
		/// check if a variable exists as a certain type in the lua state
		///
		/// note: pushTable must have been called, when using the table index
		
		bool isBool(const string& name);
		bool isBool(const unsigned int index);
		
		bool isFloat(const string& name);
		bool isFloat(const unsigned int index);
		
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
		
		bool pushTable(const string& tableName);
		bool pushTable(const unsigned int& tableIndex); // must pushTable first
		void popTable();
		void popAllTables();
		
		/// get the size of a table
		unsigned int tableSize(); //< current table
		unsigned int tableSize(const string& tableName); //< table in current table
		
		/// print a table
		void printTable(); //< current table
		void printTable(const string& tableName); //< table in current table
		
		/// clear a table, removes all objects in the table
		void clearTable(); //< current table
		void clearTable(const string& tableName); //< table in current table
		
	/// \section Reading
		
		/// note: integer indices start with 1!
		
		/// get variables
		bool getBool(const string& name, bool defaultValue=false);
		bool getBool(const unsigned int index, bool defaultValue=false);
		
		float getFloat(const string& name, float devaultValue=0.0f);
		float getFloat(const unsigned int index, float devaultValue=0.0f);
		
		string getString(const string& name, const string& defaultValue="");
		string getString(const unsigned int index, const string& defaultValue="");
		
		/// get a vector from a table, prints warnings on wrong type
		///
		/// note: clears given vector before reading lua vars
		void getBoolVector(const string& tableName, vector<bool>& v);
		void getBoolVector(const unsigned int tableIndex, vector<bool>& v);
		
		void getFloatVector(const string& tableName, vector<float>& v);
		void getFloatVector(const unsigned int tableIndex, vector<float>& v);
		
		void getStringVector(const string& tableName, vector<string>& v);
		void getStringVector(const unsigned int tableIndex, vector<string>& v);
		
	/// \section Writing
		
		/// note: integer indices start with 1!
		
		/// set variables, creates if not existing
		void setBool(const string& name, bool value);
		void setBool(const unsigned int index, bool value);
		
		void setFloat(const string& name, float value);
		void setFloat(const unsigned int index, float value);
		
		void setString(const string& name, const string value);
		void setString(const unsigned int index, const string value);

		/// set a table from a vector, table must exist
		void setBoolVector(const string& tableName, vector<bool>& v);
		void setBoolVector(const unsigned int tableIndex, vector<bool>& v);
		
		void setFloatVector(const string& tableName, vector<float>& v);
		void setFloatVector(const unsigned int tableIndex, vector<float>& v);
		
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
        		
    protected:
		
		// lua stack top index
		static const int LUA_STACK_TOP = -1;
		
		/// returns true if an object exists
		bool exists(const string& name, int type);
		bool exists(const unsigned int index, int type);
		
		/// returns true is an object is of a certain type
		bool checkType(int type, luabind::object& object);
		
		/// read a value from the state
		template <class T> T read(const string& name, T defaultVal);
		template <class T> T read(const unsigned int index, T defaultVal);
		
		/// read a table into a vector
		template <class T> void readVector(const string& name, vector<T>& v);
		template <class T> void readVector(const unsigned int index, vector<T>& v);
		template <class T> void readVectorHelper(vector<T>& v);
		
		/// write a value to the state
		template <class T> void write(const string& name, T value);
		template <class T> void write(const unsigned int index, T value);
		
		/// write a vector into a table
		template <class T> void writeVector(const string& name, vector<T>& v);
		template <class T> void writeVector(const unsigned int index, vector<T>& v);
		template <class T> void writeVectorHelper(vector<T>& v);
		
		/// print a table
		void printTable(luabind::object table, int numTabs);
		
		/// writer a table to a buffer (values only)
		void writeTable(luabind::object table, ofxLuaFileWriter& writer, bool recursive);
		
		/// send a lua error message to ofLog and any listeners
		virtual void errorOccurred(string& msg);
		
		/// called when lua state panics
		static int atPanic(lua_State *L);
	
		lua_State* L;			//< the lua state object
		bool bAbortOnError;		//< close the lua state on error?
		vector<string> tables;	//< the currently open table names		
		ofEvent<string> errorEvent; //< error event object, string is error msg
		string errorMessage; //< current error message
};

// TEMPLATE FUNCTIONS

// READ

template <class T>
T ofxLua::read(const string& name, T defaultValue) {
	
	// global variable?
	if(tables.size() == 0) {
		luabind::object o(luabind::from_stack(L, LUA_GLOBALSINDEX));
		try {
			return luabind::object_cast<T>(o[name]);
		}
		catch(...) {
			ofLogWarning("ofxLua") << "Couldn't read global var: \"" << name << "\"";
			return defaultValue;
		}
	}
	
	// in a table namespace
	else {
		luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(o) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Couldn't read var: \"" << name << "\""
				<< ", top of stack is not a table";
			return defaultValue;
		}
		
		try {
			return luabind::object_cast<T>(o[name]);
		}
		catch(...) {
			ofLogWarning("ofxLua") << "Couldn't read table var: \"" << name << "\"";
			return defaultValue;
		}
	}
	
	return defaultValue;
}

template <class T>
T ofxLua::read(const unsigned int index, T defaultValue) {
	
	// global variable?
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't read var by index, no open tables";
		return defaultValue;
	}
	
	// in a table namespace
	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't read var " << index
			<< ", top of stack is not a table";
		return defaultValue;
	}
	
	try {
		return luabind::object_cast<T>(o[index]);
	}
	catch(...) {
		ofLogWarning("ofxLua") << "Couldn't read table var " << index;
		return defaultValue;
	}
	
	return defaultValue;
}

template <class T>
void ofxLua::readVector(const string& name, vector<T>& v) {
	if(!pushTable(name))
		return;
	readVectorHelper(v);
	popTable();
}

template <class T>
void ofxLua::readVector(const unsigned int index, vector<T>& v) {
	if(!pushTable(index))
		return;
	readVectorHelper(v);
	popTable();
}

template <class T>
void ofxLua::readVectorHelper(vector<T>& v) {

	v.clear();

	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
		string tname = "unknown";
		if(!tables.empty()) {
			tname = tables.back();
		}
		ofLogWarning("ofxLua") << "Couldn't read table \"" << tname
			<< "\", stack var is not a table";
		ofLogWarning("ofxLua") << "Did you forget to call pushTable()?";
	}

	// iterate through table
	for(luabind::iterator iter(o), end; iter != end; iter++) {
		try {
			v.push_back(luabind::object_cast<T>((*iter)));
		}
		catch(...) {
			string tname = "unknown";
			if(!tables.empty()) {
				tname = tables.back();
			}
			ofLogWarning("ofxLua") << "Couldn't convert type when reading table \""
				<< tname << "\"";
		}
	}
}

// WRITE

template <class T>
void ofxLua::write(const string& name, T value) {
	
	luabind::object* table = NULL;
	
	// global variable?
	if(tables.empty()) {
		table = new luabind::object(luabind::from_stack(L, LUA_GLOBALSINDEX));
		if(!table) {
			ofLogWarning("ofxLua") << "Couldn't write global var: \"" << name << "\"";
			return;
		}
	}
	
	// in a table namespace
	else {
		table = new luabind::object(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(*table) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Couldn't write var: \"" << name << "\""
				<< ", top of stack is not a table";
			delete(table);
			return;
		}
	}
	
	// overwrites or adds new var if not existing
	luabind::settable(*table, name, value);
	delete(table);
}

template <class T>
void ofxLua::write(const unsigned int index, T value) {
	
	// global variable?
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write global var by index, no open tables";
		return;
	}
	
	// in a table namespace
	luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(table) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't write var at index " << index
			<< ", top of stack is not a table";
		delete(table);
		return;
	}
	
	// overwrites or adds new var if not existing
	luabind::settable(table, index, value);
}

template <class T>
void ofxLua::writeVector(const string& name, vector<T>& v) {
	if(!pushTable(name))
		return;
	writeVectorHelper(v);
	popTable();
}

template <class T>
void ofxLua::writeVector(const unsigned int index, vector<T>& v) {
	if(!pushTable(index))
		return;
	writeVectorHelper(v);
	popTable();
}

template <class T>
void ofxLua::writeVectorHelper(vector<T>& v) {

	string tname = "unknown";
	if(!tables.empty()) {
		tname = tables.back();
	}

	if(v.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write table \"" << tname
			<< "\", vector is empty";
		return;
	}

	luabind::object table(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(table) != LUA_TTABLE) {
		ofLogWarning("ofxLua") << "Couldn't write table \"" << tname
			<< "\", stack var is not a table";
	}

	// clear the table
	for(luabind::iterator iter(table), end; iter != end; iter++) {
		*iter = luabind::nil;
	}
	
	// add values
	for(int i = 0; i < v.size(); ++i) {
		luabind::settable(table, i+1, v[i]);
	}
}
