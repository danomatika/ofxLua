/*
 * Copyright (c) 2011,2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxLua.h"

class ofWrapper {

	public:
	
		/// static function called when binding
		static void bind(ofxLua& lua) {
		
			using namespace luabind;
			
			/// example OpenFrameworks api wrapper
			///
			/// note: this is not the *entire* api
			///
			module(lua, "of")
			[
				///////////////////////////////
				/// \section Graphics
				
				/// openGL wrappers
				def("pushMatrix", &ofPushMatrix),
				def("popMatrix", &ofPopMatrix),
				def("translate", (void(*)(float,float,float)) &ofTranslate),
				def("scale", &ofScale),
				def("rotate", (void(*)(float,float,float,float)) &ofRotate),
				def("rotateX", &ofRotateX),
				def("rotateY", &ofRotateY),
				def("rotateZ", &ofRotateZ),
				def("rotate", (void(*)(float)) &ofRotate),
				
				/// drawing modes
				def("setCircleResolution", &ofSetCircleResolution),
				def("setCurveResolution", &ofSetCurveResolution),
				
				/// drawing options
				def("noFill", &ofNoFill),
				def("fill", &ofFill),
				def("setLineWidth", &ofSetLineWidth),
				
				/// color options
				def("setColor", (void(*)(int)) &ofSetColor),
				def("setColor", (void(*)(int,int,int)) &ofSetColor),
				def("setColor", (void(*)(int,int,int,int)) &ofSetColor),
				def("setHexColor", (void(*)(int)) &ofSetHexColor),
				
				/// blending
				//def("enableBlendMode", &ofEnableBlendMode),
				//def("disableBlendMode", &ofDisableBlendMode),
				
				/// transparency
				def("enableAlphaBlending", &ofEnableAlphaBlending),
				def("disableAlphaBlending", &ofDisableAlphaBlending),
				
				/// smooth
				def("enableSmoothing", &ofEnableSmoothing),
				def("disableSmoothing", &ofDisableSmoothing),
				
				/// drawing style
				def("setPolyMode", &ofSetPolyMode),
				
				/// background
				def("background",	(void(*)(int)) &background),
				def("background",	(void(*)(int,int)) &ofBackground),
				def("background",	(void(*)(int,int,int)) &background),
				def("background",	(void(*)(int,int,int,int)) &ofBackground),
				def("clear",		(void(*)(float,float,float,float)) &ofClear),
				def("clearAlpha",	&ofClearAlpha),
						
				/// geometry
				def("line", 	(void(*)(float,float,float,float)) &ofLine),
				def("rect", 	(void(*)(float,float,float,float)) &ofRect),
				def("triangle",	(void(*)(float,float,float,float,float,float)) &ofTriangle),
				def("circle", 	(void(*)(float,float,float)) &ofCircle),
				def("ellipse",	(void(*)(float,float,float,float)) &ofEllipse),
				def("curve", 	(void(*)(float,float,float,float,float,float,float,float)) &ofCurve),
				def("bezier",	(void(*)(float,float,float,float,float,float,float,float)) &ofBezier),
				
				/// polygons
				def("beginShape", &ofBeginShape),
				def("vertex",	(void(*)(float,float)) &ofVertex),
				def("curveVertex", (void(*)(float,float)) &ofCurveVertex),
				def("bezierVertex", (void(*)(float,float,float,float,float,float)) &ofBezierVertex),
				def("endShape",	&ofEndShape),
				def("nextContour", &ofNextContour),
				
				/// bitmapped text
				def("drawBitmapString", (void(*)(string,float,float)) &ofDrawBitmapString),
			
				///////////////////////////////
				/// \section PolyLine
				
				class_<ofPolyline>("polyline")
					.def(constructor<>())
					.enum_("windingMode")
					[	
						value("WINDING_ODD", OF_POLY_WINDING_ODD),
						value("WINDING_NONZERO", OF_POLY_WINDING_NONZERO),
						value("WINDING_POSITIVE", OF_POLY_WINDING_POSITIVE),
						value("WINDING_NEGATIVE", OF_POLY_WINDING_NEGATIVE),
						value("WINDING_ABS_GEQ_TWO", OF_POLY_WINDING_ABS_GEQ_TWO)
					],
			
				///////////////////////////////
				/// \section Rectangle
				
				class_<ofRectangle>("rectangle")
					.def(constructor<>())
					.def(constructor<const ofRectangle&>())
					.def(constructor<float,float,float,float>())
					.def("set", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::set)
					.def("set", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::set)
					.def("setFromCenter", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::setFromCenter)
					//.def("inside", (void(ofRectangle::*)(float,float)) &ofRectangle::inside)
					.property("x", &ofRectangle::getX, &ofRectangle::setX)
					.property("y", &ofRectangle::getY, &ofRectangle::setY)
					.def_readonly("width", &ofRectangle::width)
					.def_readonly("height", &ofRectangle::height),
			
				///////////////////////////////
				/// \section Color
				
				class_<ofColor>("color")
					.def(constructor<>())
					.def(constructor<float,float,float,float>())
					.def(constructor<float,float,float>())
					.def(constructor<float,float>())
					.def(constructor<float>())
					.def("set", (void(ofColor::*)(float,float,float,float)) &ofColor::set)
					//.def("set", (void(ofColor::*)(float,float,float)) &ofColor::set3)
					.def("set", (void(ofColor::*)(float,float)) &ofColor::set)
					//.def("set", (void(Color::*)(float)) &ofColor::set1)
					.def("setHex", &ofColor::setHex)
					.def("getHex", &ofColor::getHex)
					.def("getHue", &ofColor::getHue)
					.def("getSaturation", &ofColor::getSaturation)
					.def("getBrightness", &ofColor::getBrightness)
					.def("getLightness", &ofColor::getLightness)
					.def("setHue", &ofColor::setHue)
					.def("setSaturation", &ofColor::setSaturation)
					.def("setBrightness", &ofColor::setBrightness),
			
				///////////////////////////////
				/// \section Pixels
				
				class_<ofPixels>("pixels")
					.def(constructor<>())
					.def("allocate", (void(ofPixels::*)(int,int,int)) &ofPixels::allocate)
					.def("allocate", (void(ofPixels::*)(int,int,ofPixelFormat)) &ofPixels::allocate)
					.def("allocate", (void(ofPixels::*)(int,int,ofImageType)) &ofPixels::allocate)
					.def("set", (void(ofPixels::*)(unsigned char)) &ofPixels::set)
					.def("set", (void(ofPixels::*)(int,unsigned char)) &ofPixels::set)
					.def("swapRgb", &ofPixels::swapRgb)
					.def("clear", &ofPixels::clear)
					.def("getColor", &ofPixels::getColor)
					.def("setColor", (void(ofPixels::*)(const ofColor&)) &ofPixels::setColor)
					.def("getPixelIndex", &ofPixels::getPixelIndex)
					.def("getPixel", &getPixel)
					.def("setPixel", &setPixel)
					.def("isAllocated", &ofPixels::isAllocated)
					.def("getWidth", &ofPixels::getWidth)
					.def("getHeight", &ofPixels::getHeight)
					.def("getImageType", &ofPixels::getImageType)
					.def("size", &ofPixels::size)
					.enum_("format")
					[
						value("MONO", OF_PIXELS_MONO),
						value("RGB", OF_PIXELS_RGB),
						value("RGBA", OF_PIXELS_RGBA),
						value("BGRA", OF_PIXELS_BGRA),
						value("RGB565", OF_PIXELS_RGB565)
					],
			
				///////////////////////////////
				/// \section Image
				
				class_<ofImage>("image")
					.def(constructor<>())
					.def(constructor<const string&>())
					.def("allocate", &ofImage::allocate)
					.def("clear", &ofImage::clear)
					.def("loadImage", (bool(ofImage::*)(string)) &ofImage::loadImage)
					.def("getPixels", &ofImage::getPixelsRef)
					.def("setImageType", &ofImage::setImageType)
					.def("getColor", &ofImage::getColor)
					.def("setColor",  (void(ofImage::*)(const ofColor&)) &ofImage::setColor)
					.def("resize", &ofImage::resize)
					.def("update", &ofImage::update)
					.def("draw", (void(ofImage::*)(float,float)) &ofImage::draw)
					.def("draw", (void(ofImage::*)(float,float,float,float)) &ofImage::draw)
					.def("getHeight", &ofImage::getHeight)
					.def("getWidth", &ofImage::getWidth)
					.def("allocated", &ofImage::bAllocated)
					.def_readonly("width", &ofImage::width)
					.def_readonly("height", &ofImage::height)
					.def_readonly("bpp", &ofImage::bpp)
					.enum_("imageType")
					[
						value("GRAYSCALE", OF_IMAGE_GRAYSCALE),
						value("COLOR", OF_IMAGE_COLOR),
						value("COLOR_ALPHA", OF_IMAGE_COLOR_ALPHA),
						value("UNDEFINED", OF_IMAGE_UNDEFINED)
					],
			
				///////////////////////////////
				/// \section Font
				
				class_<ofTrueTypeFont>("font")
					.def(constructor<>())
					.def("loadFont", &loadFont2)
					.def("loadFont", &loadFont4)
					.def("loadFont", (void(ofTrueTypeFont::*)(string,int,bool,bool,bool,float)) &ofTrueTypeFont::loadFont)
					.def("isLoaded", &ofTrueTypeFont::isLoaded)
					.def("getLineHeight", &ofTrueTypeFont::getLineHeight)
					.def("setLineHeight", &ofTrueTypeFont::setLineHeight)
					.def("getLetterSpacing", &ofTrueTypeFont::getLetterSpacing)
					.def("setLetterSpacing", &ofTrueTypeFont::setLetterSpacing)
					.def("getSpaceSize", &ofTrueTypeFont::getSpaceSize)
					.def("setSpaceSize", &ofTrueTypeFont::setSpaceSize)
					.def("stringWidth", &ofTrueTypeFont::stringWidth)
					.def("stringHeight", &ofTrueTypeFont::stringHeight)
					.def("getStringBoundingBox", &ofTrueTypeFont::getStringBoundingBox)
					.def("drawString", &ofTrueTypeFont::drawString)
					.def("drawStringAsShapes", &ofTrueTypeFont::drawStringAsShapes),
			
				///////////////////////////////
				/// \section Math
				
				def("random", (float(*)(float)) &ofRandom),
				def("random", (float(*)(float,float)) &ofRandom),
				
				///////////////////////////////
				/// \section App
				
				/// input properties
				def("mouseX", &getMouseX),
				def("mouseY", &getMouseY),
				
				/// exit
				def("exit", (void(*)(void)) &ofExit),
				def("exit", (void(*)(int)) &ofExit),
				
				/// time
				def("getFrameRate", &ofGetFrameRate),
				def("getFrameNum", &ofGetFrameNum),
				def("setFrameRate", &ofSetFrameRate),
				def("sleepMillis", &ofSleepMillis),
				def("getLastFrameTime", &ofGetLastFrameTime),
				
				/// cursor
				def("hideCursor", &ofHideCursor),
				def("showCursor", &ofShowCursor),
				
				/// window / screen
				def("getWindowPositionX", &ofGetWindowPositionX),
				def("getWindowPositionY", &ofGetWindowPositionY),
				def("getScreenWidth", &ofGetScreenWidth),
				def("getScreenHeight", &ofGetScreenHeight),
				def("getWindowMode", &ofGetWindowMode),
				def("getWidth", &ofGetWidth),
				def("getHeight", &ofGetHeight),
				def("getWindowWidth", &ofGetWindowWidth),
				def("getWindowHeight", &ofGetWindowHeight),
				
				def("setWindowPosition", &ofSetWindowPosition),
				def("setWindowShape", &ofSetWindowShape),
				def("setWindowTitle", &ofSetWindowTitle),
				def("enableSetupScreen", &ofEnableSetupScreen),
				def("disableSetupScreen", &ofDisableSetupScreen),
				def("setFullscreen", &ofSetFullscreen),
				def("toggleFullscreen", &ofToggleFullscreen),
				
				/// sync
				def("setVerticalSync", &ofSetVerticalSync),
				
				///////////////////////////////
				/// \section Utils
				
				def("nextPow2", &ofNextPow2),
				
				def("resetElapsedTimeCounter", &ofResetElapsedTimeCounter),
				def("getElapsedTime", &ofGetElapsedTimef),
				def("getElapsedTimeMillis", &ofGetElapsedTimeMillis),
				def("getElapsedTimeMicros", &ofGetElapsedTimeMicros),
				
				def("getSeconds", &ofGetSeconds),
				def("getMinutes", &ofGetMinutes),
				def("getHours", &ofGetHours),
				
				def("getUnixTime", &ofGetUnixTime),
				
				def("getSystemTime", &ofGetSystemTime),
				def("getSystemTimeMicros", &ofGetSystemTimeMicros),
				
				def("getTimestampString", (string(*)(void)) &ofGetTimestampString),
				def("getTimestampString", (string(*)(string)) &ofGetTimestampString),

				def("getYear", &ofGetYear),
				def("getMonth", &ofGetMonth),
				def("getDay", &ofGetDay),
				def("getWeekday", &ofGetWeekday),
				
				def("launchBrowser", &ofLaunchBrowser)
			];
			
			///////////////////////////////
			/// \section Add Values
			
			/// add some constant values to the lua state
			lua.doString("math.TWO_PI = "+ofToString(TWO_PI));
		}
		
		/// \section Function & Object Wrappers
		
		/// background
		static void background(int brightness) 		{ofBackground(brightness);}
		static void background(int r, int g, int b)	{ofBackground(r, g, b);}

		/// ofPixels
		static unsigned char getPixel(ofPixels* pixels, int index) {
			return pixels->getPixels()[index];
		}
		static void setPixel(ofPixels* pixels, int index, unsigned char p) {
			pixels->getPixels()[index] = p;
		}

		/// global mouse vars
		static int getMouseX() {return ofGetAppPtr()->mouseX;}
		static int getMouseY() {return ofGetAppPtr()->mouseY;}
		
		/// ofTrueTypeFont
		static void loadFont2(ofTrueTypeFont* font, string filename, int fontsize) {
			font->loadFont(filename, fontsize);
		}
		static void loadFont4(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
			font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet);
		}
};
