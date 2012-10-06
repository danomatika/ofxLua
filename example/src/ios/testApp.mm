/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxPd for documentation
 *
 */
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	// If you want a landscape oreintation 
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(127, 127, 127);
	
	// setup the app core
	core.setup();
}

//--------------------------------------------------------------
void testApp::update() {
	core.update();
}

//--------------------------------------------------------------
void testApp::draw() {
	core.draw();
}

//--------------------------------------------------------------
void testApp::exit() {
	core.exit();
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch) {
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch) {

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch) {

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch) {
	core.nextScript();
}

//--------------------------------------------------------------
void testApp::lostFocus() {

}

//--------------------------------------------------------------
void testApp::gotFocus() {

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning() {

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation) {

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs& args) {

}
