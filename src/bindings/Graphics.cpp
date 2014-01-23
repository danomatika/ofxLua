/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "of3dGraphics.h"
#include "ofGraphics.h"
#include "ofImage.h"
#include "ofPath.h"
#include "ofPixels.h"
#include "ofPolyline.h"
#include "ofTrueTypeFont.h"
#include "ofxLua.h"

namespace bindings {

// dummy classes for empty class enums

struct InterpolationMethod {};

// wrapper functions needed for overloading

// 3d utils
ofPoint getPlaneResolution()
	{ofVec2f v = ofGetPlaneResolution(); return ofPoint(v.x, v.y, 0);}
void setCylinderResolution2(int radiusSegments, int heightSegments)
	{ofSetCylinderResolution(radiusSegments, heightSegments);}
void setConeResolution2(int radiusSegments, int heightSegments)
	{ofSetConeResolution(radiusSegments, heightSegments);}

// viewport
void viewport0() {ofViewport();}
void viewport1(float x) {ofViewport(x);}
void viewport2(float x, float y) {ofViewport(x, y);}
void viewport3(float x, float y, float width)
	{ofViewport(x, y, width);}
void viewport4(float x, float y, float width, float height)
	{ofViewport(x, y, width, height);}
	
// setup screen
void setupScreenPerspective0() {ofSetupScreenPerspective();}
void setupScreenPerspective1(float width)
	{ofSetupScreenPerspective(width);}
void setupScreenPerspective2(float width, float height)
	{ofSetupScreenPerspective(width, height);}
void setupScreenPerspective3(float width, float height, float fov)
	{ofSetupScreenPerspective(width, height, fov);}
void setupScreenPerspective4(float width, float height, float fov, float nearDist)
	{ofSetupScreenPerspective(width, height, fov, nearDist);}

void setupScreenOrtho0() {ofSetupScreenOrtho();}
void setupScreenOrtho1(float width)
	{ofSetupScreenOrtho(width);}
void setupScreenOrtho2(float width, float height)
	{ofSetupScreenOrtho(width, height);}
void setupScreenOrtho3(float width, float height, float nearDist)
	{ofSetupScreenOrtho(width, height, nearDist);}

// gl wrappers
void translate2(float x, float y) {ofTranslate(x, y);}
void scale2(float xAmnt, float yAmnt) {ofScale(xAmnt, yAmnt);}

// drawing options
bool getFill() {return (bool) ofGetFill();}

// background
void background(int brightness) {ofBackground(brightness);}
void background(int r, int g, int b) {ofBackground(r, g, b);}
void backgroundHex(int hexColor) {ofBackgroundHex(hexColor);}
void backgroundGradient(const ofColor& start, const ofColor& end)
	{ofBackgroundGradient(start, end);}

void setBackgroundColor(int brightness) {ofBackground(brightness);}
void setBackgroundColor(int r, int g, int b) {ofBackground(r, g, b);}
void setBackgroundColorHex(int hexColor) {ofSetBackgroundColorHex(hexColor);}

void clear(float brightness) {ofClear(brightness);}
void clear(float r, float g, float b) {ofClear(r, g, b);}
void autoBackground() {ofSetBackgroundAuto(true);}
void noAutoBackground() {ofSetBackgroundAuto(false);}

// primitives
void curve(const ofPoint& p1, const ofPoint& p2, const ofPoint& p3, const ofPoint& p4)
	{ofCurve(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z);}
void bezier(const ofPoint& p1, const ofPoint& p2, const ofPoint& p3, const ofPoint& p4)
	{ofBezier(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z);}

// polygons
void endShape() {ofEndShape();}
void nextContour() {ofNextContour();}

// bitmapped type
void drawBitmapStringHighlight2(string text, const ofPoint& position)
	{ofDrawBitmapStringHighlight(text, position);}
void drawBitmapStringHighlight3(string text, const ofPoint& position, const ofColor& background)
	{ofDrawBitmapStringHighlight(text, position, background);}
void drawBitmapStringHighlight3(string text, int x, int y)
	{ofDrawBitmapStringHighlight(text, x, y);}
void drawBitmapStringHighlight4(string text, int x, int y, const ofColor& background)
	{ofDrawBitmapStringHighlight(text, x, y, background);}

// image
void imageSaveImage1(ofImage* image, string fileName)
	{image->saveImage(fileName);}
void imageRotate90(ofImage* image)
	{image->rotate90(1);}

// path
void pathMoveTo2(ofPath* path, float x, float y)
	{path->moveTo(x, y);}
void pathCurveTo1(ofPath* path, const ofPoint& p)
	{path->curveTo(p);}
ofPolyline pathGetOutline(ofPath* path, unsigned int index)
	{return path->getOutline()[index];}
// Todo: ofPolyline dosen't have a copy operator yet ...
//		void pathSetOutline(ofPath* path, unsigned int index, const ofPolyLine& line)
//			{path->getOutline()[index] = line;}
int pathNumOutlines(ofPath* path)
	{return path->getOutline().size();}
void pathEnableShapeColor(ofPath* path)
	{path->setUseShapeColor(true);}
void pathDisableShapeColor(ofPath* path)
	{path->setUseShapeColor(false);}
void pathSimplify0(ofPath* path)
	{path->simplify();}
void pathTranslate2(ofPath* path, float x, float y)
	{path->translate(ofPoint(x, y));}
void pathTranslate3(ofPath* path, float x, float y, float z)
	{path->translate(ofPoint(x, y, z));}
void pathRotate1(ofPath* path, float angle)
	{path->rotate(angle, ofPoint(0, 0, 1));}
void pathRotateX(ofPath* path, float angle)
	{path->rotate(angle, ofPoint(1, 0, 0));}
void pathRotateY(ofPath* path, float angle)
	{path->rotate(angle, ofPoint(0, 1, 0));}
void pathRotateZ(ofPath* path, float angle)
	{path->rotate(angle, ofPoint(0, 0, 1));}
void pathRotate4(ofPath* path, float angle, float vecX, float vecY, float vecZ)
	{path->rotate(angle, ofPoint(vecX, vecY, vecZ));}

// pixels
void pixelsSetFromPixels(ofPixels* pixels, const ofPixels& newPixels, int w, int h, int channels)
	{pixels->setFromPixels(newPixels.getPixels(), w, h, channels);}
void pixelsSetFromPixelsWithImageType(ofPixels* pixels, const ofPixels& newPixels, int w, int h, ofImageType type)
	{pixels->setFromPixels(newPixels.getPixels(), w, h, type);}
void pixelsSetFromExternalPixels(ofPixels* pixels, ofPixels& newPixels, int w, int h, int channels)
	{pixels->setFromExternalPixels(newPixels.getPixels(), w, h, channels);}
void pixelsSetFromAlignedPixels(ofPixels* pixels, ofPixels& newPixels, int w, int h, int channels, int stride)
	{pixels->setFromAlignedPixels(newPixels.getPixels(), w, h, channels, stride);}
void pixelsRotate90(ofPixels* pixels)
	{pixels->rotate90(1);}
void pixelsRotate90To(ofPixels* pixels, ofPixels& dst)
	{pixels->rotate90To(dst, 1);}
bool pixelsResize(ofPixels* pixels, int dstWidth, int dstHeight)
	{return pixels->resize(dstWidth, dstHeight);}
bool pixelsResizeTo(ofPixels* pixels, ofPixels& dst)
	{return pixels->resizeTo(dst);}
unsigned char pixelsGetPixel(ofPixels* pixels, unsigned int index)
	{return pixels->getPixels()[index];}
void pixelsSetPixel(ofPixels* pixels, unsigned int index, unsigned char p)
	{pixels->getPixels()[index] = p;}

// polyline
void polylineAddVertex2(ofPolyline* line, float x, float y) {line->addVertex(x, y);}
void polylineLineTo2(ofPolyline* line, float x, float y) {line->lineTo(x, y);}
void polylineArcPoint5(ofPolyline* line, const ofPoint & center, float radiusX, float radiusY, float angleBegin, float angleEnd)
	{line->arc(center, radiusX, radiusY, angleBegin, angleEnd);}
void polylineArcPoint6(ofPolyline* line, const ofPoint & center, float radiusX, float radiusY, float angleBegin, float angleEnd, bool clockwise)
	{line->arc(center, radiusX, radiusY, angleBegin, angleEnd, clockwise);}
void polylineArcFloat6(ofPolyline* line, float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd)
	{line->arc(x, y, radiusX, radiusY, angleBegin, angleEnd);}
void polylineArcFloat7(ofPolyline* line, float x, float y, float z, float radiusX, float radiusY, float angleBegin, float angleEnd)
	{line->arc(x, y, z, radiusX, radiusY, angleBegin, angleEnd);}
void polylineArcNegativePoint5(ofPolyline* line, const ofPoint & center, float radiusX, float radiusY, float angleBegin, float angleEnd)
	{line->arcNegative(center, radiusX, radiusY, angleBegin, angleEnd);}
void polylineArcNegativeFloat6(ofPolyline* line, float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd)
	{line->arcNegative(x, y, radiusX, radiusY, angleBegin, angleEnd);}
void polylineArcNegativeFloat7(ofPolyline* line, float x, float y, float z, float radiusX, float radiusY, float angleBegin, float angleEnd)
	{line->arcNegative(x, y, z, radiusX, radiusY, angleBegin, angleEnd);}

void polylineCurveToPoint1(ofPolyline* line, const ofPoint& to) {line->curveTo(to);}
void polylineCurveToFloat2(ofPolyline* line, float x, float y) {line->curveTo(x, y);}
void polylineCurveToFloat3(ofPolyline* line, float x, float y, float z) {line->curveTo(x, y, z);}

void polylineBezierToPoint3(ofPolyline* line, const ofPoint & cp1, const ofPoint & cp2, const ofPoint & to)
	{line->bezierTo(cp1, cp2, to);}
void polylineBezierToFloat6(ofPolyline* line, float cx1, float cy1, float cx2, float cy2, float x, float y)
	{line->bezierTo(cx1, cy1, cx2, cy2, x, y);}
void polylineBezierToFloat9(ofPolyline* line, float cx1, float cy1, float cz1, float cx2, float cy2, float cz2, float x, float y, float z)
	{line->bezierTo(cx1, cy1, cz1, cx2, cy2, cz2, x, y, z);}
void polylineQuadBezierToPoint3(ofPolyline* line, const ofPoint & cp1, const ofPoint & cp2, const ofPoint & to)
	{line->quadBezierTo(cp1, cp2, to);}
void polylineQuadBezierToFloat6(ofPolyline* line, float cx1, float cy1, float cx2, float cy2, float x, float y)
	{line->quadBezierTo(cx1, cy1, cx2, cy2, x, y);}
void polylineQuadBezierToFloat9(ofPolyline* line, float cx1, float cy1, float cz1, float cx2, float cy2, float cz2, float x, float y, float z)
	{line->quadBezierTo(cx1, cy1, cz1, cx2, cy2, cz2, x, y, z);}
ofPolyline polylineGetSmoothed1(ofPolyline* line, float smoothingSize)
	{return line->getSmoothed(smoothingSize);}
ofPoint polylineGetClosestPoint1(ofPolyline* line, const ofPoint& target)
	{return line->getClosestPoint(target);}
unsigned int polylineGetClosestPointIndex(ofPolyline* line, const ofPoint& target) {
	unsigned int index = 0;
	line->getClosestPoint(target, &index);
	return index;}
void polylineSimplify0(ofPolyline* line)
	{line->simplify();}
ofPoint polylineGetPoint(ofPolyline* line, unsigned int index)
	{return line->getVertices()[index];}
void polylineSetPoint(ofPolyline* line, unsigned int index, const ofPoint& p)
	{line->getVertices()[index] = p;}
void polylineSetRightVector(ofPolyline* line) {line->setRightVector();}

// font
void fontLoadFont2(ofTrueTypeFont* font, string filename, int fontsize)
	{font->loadFont(filename, fontsize);}
void fontLoadFont4(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet)
	{font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet);}
