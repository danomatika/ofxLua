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
	
	// bind the example OF api to lua
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
	ofDrawBitmapString("use <- & -> to change between scripts", 10, ofGetHeight()-22);
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
			// exit, reinit the lua state, and reload the current script
			lua.scriptExit();
			lua.init();
			lua.bind<ofWrapper>();
			lua.doScript(scripts[currentScript]);
			lua.scriptSetup();
			break;
	
		case OF_KEY_LEFT:
			currentScript--;
			if(currentScript < 0)
				currentScript = scripts.size()-1;
			// exit, reinit the lua state, and load the prev script
			lua.scriptExit();
			lua.init();
			lua.bind<ofWrapper>();
			lua.doScript(scripts[currentScript]);
			lua.scriptSetup();
			break;
			
		case OF_KEY_RIGHT:
			currentScript++;
			if(currentScript > scripts.size()-1)
				currentScript = 0;
			// exit, reinit the lua state, and load the next script
			lua.scriptExit();
			lua.init();
			lua.bind<ofWrapper>();
			lua.doScript(scripts[currentScript]);
			lua.scriptSetup();
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
