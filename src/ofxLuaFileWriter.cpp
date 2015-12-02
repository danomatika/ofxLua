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
	tables.push_back(tableName);
}

void ofxLuaFileWriter::beginTable(const unsigned int tableIndex) {
	if(tables.empty()) {
		buffer << tableIndex << " = {}" << endl;
	}
	else {
		writeTablePath();
		buffer << "[" << tableIndex << "] = {}" << endl;
	}
	tables.push_back(ofToString(tableIndex));
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
	write<bool>(name, BOOLEAN, value);
}

void ofxLuaFileWriter::writeBool(const unsigned int index, bool value) {
	write<bool>(index, BOOLEAN, value);
}

void ofxLuaFileWriter::writeFloat(const string& name, float value) {
	write<float>(name, NUMBER, value);
}

void ofxLuaFileWriter::writeFloat(const unsigned int index, float value) {
	write<float>(index, NUMBER, value);
}

void ofxLuaFileWriter::writeString(const string& name, string value) {
	write<string>(name, STRING, value);
}

void ofxLuaFileWriter::writeString(const unsigned int index, string value) {
	write<string>(index, STRING, value);
}

void ofxLuaFileWriter::writeBoolVector(const string& tableName, vector<bool>& v) {
	writeVector<bool>(tableName, BOOLEAN, v);
}

void ofxLuaFileWriter::writeBoolVector(const unsigned int index, vector<bool>& v) {
	writeVector<bool>(index, BOOLEAN, v);
}

void ofxLuaFileWriter::writeFloatVector(const string& tableName, vector<float>& v) {
	writeVector<float>(tableName, NUMBER, v);
}

void ofxLuaFileWriter::writeFloatVector(const unsigned int index, vector<float>& v) {
	writeVector<float>(index, NUMBER, v);
}

void ofxLuaFileWriter::writeStringVector(const string& tableName, vector<string>& v) {
	writeVector<string>(tableName, STRING, v);
}

void ofxLuaFileWriter::writeStringVector(const unsigned int index, vector<string>& v) {
	writeVector<string>(index, STRING, v);
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

template <> void ofxLuaFileWriter::writetype<float>(int type, float value) {
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
	buffer << tables[0];
	for(int i = 1; i < tables.size(); ++i) {
		buffer << "." << tables[i];
	}
}
