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
#pragma once

#include "ofConstants.h"
#include "ofLog.h"

/// writes variables out to a lua text file
///
/// this is a not a scripting replacement, but a quick way to store data
///
/// this class is largely derived from the Allacrost scripting system: http://allacrost.sourceforge.net
///
class ofxLuaFileWriter {

    public:

        ofxLuaFileWriter();
		~ofxLuaFileWriter();
		
		/// save the current buffer to a file,
		/// best to name it with the ".lua" ext
		bool saveToFile(const string& filename);
		
		/// clear the buffer
		void clear();

	/// \section Write elements
	
		/// insert a new line char
		void newLine();
	
		/// writes a single line "--" comment
		void writeComment(const string& comment);
		
		/// starts and stops a multi-line comment block aka
		/// --[[
		///		some commments, etc
		/// --]]
		///
		/// note: all data written after beginCommentBlock() will be comments
		void beginCommentBlock();
		void endCommentBlock();
		
		/// write a single line of text, not variable data
		///
		/// note: don't write close comments "--]]" when in a comment block
		void writeLine(const string& comment);
		
		/// create a table, subsequent data is written as variables inside
		void beginTable(const string& tableName);
		void beginTable(const unsigned int tableIndex); //< must beginTable first
		void endTable();

	/// \section Write variables
		
		void writeBool(const string& name, bool value);
		void writeBool(const unsigned int index, bool value);
		
		void writeFloat(const string& name, float value);
		void writeFloat(const unsigned int index, float value);
		
		void writeString(const string& name, string value);
		void writeString(const unsigned int index, string value);

		void writeBoolVector(const string& tableName, vector<bool>& v);
		void writeBoolVector(const unsigned int index, vector<bool>& v);
		
		void writeFloatVector(const string& tableName, vector<float>& v);
		void writeFloatVector(const unsigned int index, vector<float>& v);
		
		void writeStringVector(const string& tableName, vector<string>& v);
		void writeStringVector(const unsigned int index, vector<string>& v);

    private:
		
		template <class T> void write(const string& name, T value, bool isString=false);
		template <class T> void write(const unsigned int index, T value, bool isString=false);

		template <class T> void writeVector(const string& tableName, vector<T> &v, bool isString=false);
		template <class T> void writeVector(const unsigned int index, vector<T> &v, bool isString=false);
		
		/// write the currently nest table paths
		void writeTablePath();
		
		/// is the given string a number aka "1", "-300.5", "+300"
		static bool isStringANumber(const string& text);
		
		bool bCommentBlock;		//< currently in a comment block?
		vector<string> tables;	//< the currently open table names
		
		stringstream buffer; //< string buffer
};

template <class T>
void ofxLuaFileWriter::write(const string& name, T value, bool isString) {
	
	// strings must be within quotes
	string quotes = "";
	if(isString) {
		quotes = "\"";
	}
	
	if(tables.empty()) {
		buffer << name << " = " << quotes << value << quotes << endl;
	}
	else {
		writeTablePath();
		buffer << "." << name << " = " << quotes << value << quotes << endl;
	}
}

template <class T>
void ofxLuaFileWriter::write(const unsigned int index, T value, bool isString) {
	
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write var to file by index, no open tables";
		return;
	}
	
	writeTablePath();
	
	// strings must be within quotes
	string quotes = "";
	if(isString) {
		quotes = "\"";
	}
	
	buffer << "[" << index << "] = " << quotes << value << quotes << endl;
}

template <class T>
void ofxLuaFileWriter::writeVector(const string& tableName, vector<T> &v, bool isString) {
	
	if(v.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write empty vector to file";
		return;
	}
	
	// strings must be within quotes
	string quotes = "";
	if(isString) {
		quotes = "\"";
	}
	
	// write name
	if(tables.empty()) {
		buffer << tableName << " = { ";
	}
	else {
		writeTablePath();
		if(isStringANumber(tableName))
			buffer << "[" << tableName << "] = { ";
		else
			buffer << "." << tableName << " = { ";
	}
	
	// write vector
	buffer << quotes << v[0] << quotes;
	for(int i = 1; i < v.size(); ++i) {
		buffer << ", " << quotes << v[i] << quotes;
	}
	buffer << " }" << endl;
}

template <class T>
void ofxLuaFileWriter::writeVector(const unsigned int index, vector<T> &v, bool isString) {
	if(tables.empty()) {
		ofLogWarning("ofxLua") << "Couldn't write vector to file by index, no open tables";
		return;
	}
	
	// strings must be within quotes
	string quotes = "";
	if(isString) {
		quotes = "\"";
	}
	
	// write name
	writeTablePath();
	buffer << "[" << index << "] = { ";
	
	// write vector
	buffer << quotes << v[0] << quotes;
	for(int i = 1; i < v.size(); ++i) {
		buffer << ", " << quotes << v[i] << quotes;
	}
	buffer << " }" << endl;
}