void fontLoadFont5(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours)
	{font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet, makeContours);}
void fontLoadFont6(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt)
	{font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet, simplifyAmt);}

// luabind registration
luabind::scope registerGraphics() {

	using namespace luabind;
	
	return
	
		///////////////////////////////
		/// \section of3dGraphics.h
		
		def("setPlaneResolution", &ofSetPlaneResolution),
		def("getPlaneResolution", &getPlaneResolution),
		def("drawPlane", (void(*)(float,float,float,float)) &ofDrawPlane),
		def("drawPlane", (void(*)(float,float,float,float,float)) &ofDrawPlane),
		def("drawPlane", (void(*)(ofPoint&,float,float)) &ofDrawPlane),
		def("drawPlane", (void(*)(float,float)) &ofDrawPlane),
		
		def("setSphereResolution", &ofSetSphereResolution),
		def("getSphereResolution", &ofGetSphereResolution),
		def("drawSphere", (void(*)(float,float,float)) &ofDrawSphere),
		def("drawSphere", (void(*)(float,float,float,float)) &ofDrawSphere),
		def("drawSphere", (void(*)(const ofPoint&,float)) &ofDrawSphere),
		def("drawSphere", (void(*)(float)) &ofDrawSphere),
		
		def("setIcoSphereResolution", &ofSetIcoSphereResolution),
		def("getIcoSphereResolution", &ofGetIcoSphereResolution),
		def("drawIcoSphere", (void(*)(float,float,float)) &ofDrawIcoSphere),
		def("drawIcoSphere", (void(*)(float,float,float,float)) &ofDrawIcoSphere),
		def("drawIcoSphere", (void(*)(const ofPoint&,float)) &ofDrawIcoSphere),
		def("drawIcoSphere", (void(*)(float)) &ofDrawIcoSphere),
		
		def("setCylinderResolution", &setCylinderResolution2),
		def("setCylinderResolution", &ofSetCylinderResolution),
		def("getCylinderResolution", &ofGetCylinderResolution),
		def("drawCylinder", (void(*)(float,float,float,float)) &ofDrawCylinder),
		def("drawCylinder", (void(*)(float,float,float,float,float)) &ofDrawCylinder),
		def("drawCylinder", (void(*)(const ofPoint&,float,float)) &ofDrawCylinder),
		def("drawCylinder", (void(*)(float,float)) &ofDrawCylinder),
		
		def("setConeResolution", &setConeResolution2),
		def("setConeResolution", &ofSetConeResolution),
		def("getConeResolution", &ofGetConeResolution),
		def("drawCone", (void(*)(float,float,float,float)) &ofDrawCone),
		def("drawCone", (void(*)(float,float,float,float,float)) &ofDrawCone),
		def("drawCone", (void(*)(const ofPoint&,float,float)) &ofDrawCone),
		def("drawCone", (void(*)(float,float)) &ofDrawCone),
		
		def("setBoxResolution", (void(*)(int)) &ofSetBoxResolution),
		def("setBoxResolution", (void(*)(int,int,int)) &ofSetBoxResolution),
		def("getBoxResolution", &ofGetBoxResolution),
		def("drawBox", (void(*)(float,float,float,float)) &ofDrawBox),
		def("drawBox", (void(*)(float,float,float,float,float,float)) &ofDrawBox),
		def("drawBox", (void(*)(const ofPoint&,float,float,float)) &ofDrawBox),
		def("drawBox", (void(*)(const ofPoint&,float)) &ofDrawBox),
		def("drawBox", (void(*)(float)) &ofDrawBox),
		def("drawBox", (void(*)(float,float,float)) &ofDrawBox),
	
		///////////////////////////////
		/// \section ofGraphics.h
		
		// no renderer functions
		
		// pdf screenshot
	#ifndef TARGET_OF_IOS
		def("beginSaveScreenAsPDF", &ofBeginSaveScreenAsPDF),
		def("endSaveScreenAsPDF", &ofEndSaveScreenAsPDF),
	#endif
		
		// view transformations
		def("pushView", &ofPushView),
		def("popView", &ofPopView),
		
		def("viewport", (void(*)(ofRectangle)) &ofViewport),
		def("viewport", &viewport0),
		def("viewport", &viewport1),
		def("viewport", &viewport2),
		def("viewport", &viewport3),
		def("viewport", &viewport4),
		def("viewport", (void(*)(float,float,float,float,bool)) &ofViewport),
		
		def("isVFlipped", ofIsVFlipped),
		
		def("setupScreenPerspective", &setupScreenPerspective0),
		def("setupScreenPerspective", &setupScreenPerspective1),
		def("setupScreenPerspective", &setupScreenPerspective2),
		def("setupScreenPerspective", &setupScreenPerspective3),
		def("setupScreenPerspective", &setupScreenPerspective4),
		def("setupScreenPerspective", (void(*)(float,float,float,float,float)) &ofSetupScreenPerspective),
		
		def("setupScreenOrtho", &setupScreenOrtho0),
		def("setupScreenOrtho", &setupScreenOrtho1),
		def("setupScreenOrtho", &setupScreenOrtho2),
		def("setupScreenOrtho", &setupScreenOrtho3),
		def("setupScreenOrtho", (void(*)(float,float,float,float)) &ofSetupScreenOrtho),
		
		def("getCurrentViewport", &ofGetCurrentViewport),
		def("getNativeViewport", &ofGetNativeViewport),
		def("getViewportWidth", &ofGetViewportWidth),
		def("viewportHeight", &ofGetViewportHeight),
		def("orientationToDegrees", &ofOrientationToDegrees),

		def("setCoordHandedness", &ofSetCoordHandedness),
		def("getCoordHandedness", &ofGetCoordHandedness),
		
		/// openGL wrappers
		def("pushMatrix", &ofPushMatrix),
		def("popMatrix", &ofPopMatrix),
		def("translate", &translate2),
		def("translate", (void(*)(float,float,float)) &ofTranslate),
		def("translate", (void(*)(const ofPoint&)) &ofTranslate),
		def("scale", &scale2),
		def("scale", &ofScale),
		def("rotate", (void(*)(float,float,float,float)) &ofRotate),
		def("rotateX", &ofRotateX),
		def("rotateY", &ofRotateY),
		def("rotateZ", &ofRotateZ),
		def("rotate", (void(*)(float)) &ofRotate),
		def("loadIdentityMatrix", &ofLoadIdentityMatrix),
		def("loadMatrix", (void(*)(const ofMatrix4x4&)) &ofLoadMatrix),
		// ignore const float *m ofLoadMatrix
		def("multMatrix", (void(*)(const ofMatrix4x4&)) &ofMultMatrix),
		// ignore const float *m ofMultMatrix
		def("setMatrixMode", &ofSetMatrixMode),
		
		def("setupGraphicDefaults", &ofSetupGraphicDefaults),
		def("setupScreen", &ofSetupScreen),
		
		/// drawing modes
		def("getRectMode", &ofGetRectMode),
		
		def("setCircleResolution", &ofSetCircleResolution),
		def("setCurveResolution", &ofSetCurveResolution),
		
		// drawing options
		def("noFill", &ofNoFill),
		def("fill", &ofFill),
		def("getFill", &getFill), // returns bool, flags aren't wrapped
		
		def("setLineWidth", &ofSetLineWidth),
		def("setDepthTest", &ofSetDepthTest),
		def("enableDepthTest", ofEnableDepthTest),
		def("disableDepthTest", ofDisableDepthTest),
		
		// color options
		def("setColor", (void(*)(int,int,int)) &ofSetColor),
		def("setColor", (void(*)(int,int,int,int)) &ofSetColor),
		def("setColor", (void(*)(const ofColor&)) &ofSetColor),
		def("setColor", (void(*)(const ofColor&,int)) &ofSetColor),
		def("setColor", (void(*)(int)) &ofSetColor),
		def("setHexColor", (void(*)(int)) &ofSetHexColor),
		
		// blending
		def("enableBlendMode", &ofEnableBlendMode),
		def("disableBlendMode", &ofDisableBlendMode),
		
		// point sprites
		def("enablePointSprites", &ofEnablePointSprites),
		def("disablePointSprites", &ofDisablePointSprites),
		
		// transparency
		def("enableAlphaBlending", &ofEnableAlphaBlending),
		def("disableAlphaBlending", &ofDisableAlphaBlending),
		
		// smooth
		def("enableSmoothing", &ofEnableSmoothing),
		def("disableSmoothing", &ofDisableSmoothing),
		
		// drawing style
		def("getStyle", &ofGetStyle),
		def("setStyle", &ofSetStyle),
		def("pushStyle", &ofPushStyle),
		def("popStyle", &ofPopStyle),
		
		def("setPolyMode", &ofSetPolyMode),
		def("setRectMode", &ofSetRectMode),
		
		// background
		// ignoring background Ptr function
		def("getBackground", &ofGetBackground),
		def("background", (void(*)(int)) &background),
		def("background", (void(*)(int,int)) &ofBackground),
		def("background", (void(*)(int,int,int)) &background),
		def("background", (void(*)(int,int,int,int)) &ofBackground),
		def("background", (void(*)(const ofColor&)) &ofBackground),
		def("backgroundHex", (void(*)(int)) &background),
		def("backgroundHex", (void(*)(int,int)) &ofBackgroundHex),
		def("bacgkroundGradient", &backgroundGradient),
		def("bacgkroundGradient", &ofBackgroundGradient),
		
		// no sure why these are duplicates of the functions above ...
		def("setBackgroundColor", (void(*)(int)) &setBackgroundColor),
		def("setBackgroundColor", (void(*)(int,int)) &ofSetBackgroundColor),
		def("setBackgroundColor", (void(*)(int,int,int)) &setBackgroundColor),
		def("setBackgroundColor", (void(*)(int,int,int,int)) &ofSetBackgroundColor),
		def("setBackgroundColor", (void(*)(const ofColor&)) &ofSetBackgroundColor),
		def("setBackgroundColorHex", (void(*)(int)) &setBackgroundColorHex),
		def("setBackgroundColorHex", (void(*)(int,int)) &ofSetBackgroundColorHex),
		
		def("setBackgroundAuto", &ofSetBackgroundAuto),
		
		def("clear", (void(*)(const ofColor&)) &ofClear),
		def("clear", (void(*)(float)) &clear),
		def("clear", (void(*)(float,float)) &ofClear),
		def("clear", (void(*)(float,float,float)) &clear),
		def("clear", (void(*)(float,float,float,float)) &ofClear),
		def("clearAlpha", &ofClearAlpha),
		
		def("bClearBg", &ofbClearBg), // is this needed?
				
		// geometry
		def("triangle",	(void(*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofTriangle),
		def("triangle",	(void(*)(float,float,float,float,float,float)) &ofTriangle),
		def("triangle",	(void(*)(float,float,float,float,float,float,float,float,float)) &ofTriangle),
		
		def("circle", (void(*)(float,float,float)) &ofCircle),
		def("circle", (void(*)(float,float,float,float)) &ofCircle),
		def("circle", (void(*)(const ofPoint&,float)) &ofCircle),
		
		def("ellipse", (void(*)(const ofPoint&,float,float)) &ofEllipse),
		def("ellipse", (void(*)(float,float,float,float)) &ofEllipse),
		def("ellipse", (void(*)(float,float,float,float,float)) &ofEllipse),
		
		def("line", (void(*)(float,float,float,float)) &ofLine),
		def("line", (void(*)(float,float,float,float,float,float)) &ofLine),
		def("line", (void(*)(const ofPoint&,const ofPoint&)) &ofLine),
		
		def("rect", (void(*)(const ofRectangle&)) &ofRect),
		def("rect", (void(*)(const ofPoint&,float,float)) &ofRect),
		def("rect", (void(*)(float,float,float,float)) &ofRect),
		def("rect", (void(*)(float,float,float,float,float)) &ofRect),
		
		def("rectRounded", (void(*)(const ofRectangle&,float)) &ofRectRounded),
		def("rectRounded", (void(*)(const ofPoint&,float,float,float)) &ofRectRounded),
		def("rectRounded", (void(*)(float,float,float,float,float)) &ofRectRounded),
		//def("rectRounded", (void(*)(float,float,float,float,float,float)) &ofRectRounded),
		
		def("rectRounded", (void(*)(const ofPoint&,float,float,float,float,float,float)) &ofRectRounded),
		def("rectRounded", (void(*)(const ofRectangle&,float,float,float,float)) &ofRectRounded),
		def("rectRounded", (void(*)(float,float,float,float,float,float,float,float,float)) &ofRectRounded),
		
		def("curve", (void(*)(float,float,float,float,float,float,float,float)) &ofCurve),
		def("curve", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &curve),
		
		def("bezier", (void(*)(float,float,float,float,float,float,float,float)) &ofBezier),
		def("bezier", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &bezier),
		
		// polygons
		def("beginShape", &ofBeginShape),
		def("vertex", (void(*)(ofPoint&)) &ofVertex),
		def("vertex", (void(*)(float,float)) &ofVertex),
		def("vertex", (void(*)(float,float,float)) &ofVertex),
		//def("vertices", &vertices), // TODO: needs vector
		
		def("curveVertex", (void(*)(ofPoint&)) &ofCurveVertex),
		def("curveVertex", (void(*)(float,float)) &ofCurveVertex),
		def("curveVertex", (void(*)(float,float,float)) &ofCurveVertex),
		//def("curveVertices", &curveVertices), // TODO: needs vector
		
		def("bezierVertex", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofBezierVertex),
		def("bezierVertex", (void(*)(float,float,float,float,float,float)) &ofBezierVertex),
		def("bezierVertex", (void(*)(float,float,float,float,float,float,float,float,float)) &ofBezierVertex),
		//def("bezierVertices", &bezierVertices), // TODO: needs vector
		
		def("endShape",	(void(*)(void)) &endShape),
		def("endShape",	(void(*)(bool)) &ofEndShape),
		def("nextContour", (void(*)(void)) &nextContour),
		def("nextContour", (void(*)(bool)) &ofNextContour),
		
		// bitmapped type
		def("setDrawBitmapMode", &ofSetDrawBitmapMode),
		def("drawBitmapString", (void(*)(string,const ofPoint&)) &ofDrawBitmapString),
		def("drawBitmapString", (void(*)(string,float,float)) &ofDrawBitmapString),
		def("drawBitmapString", (void(*)(string,float,float,float)) &ofDrawBitmapString),
		def("drawBitmapStringHighlight", (void(*)(string,const ofPoint&)) &drawBitmapStringHighlight2),
		def("drawBitmapStringHighlight", (void(*)(string,const ofPoint&,const ofColor&)) &drawBitmapStringHighlight3),
		def("drawBitmapStringHighlight", (void(*)(string,const ofPoint&,const ofColor&,const ofColor&)) &ofDrawBitmapStringHighlight),
		def("drawBitmapStringHighlight", (void(*)(string,int,int)) &drawBitmapStringHighlight3),
		def("drawBitmapStringHighlight", (void(*)(string,int,int,const ofColor&)) &drawBitmapStringHighlight4),
		def("drawBitmapStringHighlight", (void(*)(string,int,int,const ofColor&,const ofColor&)) &ofDrawBitmapStringHighlight),
	
	
		///////////////////////////////
		/// \section ofImage.h
		
		class_<ofImage>("Image")
			.def(constructor<>())
			// ignoring pixel, file, & string constructor
			
			.def("allocate", &ofImage::allocate)
			.def("clear", &ofImage::clear)
			.def("clone", (void(ofImage::*)(const ofImage&)) &ofImage::clone)
			
			.def("setUseTexture", &ofImage::setUseTexture)
			.def("isUsingTexture", &ofImage::isUsingTexture)
			.property("usingTexture", &ofImage::isUsingTexture)
			.def("getTextureReference", &ofImage::getTextureReference)
			
			// ignoring bind/unbind
			
			.def("loadImage", (bool(ofImage::*)(string)) &ofImage::loadImage)
			.def("saveImage", &imageSaveImage1)
			.def("saveImage", (void(ofImage::*)(string,ofImageQualityType)) &ofImage::saveImage)
			
			.def("getPixelsRef", &ofImage::getPixelsRef)
			
			.def("getColor", &ofImage::getColor)
			.def("setColor", (void(ofImage::*)(int,int,const ofColor&)) &ofImage::setColor)
			.def("setColor", (void(ofImage::*)(int,const ofColor&)) &ofImage::setColor)
			.def("setColor", (void(ofImage::*)(const ofColor&)) &ofImage::setColor)
			.def("setFromPixels", (void(ofImage::*)(const ofPixels&)) &ofImage::setFromPixels)
			.def("setImageType", &ofImage::setImageType)
			.def("resize", &ofImage::resize)
			.def("grabScreen", &ofImage::grabScreen)
			
			.def("crop", &ofImage::crop)
			.def("cropFrom", &ofImage::cropFrom)
			.def("rotate90", &imageRotate90)
			.def("rotate90", &ofImage::rotate90)
			.def("mirror", &ofImage::mirror)
			
			.def("update", &ofImage::update)
			
			.def("setAnchorPercent", &ofImage::setAnchorPercent)
			.def("setAnchorPoint", &ofImage::setAnchorPoint)
			.def("resetAnchor", &ofImage::resetAnchor)
			
			.def("draw", (void(ofImage::*)(float,float)) &ofImage::draw)
			.def("draw", (void(ofImage::*)(float,float,float)) &ofImage::draw)
			.def("draw", (void(ofImage::*)(float,float,float,float)) &ofImage::draw)
			
			.def("drawSubsection", (void(ofImage::*)(float,float,float,float,float,float)) &ofImage::drawSubsection)
			.def("drawSubsection", (void(ofImage::*)(float,float,float,float,float,float,float)) &ofImage::drawSubsection)
			.def("drawSubsection", (void(ofImage::*)(float,float,float,float,float,float,float,float)) &ofImage::drawSubsection)
			.def("drawSubsection", (void(ofImage::*)(float,float,float,float,float,float,float,float,float)) &ofImage::drawSubsection)
			
			.def("isAllocated", &ofImage::isAllocated)
			.def_readonly("allocated", &ofImage::isAllocated)
			
			.def("getWidth", &ofImage::getWidth)
			.def("getHeight", &ofImage::getHeight)
			.def_readonly("width",  &ofImage::width)
			.def_readonly("height", &ofImage::height)
			.def_readonly("type", &ofImage::type)
			.def_readonly("bpp", &ofImage::bpp),
	
		///////////////////////////////
		/// \section ofPath.h
		
		class_<ofPath>("Path")
			.def(constructor<>())
			.def("clear", &ofPath::clear)
			
			.def("newSubPath", &ofPath::newSubPath)
			.def("close", &ofPath::close)
			
			.def("lineTo", (void(ofPath::*)(const ofPoint&)) &ofPath::lineTo)
			.def("lineTo", (void(ofPath::*)(float,float)) &ofPath::lineTo)
			.def("lineTo", (void(ofPath::*)(float,float,float)) &ofPath::lineTo)
			
			.def("moveTo", (void(ofPath::*)(const ofPoint&)) &ofPath::moveTo)
			.def("moveTo", &pathMoveTo2)
			.def("moveTo", (void(ofPath::*)(float,float,float)) &ofPath::moveTo)
			
			.def("curveTo", &pathCurveTo1)
			.def("curveTo",  (void(ofPath::*)(float,float)) &ofPath::curveTo)
			.def("curveTo", (void(ofPath::*)(float,float,float)) &ofPath::curveTo)
			
			.def("bezierTo", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::bezierTo)
			.def("bezierTo", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::bezierTo)
			.def("bezierTo", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::bezierTo)
			
			.def("quadBezierTo", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::quadBezierTo)
			.def("quadBezierTo", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::quadBezierTo)
			.def("quadBezierTo", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::quadBezierTo)
			
			.def("arc", (void(ofPath::*)(const ofPoint&,float,float,float,float)) &ofPath::arc)
			.def("arc", (void(ofPath::*)(const ofPoint&,float,float,float,float,bool)) &ofPath::arc)
			.def("arc", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::arc)
			.def("arc", (void(ofPath::*)(float,float,float,float,float,float,float)) &ofPath::arc)
			
			.def("arcNegative", (void(ofPath::*)(const ofPoint&,float,float,float,float)) &ofPath::arcNegative)
			.def("arcNegative", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::arcNegative)
			.def("arcNegative", (void(ofPath::*)(float,float,float,float,float,float,float)) &ofPath::arcNegative)
			
			.def("triangle", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::triangle)
			.def("triangle", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::triangle)
			.def("triangle", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::triangle)
			
			.def("circle", (void(ofPath::*)(float,float,float)) &ofPath::circle)
			.def("circle", (void(ofPath::*)(float,float,float,float)) &ofPath::circle)
			.def("circle", (void(ofPath::*)(const ofPoint&,float)) &ofPath::circle)
			
			.def("ellipse", (void(ofPath::*)(float,float,float,float)) &ofPath::ellipse)
			.def("ellipse", (void(ofPath::*)(float,float,float,float,float)) &ofPath::ellipse)
			.def("ellipse", (void(ofPath::*)(const ofPoint&,float,float)) &ofPath::ellipse)
			
			.def("rectangle", (void(ofPath::*)(const ofRectangle&)) &ofPath::rectangle)
			.def("rectangle", (void(ofPath::*)(const ofPoint&,float,float)) &ofPath::rectangle)
			.def("rectangle", (void(ofPath::*)(float,float,float,float)) &ofPath::rectangle)
			.def("rectangle", (void(ofPath::*)(float,float,float,float,float)) &ofPath::rectangle)
			
			.def("rectRounded", (void(ofPath::*)(const ofRectangle&,float)) &ofPath::rectRounded)
			.def("rectRounded", (void(ofPath::*)(const ofPoint&,float,float,float)) &ofPath::rectRounded)
			.def("rectRounded", (void(ofPath::*)(float,float,float,float,float)) &ofPath::rectRounded)
			.def("rectRounded", (void(ofPath::*)(const ofPoint&,float,float,float,float,float,float)) &ofPath::rectRounded)
			.def("rectRounded", (void(ofPath::*)(const ofRectangle&,float,float,float,float)) &ofPath::rectRounded)
			.def("rectRounded", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::rectRounded)
			
			.def("setPolyWindingMode", &ofPath::setPolyWindingMode)
			.def("setFilled", &ofPath::setFilled)
			.def("setStrokeWidth", &ofPath::setStrokeWidth)
			.def("setColor", &ofPath::setColor) // set fill/stroke
			.def("setHexColor", &ofPath::setHexColor) // set fill/stroke
			.def("setFillColor", &ofPath::setFillColor)
			.def("setFillHexColor", &ofPath::setFillHexColor)
			.def("setStrokeColor", &ofPath::setStrokeColor)
			.def("setStrokeHexColor", &ofPath::setStrokeHexColor)
			
			.def("getWindingMode", &ofPath::getWindingMode)
			.def("isFilled", &ofPath::isFilled)
			.property("filled", &ofPath::isFilled)
			.def("getFillColor", &ofPath::getFillColor)
			.def("getStrokeColor", &ofPath::getStrokeColor)
			.def("getStrokeWidth", &ofPath::getStrokeWidth)
			.def("hasOutline", &ofPath::hasOutline)
			.property("outline", &ofPath::hasOutline)
			
			.def("draw", (void(ofPath::*)(float,float)) &ofPath::draw)
			.def("draw", (void(ofPath::*)(void)) &ofPath::draw)
			
			//.def("getOutline", &ofPath::getOutline) // TODO: returns vector
			.def("getTesselation", &ofPath::getTessellation)
			
			.def("simplify", &pathSimplify0)
			.def("simplify", &ofPath::simplify)
			
			.def("flagShapeChanged", &ofPath::flagShapeChanged)
			.def("hasChanged", &ofPath::hasChanged)
			.property("changed", &ofPath::hasChanged)
			
			.def("setMode", &ofPath::setMode)
			.def("getMode", &ofPath::getMode)
			.property("mode", &ofPath::getMode, &ofPath::setMode)
			.enum_("mode") [
				value("COMMANDS", ofPath::COMMANDS),
				value("POLYLINES", ofPath::POLYLINES)
			]
			.def("setCurveResolution", &ofPath::setCurveResolution)
			.def("setCircleResolution", &ofPath::setCircleResolution)
			.def("getCircleResolution", &ofPath::getCircleResolution)
			
			.def("setUseShapeColor", &ofPath::setUseShapeColor)
			.def("getUseShapeColor", &ofPath::getUseShapeColor)
			
			.def("tessellate", &ofPath::tessellate)
			
			.def("translate", &pathTranslate2)
			.def("translate", &ofPath::translate)
			.def("rotate", &pathRotate1)
			.def("rotateX", &pathRotateX)
			.def("rotateY", &pathRotateY)
			.def("rotateZ", &pathRotateZ)
			.def("rotate", &ofPath::rotate)
			.def("rotate", pathRotate4)
			.def("scale", &ofPath::scale),
			
			// skipping commands & command functions
			
		///////////////////////////////
		/// \section ofPixels.h
		
		class_<InterpolationMethod>("INTERPOLATE")
			.enum_("method") [
				value("NEAREST_NEIGHBOR", OF_INTERPOLATE_NEAREST_NEIGHBOR),
				value("BILINEAR", OF_INTERPOLATE_BILINEAR),
				value("BICUBIC", OF_INTERPOLATE_BICUBIC)
			],
		
		class_<ofPixels>("Pixels")
			.def(constructor<>())
			.def(constructor<const ofPixels&>())
			
			.def("allocate", (void(ofPixels::*)(int,int,int)) &ofPixels::allocate)
			.def("allocateWithFormat", (void(ofPixels::*)(int,int,ofPixelFormat)) &ofPixels::allocate)
			.def("allocateWithImageType", (void(ofPixels::*)(int,int,ofImageType)) &ofPixels::allocate)
			
			.def("set", (void(ofPixels::*)(unsigned char)) &ofPixels::set)
			.def("set", (void(ofPixels::*)(int,unsigned char)) &ofPixels::set)
			.def("setFromPixels", &pixelsSetFromPixels)
			.def("setFromPixelsWithImageType", &pixelsSetFromPixelsWithImageType)
			.def("setFromExternalPixels", &pixelsSetFromExternalPixels)
			.def("setFromAlignedPixels", &pixelsSetFromAlignedPixels)
			.def("swap", (void(ofPixels::*)(ofPixels&)) &ofPixels::swap)
			
			.def("crop", &ofPixels::crop)
			.def("cropTo", &ofPixels::cropTo)
			
			.def("rotate90", &pixelsRotate90)
			.def("rotate90", &ofPixels::rotate90)
			.def("rotate90To", &pixelsRotate90To)
			.def("rotate90To", &ofPixels::rotate90To)
			.def("resize", &pixelsResize)
			.def("resize", &ofPixels::resize)
			.def("resizeTo", &pixelsResizeTo)
			.def("resizeTo", &ofPixels::resizeTo)
			.def("pasteInto", &ofPixels::pasteInto)
			
			.def("swapRgb", &ofPixels::swapRgb)
			.def("clear", &ofPixels::clear)
			
			// ignoring getPixels() with pointers
			
			.def("getPixelIndex", &ofPixels::getPixelIndex)
			.def("getColor", &ofPixels::getColor)
			.def("setColor", (void(ofPixels::*)(int,int,const ofColor&)) &ofPixels::setColor)
			.def("setColor", (void(ofPixels::*)(int,const ofColor&)) &ofPixels::setColor)
			.def("setColor", (void(ofPixels::*)(const ofColor&)) &ofPixels::setColor)
			
			// wrapper for [] operator
			.def("getPixel", &pixelsGetPixel)
			.def("setPixel", &pixelsSetPixel)
			
			.def("isAllocated", &ofPixels::isAllocated)
			.property("allocated", &ofPixels::isAllocated)
			
			.def("getWidth", &ofPixels::getWidth)
			.def("getHeight", &ofPixels::getHeight)
			.property("width", &ofPixels::getWidth)
			.property("height", &ofPixels::getHeight)
			
			.def("getBytesPerPixel", &ofPixels::getBytesPerPixel)
			.def("getBitsPerPixel", &ofPixels::getBitsPerPixel)
			.def("getBytesPerChannel", &ofPixels::getBytesPerChannel)
			.def("getBitsPerChannel", &ofPixels::getBitsPerChannel)
			.property("bytesPerPixel", &ofPixels::getBytesPerPixel)
			.property("bitsPerPixel", &ofPixels::getBitsPerPixel)
			.property("bytesPerChannel", &ofPixels::getBytesPerChannel)
			.property("bitsPerChannel", &ofPixels::getBitsPerChannel)
			
			.def("getChannel", &ofPixels::getChannel)
			.def("setChannel", &ofPixels::setChannel)
			.property("channel", &ofPixels::getChannel, &ofPixels::setChannel)
			
			.def("getImageType", &ofPixels::getImageType)
			.def("setImageType", &ofPixels::setImageType)
			.property("imageType", &ofPixels::getImageType, &ofPixels::setImageType)
			
			.def("getNumChannels", &ofPixels::getNumChannels)
			.def("setNumChannels", &ofPixels::setNumChannels)
			.property("numChannels", &ofPixels::getNumChannels, &ofPixels::setNumChannels)
			
			.def("size", &ofPixels::size),
	
		///////////////////////////////
		/// \section ofPolyLine.h
		
		class_<ofPolyline>("Polyline")
			.def(constructor<>())
			
			.def("clear", &ofPolyline::clear)
			
			.def("addVertex", (void(ofPolyline::*)(const ofPoint&)) &ofPolyline::addVertex)
			.def("addVertex", &polylineAddVertex2)
			.def("addVertex", (void(ofPolyline::*)(float,float,float)) &ofPolyline::addVertex)
			// ignoring addVertices which requires pointers
			
			.def("lineTo", (void(ofPolyline::*)(const ofPoint&)) &ofPolyline::lineTo)
			.def("lineTo", &polylineLineTo2)
			.def("lineTo", (void(ofPolyline::*)(float,float,float)) &ofPolyline::lineTo)
			
			.def("insertVertex", (void(ofPolyline::*)(const ofPoint&,int)) &ofPolyline::insertVertex)
			.def("insertVertex", (void(ofPolyline::*)(float,float,float,int)) &ofPolyline::insertVertex)
			
			.def("arc", &polylineArcPoint5)
			.def("arc", (void(ofPolyline::*)(const ofPoint&,float,float,float,float,int)) &ofPolyline::arc)
			.def("arc", &polylineArcPoint6)
			.def("arc", (void(ofPolyline::*)(const ofPoint&,float,float,float,float,bool,int)) &ofPolyline::arc)
			.def("arc", &polylineArcFloat6)
			.def("arc", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::arc)
			.def("arc", &polylineArcFloat7)
			.def("arc", (void(ofPolyline::*)(float,float,float,float,float,float,float,int)) &ofPolyline::arc)
			.def("arcNegative", (void(ofPolyline::*)(const ofPoint&,float,float,float,float,int)) &ofPolyline::arcNegative)
			.def("arcNegative", &polylineArcNegativePoint5)
			.def("arcNegative", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::arcNegative)
			.def("arcNegative", &polylineArcNegativeFloat6)
			.def("arcNegative", (void(ofPolyline::*)(float,float,float,float,float,float,float,int)) &ofPolyline::arcNegative)
			.def("arcNegative", &polylineArcNegativeFloat7)
			
			.def("curveTo", &polylineCurveToPoint1)
			.def("curveTo", (void(ofPolyline::*)(const ofPoint&,int)) &ofPolyline::curveTo)
			.def("curveTo", &polylineCurveToFloat2)
			.def("curveTo", &polylineCurveToFloat3)
			.def("curveTo", (void(ofPolyline::*)(float,float,float,int)) &ofPolyline::curveTo)
			
			.def("bezierTo", &polylineBezierToPoint3)
			.def("bezierTo", (void(ofPolyline::*)(const ofPoint&,const ofPoint&,const ofPoint&, int)) &ofPolyline::bezierTo)
			.def("bezierTo", &polylineBezierToFloat6)
			.def("bezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::bezierTo)
			.def("bezierTo", &polylineBezierToFloat9)
			.def("bezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,float,float,float,int)) &ofPolyline::bezierTo)
			
			.def("quadBezierTo", &polylineQuadBezierToPoint3)
			.def("quadBezierTo", (void(ofPolyline::*)(const ofPoint&,const ofPoint&,const ofPoint&, int)) &ofPolyline::quadBezierTo)
			.def("quadBezierTo", &polylineQuadBezierToFloat6)
			.def("quadBezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::quadBezierTo)
			.def("quadBezierTo", &polylineQuadBezierToFloat9)
			.def("quadBezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,float,float,float,int)) &ofPolyline::quadBezierTo)
			
			.def("getSmoothed", &polylineGetSmoothed1)
			.def("getSmoothed", (void(ofPolyline::*)(int,float)) &ofPolyline::getSmoothed)
			.def("getResampledBySpacing", &ofPolyline::getResampledBySpacing)
			.def("getResampledByCount", &ofPolyline::getResampledByCount)
			.def("getBoundingBox", &ofPolyline::getBoundingBox)
			.def("getClosestPoint", &polylineGetClosestPoint1)
			.def("getClosestPointIndex", &polylineGetClosestPointIndex)
			
			//.def("inside", (bool(ofPolyline::*)(const ofPoint&,const ofPolyline&)) &ofPolyline::inside) // TODO: these are static
			//.def("inside", (bool(ofPolyline::*)(float,float,const ofPolyline&)) &ofPolyline::inside) // TODO: static
			.def("inside", (bool(ofPolyline::*)(const ofPoint&) const) &ofPolyline::inside)
			.def("inside", (bool(ofPolyline::*)(float,float) const) &ofPolyline::inside)
			
			.def("simplify", &polylineSimplify0)
			.def("simplify", &ofPolyline::simplify)
			
			// [] operator access
			.def("size", &ofPolyline::size)
			.def("getPoint", &polylineGetPoint)
			.def("setPoint", &polylineSetPoint)
			.def("resize", &ofPolyline::resize)
			
			.def("setClosed", &ofPolyline::setClosed)
			.def("isClosed", &ofPolyline::isClosed)
			.property("closed", &ofPolyline::isClosed)
			.def("close", &ofPolyline::close)
			
			.def("hasChanged", &ofPolyline::hasChanged)
			.property("changed", &ofPolyline::hasChanged)
			.def("flagHasChanged", &ofPolyline::flagHasChanged)
			
			//.def("getVertices", &ofPolyline::getVertices) // TODO: returns vector
			
			.def("getPerimeter", &ofPolyline::getPerimeter)
			.def("getArea", &ofPolyline::getArea)
			
			.def("getCentroid2D", &ofPolyline::getCentroid2D)
			
			.def("draw", &ofPolyline::draw)
			
			.def("setRightVector", &polylineSetRightVector)
			.def("setRightVector", &ofPolyline::setRightVector)
			.def("getRightVector", &ofPolyline::getRightVector)
			
			.def("getIndexAtLength", &ofPolyline::getIndexAtLength)
			.def("getIndexAtPercent", &ofPolyline::getIndexAtPercent)
			.def("getLengthAtIndex", &ofPolyline::getLengthAtIndex)
			.def("getLengthAtIndexInterpolated", &ofPolyline::getLengthAtIndexInterpolated)
			
			.def("getPointAtLength", &ofPolyline::getPointAtLength)
			.def("getPointAtPercent", &ofPolyline::getPointAtPercent)
			.def("getPointAtIndexInterpolated", &ofPolyline::getPointAtIndexInterpolated)
			
			.def("getAngleAtLength", &ofPolyline::getPointAtLength)
			.def("getAngleAtIndexInterpolated", &ofPolyline::getPointAtIndexInterpolated)
			
			.def("getRotationAtLength", &ofPolyline::getPointAtLength)
			.def("getRotationAtIndexInterpolated", &ofPolyline::getPointAtIndexInterpolated)
			
			.def("getTangentAtLength", &ofPolyline::getPointAtLength)
			.def("getTangentAtIndexInterpolated", &ofPolyline::getPointAtIndexInterpolated)
			
			.def("getNormalAtLength", &ofPolyline::getPointAtLength)
			.def("getNormalAtIndexInterpolated", &ofPolyline::getPointAtIndexInterpolated)
			
			.def("getWrappedIndex", &ofPolyline::getWrappedIndex),
			
		///////////////////////////////
		/// \section ofTrueTypeFont.h
		
		class_<ofTrueTypeFont>("Font")
			.def(constructor<>())
			
			// static functions
			.scope [
				def("setGlobalDpi", &ofTrueTypeFont::setGlobalDpi)
			]
			
			.def("loadFont", &fontLoadFont2)
			.def("loadFont", &fontLoadFont4)
			.def("loadFont", &fontLoadFont5)
			.def("loadFont", &fontLoadFont6)
			.def("loadFont", (void(ofTrueTypeFont::*)(string,int,bool,bool,bool,float,int)) &ofTrueTypeFont::loadFont)
			
			.def("isLoaded", &ofTrueTypeFont::isLoaded)
			.def("isAntiAliased", &ofTrueTypeFont::isAntiAliased)
			.def("hasFullCharacterSet", &ofTrueTypeFont::hasFullCharacterSet)
			
			.def("getSize", &ofTrueTypeFont::getSize)
			.property("size", &ofTrueTypeFont::getSize)
			
			.def("getLineHeight", &ofTrueTypeFont::getLineHeight)
			.def("setLineHeight", &ofTrueTypeFont::setLineHeight)
			.property("lineHeight", &ofTrueTypeFont::getLineHeight, &ofTrueTypeFont::setLineHeight)
			
			.def("getLetterSpacing", &ofTrueTypeFont::getLetterSpacing)
			.def("setLetterSpacing", &ofTrueTypeFont::setLetterSpacing)
			.property("letterSpacing", &ofTrueTypeFont::getLetterSpacing, &ofTrueTypeFont::setLetterSpacing)
			
			.def("getSpaceSize", &ofTrueTypeFont::getSpaceSize)
			.def("setSpaceSize", &ofTrueTypeFont::setSpaceSize)
			.property("spaceSize", &ofTrueTypeFont::getSpaceSize, &ofTrueTypeFont::setSpaceSize)
			
			.def("stringWidth", &ofTrueTypeFont::stringWidth)
			.def("stringHeight", &ofTrueTypeFont::stringHeight)
			
			.def("getStringBoundingBox", &ofTrueTypeFont::getStringBoundingBox)
			
			.def("drawString", &ofTrueTypeFont::drawString)
			.def("drawStringAsShapes", &ofTrueTypeFont::drawStringAsShapes)
			
			.def("getNumCharacters", &ofTrueTypeFont::getNumCharacters)
			.property("numCharacters", &ofTrueTypeFont::getNumCharacters)
			
			.def("getCharacterAsPoints", (ofPath(ofTrueTypeFont::*)(int)) &ofTrueTypeFont::getCharacterAsPoints)
			.def("getCharacterAsPoints", (ofPath(ofTrueTypeFont::*)(int,bool)) &ofTrueTypeFont::getCharacterAsPoints)
			//.def("getStringAsPoints", &ofTrueTypeFont::getStringAsPoints) // TODO: returns vector
			.def("getStringMesh", &ofTrueTypeFont::getStringMesh)
			.def("getFontTexture", &ofTrueTypeFont::getFontTexture)
			
			.def("bind", &ofTrueTypeFont::bind)
			.def("unbind", &ofTrueTypeFont::unbind)
			
			.def("getEncoding", &ofTrueTypeFont::getEncoding)
			.def("setEncoding", &ofTrueTypeFont::setEncoding)
			.property("encoding", &ofTrueTypeFont::getEncoding, &ofTrueTypeFont::setEncoding)
	;
}

} // namespace
