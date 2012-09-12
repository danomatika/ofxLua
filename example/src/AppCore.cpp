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

	ofSetFrameRate(30);
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
	
	ofLogNotice() << endl << "*** BEGIN READ TEST ***";
	
	// load a script with some variables we want
	lua.doScript("variableTest.lua");
	
	// print the variables in the script manually
	ofLogNotice() << "variableTest variables:";
	ofLogNotice() << "	abool: " << lua.getBool("abool");
	ofLogNotice() << "	afloat: " << lua.getFloat("afloat");
	ofLogNotice() << "	astring: " << lua.getString("astring");
	
	// load simple table arrays by type
	stringstream line;
	
	vector<bool> boolTable;
	lua.getBoolTable("boolTable", boolTable);
	line << "	boolTable: ";
	for(int i = 0; i < boolTable.size(); ++i)
		line << boolTable[i] << " ";
	ofLogNotice() << line.str();
	line.str(""); // clear
	
	vector<float> floatTable;
	lua.getFloatTable("floatTable", floatTable);
	line << "	floatTable: ";
	for(int i = 0; i < floatTable.size(); ++i)
		line << floatTable[i] << " ";
	ofLogNotice() << line.str();
	line.str(""); // clear
	
	vector<string> stringTable;
	lua.getStringTable("stringTable", stringTable);
	line << "	stringTable: ";
	for(int i = 0; i < stringTable.size(); ++i)
		line << "\"" << stringTable[i] << "\" ";
	ofLogNotice() << line.str();
	line.str(""); // clear
	
	// try to load a mixed var table, should fail and issue warnings
	lua.getStringTable("mixedTable", stringTable);
	
	// print the contents of the "atable" table
	lua.pushTable("atable"); // move from the global lua namespace to the "atable" table
	lua.printTable(); // print variables & tables in "atable"
	lua.popTable(); // return to the global namespace
	
	ofLogNotice() << "*** END READ TEST ***" << endl;
	
	
	ofLogNotice() << "*** BEGIN WRITE TEST ***";
	
	// print
	ofLogNotice() << "values before:";
	ofLogNotice() << "	abool: " << lua.getBool("abool");
	ofLogNotice() << "	afloat: " << lua.getFloat("afloat");
	ofLogNotice() << "	astring: " << lua.getString("astring");
	
	// this should throw a warning, it dosen't exist yet
	ofLogNotice() << "	newstring: " << lua.getString("newstring");
	
	floatTable.clear();
	lua.getFloatTable("floatTable", floatTable);
	line << "	floatTable: ";
	for(int i = 0; i < floatTable.size(); ++i)
		line << floatTable[i] << " ";
	ofLogNotice() << line.str();
	line.str(""); // clear
	
	// set values
	lua.setBool("abool", false);
	lua.setFloat("afloat", 66.6);
	lua.setString("astring", "kaaaaa");
	
	// add new value
	lua.setString("newstring", "a new string");
	
	// set vector
	floatTable.clear();
	for(int i = 0; i < 4; i+=2) {
		floatTable.push_back(i);
	}
	lua.setFloatTable("floatTable", floatTable);
	
	// print again
	ofLogNotice() << "values after:";
	ofLogNotice() << "	abool: " << lua.getBool("abool");
	ofLogNotice() << "	afloat: " << lua.getFloat("afloat");
	ofLogNotice() << "	astring: " << lua.getString("astring");
	ofLogNotice() << "	newstring: " << lua.getString("newstring");
	
	floatTable.clear();
	lua.getFloatTable("floatTable", floatTable);
	line << "	floatTable: ";
	for(int i = 0; i < floatTable.size(); ++i)
		line << floatTable[i] << " ";
	ofLogNotice() << line.str();
	line.str(""); // clear
	
	ofLogNotice() << "*** END WRITE TEST ***" << endl;
	
	
	ofLogNotice() << "*** BEGIN EXIST TEST ***";
	
	// "avar" dosen't exist
	ofLogNotice() << "avar exists: " << lua.isFloat("avar");
	ofLogNotice() << "avar is nil: " << lua.isNil("avar");
	
	// "avar" exists and is equal to 99
	lua.setFloat("avar", 99);
	ofLogNotice() << "avar exists: " << lua.isFloat("avar");
	ofLogNotice() << "avar is nil: " << lua.isNil("avar");
	ofLogNotice() << "	avar: " << lua.getFloat("avar");
	
	// set "avar" to nil, it no longer exists
	lua.setNil("avar");
	ofLogNotice() << "avar exists: " << lua.isFloat("avar");
	ofLogNotice() << "avar is nil: " << lua.isNil("avar");
	
	ofLogNotice() << "*** END EXIST TEST ***" << endl;
	
	
	// bind the example OF api to the lua state
	lua.bind<ofWrapper>();
	
	// run a script as a coroutine so we don't have to reinit and rebind the
	// global state each time
	//coroutine.init(lua); //< a coroutine is a child of a lua state
	//coroutine.doScript(scripts[currentScript]);
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
void AppCore::errorReceived(const std::string& msg) {
	cout << "got an error: " << msg << endl;
}

//--------------------------------------------------------------
void AppCore::reloadScript() {
	// exit, reinit the lua state, and reload the current script
	lua.scriptExit();
	lua.init();
	lua.bind<ofWrapper>(); // rebind
	//coroutine.init(lua);
	//coroutine.doScript(scripts[currentScript]);
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
