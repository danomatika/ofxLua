/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "AppCore.h"

//--------------------------------------------------------------
void AppCore::setup() {

	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
		
	// scripts to run
	scripts.push_back("scripts/graphicsExample.lua");
	scripts.push_back("scripts/imageLoaderExample.lua");
	scripts.push_back("scripts/polygonExample.lua");
	scripts.push_back("scripts/fontsExample.lua");
	currentScript = 0;
	
	// init the lua state
	lua.init();
	
	// listen to error events
	lua.addListener(this);
	
	// run some api tests if not on iOS
	#ifndef TARGET_IPHONE
		runTests();
	#endif
	
	// reinit the lua state, clear test data in state
	lua.init();
	
	// bind the example OF api to the lua state
	lua.bind<ofWrapper>();
	
	// run a script
	lua.doScript(scripts[currentScript]);
	
	// call the script's setup() function
	lua.scriptSetup();
}

//--------------------------------------------------------------
void AppCore::update() {
	// call the script's update() function
	lua.scriptUpdate();
}

//--------------------------------------------------------------
void AppCore::draw() {
	// call the script's draw() function
	lua.scriptDraw();
	
	ofSetColor(0);
	ofDrawBitmapString("use <- & -> (double tap on iOS) to change between scripts", 10, ofGetHeight()-22);
	ofDrawBitmapString(scripts[currentScript], 10, ofGetHeight()-10);
}

//--------------------------------------------------------------
void AppCore::exit() {
	// call the script's exit() function
	lua.scriptExit();
	
	// clear the lua state
	lua.clear();
}

//--------------------------------------------------------------
void AppCore::keyPressed(int key) {
	
	switch(key) {
	
		case 'r':
			reloadScript();
			break;
	
		case OF_KEY_LEFT:
			prevScript();
			break;
			
		case OF_KEY_RIGHT:
			nextScript();
			break;
			
		case ' ':
			lua.doString("print(\"this is a lua string saying you hit the space bar!\")");
			break;
	}
	
	lua.scriptKeyPressed(key);
}

//--------------------------------------------------------------
void AppCore::mouseMoved(int x, int y) {
	lua.scriptMouseMoved(x, y);
}

//--------------------------------------------------------------
void AppCore::mouseDragged(int x, int y, int button) {
	lua.scriptMouseDragged(x, y, button);
}

//--------------------------------------------------------------
void AppCore::mousePressed(int x, int y, int button) {
	lua.scriptMousePressed(x, y, button);
}

//--------------------------------------------------------------
void AppCore::mouseReleased(int x, int y, int button) {
	lua.scriptMouseReleased(x, y, button);
}

//--------------------------------------------------------------
void AppCore::errorReceived(string& msg) {
	cout << "got an error: " << msg << endl;
}

//--------------------------------------------------------------
void AppCore::reloadScript() {
	// exit, reinit the lua state, and reload the current script
	lua.scriptExit();
	lua.init();
	lua.bind<ofWrapper>(); // rebind
	lua.doScript(scripts[currentScript]);
	lua.scriptSetup();
}

void AppCore::nextScript() {
	currentScript++;
	if(currentScript > scripts.size()-1)
		currentScript = 0;
	reloadScript();
}

void AppCore::prevScript() {
	currentScript--;
	if(currentScript < 0)
		currentScript = scripts.size()-1;
	reloadScript();
}

