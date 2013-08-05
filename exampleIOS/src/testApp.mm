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
	
	// iOSAlerts will be sent to this.
	ofxiOSAlerts.addListener(this);
	
	// if you want a landscape oreintation 
	ofSetOrientation(OF_ORIENTATION_90_RIGHT);
	
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
	core.mousePressed(touch.x, touch.y, 0);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch) {
	core.mouseMoved(touch.x, touch.y);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch) {
	core.mouseReleased(touch.x, touch.y, 0);
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
