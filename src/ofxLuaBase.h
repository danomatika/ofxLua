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
#include "ofLog.h"

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
        
//		/// init the lua state
//		///
//		/// set abortOnError to true if you want the lua state to be cleared
//		/// when an error ocurrs
//		///
//		/// set openLibs to false if you don't want to load the
//		/// standard lua libs (math, io, string, etc)
//		///
//		/// note: calls clear if the state has already been inited
//		///
//		bool init(bool abortOnError=false, bool openLibs=true);
//		
//		/// clears current state
//		///
//		/// note: this also clears all bindings, make sure to call bind()
//		///		  again when reiniting
//		///
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
		
		bool variableExists(const std::string& name);
		bool numberExists(const std::string& name);
		
		bool boolExists(const std::string& name);
		bool intExists(const std::string& name);
		bool uintExists(const std::string& name);
		bool floatExists(const std::string& name);
		bool stringExists(const std::string& name);
		
		bool functionExists(const std::string& name);
		bool tableExists(const std::string& name);
		
		/// \section Table Operations
		
		bool pushTable(const std::string& tableName, bool isGlobal=false);
		void popTable();
		void popAllTables();
		
		unsigned int tableSize();
		unsigned int tableSize(const std::string& tableName);
		
		/// print the current table
		void printTable();
		
		/// \section Reading
		
		bool readBool(const std::string& name, bool defaultValue=false);
		int readInt(const std::string& name, int devaultValue=0);
		unsigned int readUInt(const std::string& name, unsigned int devaultValue=0);
		float readFloat(const std::string& name, float devaultValue=0.0f);
		std::string readString(const std::string& name, const std::string& defaultValue="");
		
		void readBoolVector(const std::string& tableName, std::vector<bool>& array);
		void readIntVector(const std::string& tableName, std::vector<int>& array);
		void readUIntVector(const std::string& tableName, std::vector<unsigned int>& array);
		void readFloatVector(const std::string& tableName, std::vector<float>& array);
		void readStringVector(const std::string& tableName, std::vector<std::string>& array);
		
		/// \section Writing
		
//		void setBool(const std::string& name, bool value);
//		void setInt(const std::string& name, int value);
//		void setUInt(const std::string& name, unsigned int value);
//		void setFloat(const std::string& name, float value);
//		void setString(const std::string& name, const std::string value);
//		
//		void setBoolVector(const std::string& tableName, std::vector<bool>& array);
//		void setIntVector(const std::string& tableName, std::vector<int>& array);
//		void setUIntVector(const std::string& tableName, std::vector<unsigned int>& array);
//		void setFloatVector(const std::string& tableName, std::vector<float>& array);
//		void setStringVector(const std::string& tableName, std::vector<std::string>& array);
        		
    protected:
		
		// add some defines since lua only has LUA_TNUMBER,
		// should be far enough away from lua types (-1 to 8 in Lua 5)
		static const int LUA_TINTEGER = 0x12345678;
		static const int LUA_TUINTEGER = 0x87654321;
		static const int LUA_TFLOAT = 0x12344321;
		
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
		
		/// print a table
		void printTable(luabind::object table, int numTabs);
		
//		/// send a lua error message to ofLog and any listeners
		virtual void errorOccurred(const std::string& msg);
//		
//		/// called when lua state panics
		static int atPanic(lua_State *L);
	
		lua_State* L;							//< the lua state object
		bool bAbortOnError;						//< close the lua state on error?
		std::vector<std::string> tables;		//< the currently open table names 
};

// TEMPLATE FUNCTIONS

template <class T>
T ofxLuaBase::read(const std::string& name, T defaultVal) {
	
	// global variable?
	if(tables.size() == 0) {
	
		lua_getglobal(L, name.c_str());
		luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
		if(!o) {
			ofLogWarning("ofxLua") << "Couldn't read global var: \"" << name << "\"";
			return defaultVal;
		}
		
		try {
			T ret = luabind::object_cast<T>(o);
			lua_pop(L, 1);
			return ret;
		}
		catch(...) {
			ofLogWarning("ofxLua") << "Couldn't convert type for global var: \"" << name << "\"";
			return defaultVal;
		}
	}
	
	// in a table namespace
	else {
	
		luabind::object o(luabind::from_stack(L, LUA_STACK_TOP));
		if(luabind::type(o) != LUA_TTABLE) {
			ofLogWarning("ofxLua") << "Couldn't read var: \"" << name << "\""
				<< ", top of stack is not a table";
			return defaultVal;
		}
		
		try {
			return luabind::object_cast<T>(o[name]);
		}
		catch(...) {
			ofLogWarning("ofxLua") << "Couldn't read table var: \"" << name << "\"";
			return defaultVal;
		}
	}
	
	return defaultVal;
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
