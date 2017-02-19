/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "ofxLuaFileWriter.h"

#include "ofUtils.h"

//------------------------------------------------------------------------------
ofxLuaFileWriter::ofxLuaFileWriter() {
	bCommentBlock = false;
}

//------------------------------------------------------------------------------
ofxLuaFileWriter::~ofxLuaFileWriter() {}

//------------------------------------------------------------------------------
bool ofxLuaFileWriter::saveToFile(const string& filename) {
	ofBuffer b(buffer);
	return ofBufferToFile(ofToDataPath(filename), b);
}

//------------------------------------------------------------------------------
void ofxLuaFileWriter::clear() {
	buffer.clear();
	tables.clear();
}

//------------------------------------------------------------------------------
void ofxLuaFileWriter::newLine() {
	buffer << endl;
}

void ofxLuaFileWriter::writeComment(const string& comment) {
	buffer << "-- " << comment << endl;
}

void ofxLuaFileWriter::beginCommentBlock() {
	if(bCommentBlock) {
		ofLogWarning("ofxLua") << "Comment block already begun";
		return;
	}
	bCommentBlock = true;
	buffer << "--[[" << endl;
}

void ofxLuaFileWriter::endCommentBlock() {
	if(!bCommentBlock) {
		ofLogWarning("ofxLua") << "Comment block not begun";
		return;
	}
	bCommentBlock = false;
	buffer << "--]]" << endl;
}

void ofxLuaFileWriter::writeLine(const string& line) {
	buffer << line << endl;
}

void ofxLuaFileWriter::beginTable(const string& tableName) {
	if(tables.empty()) {
		buffer << tableName << " = {}" << endl;
	}
	else {
		writeTablePath();
		buffer << "." << tableName << " = {}" << endl;
	}
	tables.push_back({LUA_TSTRING, tableName, 0});
}

void ofxLuaFileWriter::beginTable(const unsigned int tableIndex) {
	if(tables.empty()) {
		buffer << tableIndex << " = {}" << endl;
	}
	else {
		writeTablePath();
		buffer << "[" << tableIndex << "] = {}" << endl;
	}
	tables.push_back({LUA_TNUMBER, "", (unsigned int)tableIndex});
}

void ofxLuaFileWriter::endTable() {
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "No tables to end, call beginTable";
	}
	else {
		tables.pop_back();
	}
}

//------------------------------------------------------------------------------
void ofxLuaFileWriter::writeBool(const string& name, bool value) {
	write<bool>(name, LUA_TBOOLEAN, value);
}

void ofxLuaFileWriter::writeBool(const unsigned int index, bool value) {
	write<bool>(index, LUA_TBOOLEAN, value);
}

void ofxLuaFileWriter::writeNumber(const string& name, lua_Number value) {
	write<lua_Number>(name, LUA_TNUMBER, value);
}

void ofxLuaFileWriter::writeNumber(const unsigned int index, lua_Number value) {
	write<lua_Number>(index, LUA_TNUMBER, value);
}

void ofxLuaFileWriter::writeString(const string& name, string value) {
	write<string>(name, LUA_TSTRING, value);
}

void ofxLuaFileWriter::writeString(const unsigned int index, string value) {
	write<string>(index, LUA_TSTRING, value);
}

void ofxLuaFileWriter::writeBoolVector(const string& tableName, vector<bool>& v) {
	writeVector<bool>(tableName, LUA_TBOOLEAN, v);
}

void ofxLuaFileWriter::writeBoolVector(const unsigned int index, vector<bool>& v) {
	writeVector<bool>(index, LUA_TBOOLEAN, v);
}

void ofxLuaFileWriter::writeNumberVector(const string& tableName, vector<lua_Number>& v) {
	writeVector<lua_Number>(tableName, LUA_TNUMBER, v);
}

void ofxLuaFileWriter::writeNumberVector(const unsigned int index, vector<lua_Number>& v) {
	writeVector<lua_Number>(index, LUA_TNUMBER, v);
}

void ofxLuaFileWriter::writeStringVector(const string& tableName, vector<string>& v) {
	writeVector<string>(tableName, LUA_TSTRING, v);
}

void ofxLuaFileWriter::writeStringVector(const unsigned int index, vector<string>& v) {
	writeVector<string>(index, LUA_TSTRING, v);
}

// PRIVATE

//------------------------------------------------------------------------------
template <> void ofxLuaFileWriter::writetype<bool>(int type, bool value) {
	buffer << (value ? "true" : "false");
}

// catch vector<bool> internal type since it isn't actually a bool
template <> void ofxLuaFileWriter::writetype<vector<bool>::reference>(int type, vector<bool>::reference value) {
	buffer << ((bool)value ? "true" : "false");
}

template <> void ofxLuaFileWriter::writetype<lua_Number>(int type, lua_Number value) {
	buffer << value;
}

template <> void ofxLuaFileWriter::writetype<string>(int type, string value) {
	buffer << "\"" << value << "\"";
}

//------------------------------------------------------------------------------
// writes path for all open tables ie "t1.t2[3]"
void ofxLuaFileWriter::writeTablePath() {
	if(tables.empty()) {
		return;
	}
	buffer << (string)tables[0];
	for(int i = 1; i < tables.size(); ++i) {
		if(tables[i].type == LUA_TSTRING) {
			buffer << "." << (string)tables[i];
		}
		else {
			buffer << "[" << (string)tables[i] << "]";
		}
	}
}
