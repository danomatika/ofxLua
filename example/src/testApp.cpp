#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

	ofSetVerticalSync(true);
	ofSetLogLevel("ofxLua", OF_LOG_VERBOSE);
		
	// scripts to run
	//scripts.push_back("scripts/functionTest.lua");
	scripts.push_back("scripts/objectTest.lua");
	scripts.push_back("scripts/classTest.lua");
	scripts.push_back("scripts/graphicsExample.lua");
	scripts.push_back("scripts/imageLoaderExample.lua");
	scripts.push_back("scripts/polygonExample.lua");
	scripts.push_back("scripts/fontsExample.lua");
	currentScript = 0;
	
	// init the lua state
	lua.init(true);
	
	// listen to error events
	lua.addListener(this);
	
	// run a script
	lua.doScript(scripts[currentScript]);
	
	// call the script's setup() function
	lua.scriptSetup();
}

//--------------------------------------------------------------
void testApp::update() {
	// call the script's update() function
	lua.scriptUpdate();
}

//--------------------------------------------------------------
void testApp::draw() {
	// call the script's draw() function
	lua.scriptDraw();
	
	ofSetColor(0);
	ofDrawBitmapString("use <- & -> (double tap on iOS) to change between scripts", 10, ofGetHeight()-22);
	ofDrawBitmapString(scripts[currentScript], 10, ofGetHeight()-10);
}

//--------------------------------------------------------------
void testApp::exit() {
	// call the script's exit() function
	lua.scriptExit();
	
	// clear the lua state
	lua.clear();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
void testApp::keyReleased(int key){
	lua.scriptKeyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	lua.scriptMouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	lua.scriptMouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	lua.scriptMousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	lua.scriptMouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::errorReceived(string& msg) {
	cout << "got an error: " << msg << endl;
	lua.clear();
}

//--------------------------------------------------------------
void testApp::reloadScript() {
	// exit, reinit the lua state, and reload the current script
	lua.scriptExit();
	lua.init(true);
	lua.doScript(scripts[currentScript]);
	lua.scriptSetup();
}

void testApp::nextScript() {
	currentScript++;
	if(currentScript > scripts.size()-1)
		currentScript = 0;
	reloadScript();
}

void testApp::prevScript() {
	currentScript--;
	if(currentScript < 0)
		currentScript = scripts.size()-1;
	reloadScript();
}