//--------------------------------------------------------------
void AppCore::runTests() {

	// do tests
	//------
	ofLog();
	ofLog() << "*** BEGIN READ TEST ***";
	
	// load a script with some variables we want
	lua.doScript("variableTest.lua");
	
	// print the variables in the script manually
	ofLog() << "variableTest variables:";
	ofLog() << "	abool: " << lua.getBool("abool");
	ofLog() << "	afloat: " << lua.getFloat("afloat");
	ofLog() << "	astring: " << lua.getString("astring");
	
	// load simple table arrays by type
	stringstream line;
	
	vector<bool> boolTable;
	lua.getBoolVector("boolTable", boolTable);
	line << "	boolTable: ";
	for(int i = 0; i < boolTable.size(); ++i)
		line << boolTable[i] << " ";
	ofLog() << line.str() << "#: " << lua.tableSize("boolTable");
	line.str(""); // clear
	
	vector<float> floatTable;
	lua.getFloatVector("floatTable", floatTable);
	line << "	floatTable: ";
	for(int i = 0; i < floatTable.size(); ++i)
		line << floatTable[i] << " ";
	ofLog() << line.str() << "#: " << lua.tableSize("floatTable");
	line.str(""); // clear
	
	vector<string> stringTable;
	lua.getStringVector("stringTable", stringTable);
	line << "	stringTable: ";
	for(int i = 0; i < stringTable.size(); ++i)
		line << "\"" << stringTable[i] << "\" ";
	ofLog() << line.str() << "#: " << lua.tableSize("stringTable");
	line.str(""); // clear
	
	// try to load a mixed var table, should fail and issue warnings
	lua.getStringVector("mixedTable", stringTable);
	
	// read manually by index, remember lua indices start at 1 not 0!
	lua.pushTable("mixedTable");
	ofLog() << "mixedTable";
	for(int i = 1; i <= lua.tableSize(); ++i) {
		if(lua.isBool(i)) {
			ofLogNotice() << i << " b: " << lua.getBool(i);
		}
		else if(lua.isFloat(i)) {
			ofLogNotice() << i << " f: " << lua.getFloat(i);
		}
		else if(lua.isString(i)) {
			ofLogNotice() << i << " s: " << lua.getString(i);
		}
	}
	lua.popTable();
	
	// print the contents of the "atable" table
	lua.pushTable("atable"); // move from the global lua namespace to the "atable" table
	lua.printTable(); // print variables & tables in "atable"
	lua.popTable(); // return to the global namespace
	
	ofLog() << "*** END READ TEST ***" << endl;
	
	//------
	
	ofLog() << "*** BEGIN WRITE TEST ***";
	
	// print
	ofLog() << "values before:";
	ofLog() << "	abool: " << lua.getBool("abool");
	ofLog() << "	afloat: " << lua.getFloat("afloat");
	ofLog() << "	astring: " << lua.getString("astring");
	
	// this should throw a warning, it dosen't exist yet
	ofLog() << "	newstring: " << lua.getString("newstring");
	
	floatTable.clear();
	lua.getFloatVector("floatTable", floatTable);
	line << "	floatTable: ";
	for(int i = 0; i < floatTable.size(); ++i)
		line << floatTable[i] << " ";
	ofLog() << line.str() << "#: " << lua.tableSize("floatTable");
	line.str(""); // clear
	
	// set values
	lua.setBool("abool", false);
	lua.setFloat("afloat", 66.6);
	lua.setString("astring", "kaaaaa");
	
	// add new value
	lua.setString("newstring", "a new string");
	
	// set vector
	floatTable.clear();
	for(int i = 0; i < 10; i+=2) {
		floatTable.push_back(i);
	}
	lua.setFloatVector("floatTable", floatTable);
	
	// print again
	ofLog() << "values after:";
	ofLog() << "	abool: " << lua.getBool("abool");
	ofLog() << "	afloat: " << lua.getFloat("afloat");
	ofLog() << "	astring: " << lua.getString("astring");
	ofLog() << "	newstring: " << lua.getString("newstring");
	
	floatTable.clear();
	lua.getFloatVector("floatTable", floatTable);
	line << "	floatTable: ";
	for(int i = 0; i < floatTable.size(); ++i)
		line << floatTable[i] << " ";
	ofLog() << line.str() << "#: " << lua.tableSize("floatTable");
	line.str(""); // clear
	
	// write manually by index, remember lua indices start at 1 not 0!
	lua.pushTable("mixedTable");
	for(int i = 1; i <= lua.tableSize(); ++i) {
		if(lua.isBool(i)) {
			lua.setBool(i, true);
		}
		else if(lua.isFloat(i)) {
			lua.getFloat(i, 9999.99);
		}
		else if(lua.isString(i)) {
			lua.getString(i, "abcdefg");
		}
	}
	lua.printTable();
	lua.popTable();
	
	ofLog() << "*** END WRITE TEST ***" << endl;
	
	//------
	
	ofLog() << "*** BEGIN EXIST TEST ***";
	
	// "avar" dosen't exist
	ofLog() << "avar exists: " << lua.isFloat("avar")
		<< ", is nil: " << lua.isNil("avar");
	
	// "avar" exists and is equal to 99
	lua.setFloat("avar", 99);
	ofLog() << "avar exists: " << lua.isFloat("avar")
		<< ", is nil: " << lua.isNil("avar");
	ofLog() << "	avar: " << lua.getFloat("avar");
	
	// set "avar" to nil, it no longer exists
	lua.setNil("avar");
	ofLog() << "avar exists: " << lua.isFloat("avar")
		<< ", is nil: " << lua.isNil("avar");
	
	ofLog() << "*** END EXIST TEST ***" << endl;
	
	//------
	
	ofLog() << "*** BEGIN CLEAR TEST ***";
	
	lua.printTable("anotherTable");
	lua.clearTable("anotherTable");
	lua.printTable("anotherTable"); // should only print the name
	
	ofLog() << "*** END CLEAR TEST ***" << endl;
	
	//------
	
	ofLog() << "*** BEGIN FILE WRITER TEST ***";
	
	// write vars out into a text file
	ofxLuaFileWriter luaWriter;
	string filename = "writerTest.lua";
	luaWriter.writeComment("lua writer test");
	luaWriter.newLine();
	luaWriter.beginCommentBlock();
	luaWriter.writeLine("this is a comment block");
	luaWriter.endCommentBlock();
	luaWriter.writeBool("abool", lua.getBool("abool"));
	luaWriter.writeFloat("afloat", lua.getFloat("afloat"));
	luaWriter.writeString("astring", lua.getString("astring"));
	luaWriter.writeStringVector("stringTable", stringTable);
	
	// write a table's contents recursively into the file
	lua.writeTable("atable", luaWriter, false);
	
	// save, load, and print file
	if(luaWriter.saveToFile(filename)) {
		
		// print
		ofBuffer b = ofBufferFromFile(filename);
		while(!b.isLastLine()) {
			ofLog() << b.getNextLine();
		}
		b.clear();
		
		// try loading into lua state
		lua.doScript(filename);
		
		// delete when done
		ofFile::removeFile(filename);
	}
	
	ofLog() << "*** END FILE WRITER TEST ***" << endl;
	
	//-------
	// tests done
}
