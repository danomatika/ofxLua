#pragma once

#include "ofMain.h"

#include "ofxLua.h"

class testApp : public ofBaseApp, ofxLuaListener {

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		// ofxLua error callback
		void errorReceived(string& msg);
		
		// script control
		void reloadScript();
		void nextScript();
		void prevScript();
		
		ofxLua lua;
		vector<string> scripts;
		int currentScript;
};
