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
#include "ofMain.h"
#include "ofUtils.h"

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
///	base for a Lua interpreter instance, do not use directly
///
///	references:
///		- lua api http://pgl.yoyo.org/luai/i/_
///		- luabind docs http://www.rasterbar.com/products/luabind/docs.html
///		- luabind C++ tutorial http://www.gandogames.com/2011/01/tutorial-using-luabind-to-integrate-lua-with-cc-pt-2/
///		- call a lua func from C++ http://cc.byexamples.com/2008/07/15/calling-lua-function-from-c/
///		- bindling lua and ogre3d http://www.codeproject.com/KB/graphics/luabindLuaAndOgre3d.aspx
///
class ofxLuaBase {
	
	public :

		ofxLuaBase();
		virtual ~ofxLuaBase();
        
		/// clears current state
		///
		/// note: this also clears all bindings, make sure to call bind()
		///		  again when reiniting
		///
		void clear();
		
		/// is this state valid? (inited, not aborted, etc)
		bool isValid();
		
		/// is this state a lua thread?
		virtual bool isThread() = 0;
		
		/// get/set abort on error
		/// if abort on error is true, the state is closed when an error ocurrs
		bool getAbortOnError()				{return bAbortOnError;}
		void setAbortOnError(bool abort)	{bAbortOnError = abort;}
		
		/// \section Running Lua code
		
		/// run a lua string
		bool doString(const std::string& text);
		
		/// run a lua script
		bool doScript(const std::string& script);
		
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
		
		/// \section Variables
		
		/// check if variables, functions, tables, etc exist in the lua state
		///
		/// these can also be used to check object type
		
		//bool variableExists(const std::string& name);
		
		bool isBool(const std::string& name);
		bool isFloat(const std::string& name);
		bool isString(const std::string& name);
		
		bool isFunction(const std::string& name);
		bool isTable(const std::string& name);
		
		/// check explictly if something *dosen't* exist
		bool isNil(const std::string& name);
		
		/// \section Table Operations
		
		bool pushTable(const std::string& tableName, bool isGlobal=false);
		void popTable();
		void popAllTables();
		
		/// size of current table
		unsigned int tableSize();
		
		/// size of tableName in current table
		unsigned int tableSize(const std::string& tableName);
		
		/// print the current table
		void printTable();
		
		/// \section Reading
		
		/// get variables
		bool getBool(const std::string& name, bool defaultValue=false);
		float getFloat(const std::string& name, float devaultValue=0.0f);
		std::string getString(const std::string& name, const std::string& defaultValue="");
		
		/// get an vector from a table, prints warnings on wrong type
		void getBoolTable(const std::string& tableName, std::vector<bool>& array);
		void getFloatTable(const std::string& tableName, std::vector<float>& array);
		void getStringTable(const std::string& tableName, std::vector<std::string>& array);
		
		//void getTable(const std::string& tableName, ofxLuaTable& table);
		
		/// \section Writing
		
		/// set variables, creates if not existing
		void setBool(const std::string& name, bool value);
		void setFloat(const std::string& name, float value);
		void setString(const std::string& name, const std::string value);

		/// set a table from a vector, table must exist
		///
		/// tries to match indexes, drops values if either table or vector are too short
		/// it's up to you to make sure the table is of the right type and size
		void setBoolTable(const std::string& tableName, std::vector<bool>& array);
		void setFloatTable(const std::string& tableName, std::vector<float>& array);
		void setStringTable(const std::string& tableName, std::vector<std::string>& array);
		
		/// set a variable or table to nil, essentially deleting it from the state
		void setNil(const std::string& name);
        		
    protected:
		
		// lua stack top index
		static const int LUA_STACK_TOP = -1;
		
		/// returns true if an object exists
		bool exists(const std::string& name, int type);
		
		/// returns true is an object is of a certain type
		bool checkType(int type, luabind::object& object);
		
		/// read a value from the state
		template <class T>
		T read(const std::string& name, T defaultVal);
		
		/// read a table into a vector
		template <class T>
		void readVector(const std::string& name, std::vector<T>& v);
		template <class T>
		void readVectorHelper(std::vector<T>& v);
		
		/// write a value to the state
		template <class T>
		void write(const std::string& name, T value);
		
		/// write a vector into a table
		template <class T>
		void writeVector(const std::string& name, std::vector<T>& v);
		template <class T>
		void writeVectorHelper(std::vector<T>& v);
		
		/// print a table
		void printTable(luabind::object table, int numTabs);
		
		/// send a lua error message to ofLog and any listeners
		virtual void errorOccurred(const std::string& msg);
		
		/// called when lua state panics
		static int atPanic(lua_State *L);
	
		lua_State* L;							//< the lua state object
		bool bAbortOnError;						//< close the lua state on error?
		std::vector<std::string> tables;		//< the currently open table names 
};

// TEMPLATE FUNCTIONS

// READ

template <class T>
T ofxLuaBase::read(const std::string& name, T defaultValue) {
	
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
void ofxLuaBase::readVector(const std::string& name, std::vector<T>& v) {
	if(!pushTable(name))
		return;
	readVectorHelper(v);
	popTable();
}

template <class T>
void ofxLuaBase::readVectorHelper(std::vector<T>& v) {

	v.clear();

	luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
	if(luabind::type(o) != LUA_TTABLE) {
		std::string tname = "unknown";
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
void ofxLuaBase::write(const std::string& name, T value) {
	
	luabind::object* o = NULL;
	
	// global variable?
	if(tables.size() == 0) {
		o = new luabind::object(luabind::from_stack(L, LUA_GLOBALSINDEX));
		if(!o) {
			ofLogWarning("ofxLua") << "Couldn't write global var: \"" << name << "\"";
			return;
		}
	}
	
	// in a table namespace
	else {
		o = new luabind::object(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(*o) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Couldn't write var: \"" << name << "\""
				<< ", top of stack is not a table";
			ofLogWarning("ofxLua") << "Did you forget to call pushTable()?";
			delete(o);
			return;
		}
	}
	
	// overwrites or adds new var if not existing
	luabind::settable(*o, name, value);

	delete(o);
}

template <class T>
void ofxLuaBase::writeVector(const std::string& name, std::vector<T>& v) {
	if(!pushTable(name))
		return;
	writeVectorHelper(v);
	popTable();
}

template <class T>
void ofxLuaBase::writeVectorHelper(std::vector<T>& v) {

	std::string tname = "unknown";
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
		ofLogWarning("ofxLua") << "Did you forget to call pushTable()?";
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
