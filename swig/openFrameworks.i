%module of
%{
#include "ofMain.h"
%}

// to help create attibutes from getters/setters
%include <attribute.i>

// ----- STL -----

%include <typemaps.i>
%include <stl.i>

%template(FloatVector) std::vector<float>;
%template(StringVector) std::vector<std::string>;

// ----- Classes for Lua -----

// support for simple classes from http://lua-users.org/wiki/SimpleLuaClasses
%luacode {
-- class.lua
-- Compatible with Lua 5.1 (not 5.0).
function class(base, __init)
   local c = {}    -- a new class instance
   if not __init and type(base) == 'function' then
      __init = base
      base = nil
   elseif type(base) == 'table' then
    -- our new class is a shallow copy of the base class!
      for i,v in pairs(base) do
         c[i] = v
      end
      c._base = base
   end
   -- the class will be the metatable for all its objects,
   -- and they will look up their methods in it.
   c.__index = c

   -- expose a constructor which can be called by <classname>(<args>)
   local mt = {}
   mt.__call = function(class_tbl, ...)
   local obj = {}
   setmetatable(obj,c)
   if class_tbl.__init then
      class_tbl.__init(obj,...)
   else 
      -- make sure that any stuff from the base class is initialized!
      if base and base.__init then
      base.__init(obj, ...)
      end
   end
   return obj
   end
   c.__init = __init
   c.is_a = function(self, klass)
      local m = getmetatable(self)
      while m do 
         if m == klass then return true end
         m = m._base
      end
      return false
   end
   setmetatable(c, mt)
   return c
end

}

// ----- UTILS -----------------------------------------------------------------

// ----- ofConstants.h -----

%include "utils/ofConstants.h"

// ----- TYPES -----------------------------------------------------------------

// ----- ofBaseTypes.h -----

%ignore ofBaseApp;
%ignore ofBaseDraws;
%ignore ofBaseFileSerializer;
%ignore ofBaseHasPixels;
%ignore ofBaseImage;
%ignore ofBaseRenderer;
%ignore ofBaseSerializer;
%ignore ofBaseSoundInput;
%ignore ofBaseSoundOutput;
%ignore ofBaseUpdates;
%ignore ofBaseVideo;
%ignore ofBaseVideoDraws;
%ignore ofBaseVideoGrabber;
%ignore ofBaseVideoPlayer;

%ignore of3dPrimitive;

%ignore ofAppBaseWindow;

%include "types/ofBaseTypes.h"

//%template(BaseDraws) ofBaseDraws;
//%template(BaseHasTexture) ofBaseHasTexture;

//%template(AbstractHasPixels) ofAbstractHasPixels;
//%template(AbstractImage) ofAbstractImage;

//%template(BaseHasPixels) ofBaseHasPixels_<unsigned char>;
//%template(BaseHasFloatPixels) ofBaseHasPixels_<float>;
//%template(BaseHasShortPixels) ofBaseHasPixels_<unsigned short>;

//%template(BaseImage) ofBaseImage_<unsigned char>;
//%template(BaseFloatImage) ofBaseImage_<float>;
//%template(BaseShortImage) ofBaseImage_<unsigned short>;

// ----- ofTypes.h -----

// not sure if those are needed in lua
%ignore ofSerial;
%ignore ofSerialDeviceInfo;
%ignore ofVideoFormat;
%ignore ofVideoDevice;

// these don't seem to work in lua
%rename(Mutex) ofMutex;
%rename(ScopedLock) ofScopedLock;

%rename(Style) ofStyle;

// probably don't need this in lua
%ignore ofPtr;

%include "types/ofTypes.h"

// ----- ofUtils.h -----

%rename(nextPow2) ofNextPow2;

%rename(resetElapsedTimeCounter) ofResetElapsedTimeCounter;
%rename(getElapsedTimef) ofGetElapsedTimef;
%rename(getElapsedTimeMillis) ofGetElapsedTimeMillis;
%rename(getElapsedTimeMicros) ofGetElapsedTimeMicros;
%rename(getFraneNum) ofGetFrameNum;

%rename(getSeconds) ofGetSeconds;
%rename(getMinutes) ofGetMinutes;
%rename(getHours) ofGetHours;

%rename(getUnixTime) ofGetUnixTime;

%rename(getSystemTime) ofGetSystemTime;
%rename(getSystemTimeMicros) ofGetSystemTimeMicros;

%rename(getTimestampString) ofGetTimestampString;

%rename(getYear) ofGetYear;
%rename(getMonth) ofGetMonth;
%rename(getDay) ofGetDay;
%rename(getWeekday) ofGetWeekday;

%rename(launchBrowser) ofLaunchBrowser;

%rename(enableDataPath) ofEnableDataPath;
%rename(disableDataPath) ofDisableDataPath;
%rename(toDataPath) ofToDataPath;

%rename(setWorkingDirectoryToDefault) ofSetWorkingDirectoryToDefault;
%rename(setDataPathRoot) ofSetDataPathRoot;

// use lua tostring() or the string library
%ignore ofToString;

// use the lua string conversions
%ignore ofFromString;

%ignore ofToHex;
%ignore ofHexToInt;
%ignore ofHexToChar;
%ignore ofHexToFloat;
%ignore ofHexToString;

%ignore ofToInt;
%ignore ofToChar;
%ignore ofToFloat;
%ignore ofToDouble;
%ignore ofToBool;

%ignore ofToBinary;
%ignore ofBinaryToInt;
%ignore ofBinaryToChar;
%ignore ofBinaryToFloat;
%ignore ofBinaryToString;

%rename(getVersionInfo) ofGetVersionInfo;
%rename(getVersionMajor) ofGetVersionMajor;
%rename(getVersionMinor) ofGetVersionMinor;
%rename(getVersionPath) ofGetVersionPatch;

%rename(saveScreen) ofSaveScreen;
%rename(saveFrame) ofSaveFrame;
%rename(saveViewport) ofSaveViewport;

// these are possible with the lua string library, but keep them for now
%rename(splitString) ofSplitString;
%rename(joinString) ofJoinString;
%rename(stringReplace) ofStringReplace;
%rename(isStringInString) ofIsStringInString;
%rename(stringTimeInString) ofStringTimeInString;

%rename(toLower) ofToLower;
%rename(toUpper) ofToUpper;

// no VAARGS
%ignore ofVAArgsToString;

// allow this for now, but I think you can do this with the lua system lib ...
%rename(system) ofSystem;

%rename(getTargetPlatform) ofGetTargetPlatform;

%include "utils/ofUtils.h"

// ----- ofColor.h -----

%extend ofColor_<unsigned char> {

	// getters for nested union data which isn't wrapped by SWIG,
	// ugly in lua land, I would rather have color.r, color.g, etc ...
	unsigned char getR() {return self->r;}
	unsigned char getG() {return self->g;}
	unsigned char getB() {return self->b;}
	unsigned char getA() {return self->a;}

	void setR(unsigned char r) {self->r = r;}
	void setG(unsigned char g) {self->g = g;}
	void setB(unsigned char b) {self->b = b;}
	void setA(unsigned char a) {self->a = a;}

	// tostring wrapper for operator <<
	const char* __str__() {
		stringstream str;
		str << (*self);
		return str.str().c_str();
	}
};
/*
%attribute(ofColor_, unsigned char, R, getR, setR);
%attribute(ofColor_, unsigned char, G, getG, setG);
%attribute(ofColor_, unsigned char, B, getB, setB);
%attribute(ofColor_, unsigned char, A, getA, setA);
*/
%include "types/ofColor.h"

%template(Color) ofColor_<unsigned char>;
//%template(FloatColor) ofColor_<float>;
//%template(ShortColor) ofColor_<unsigned short>;

// ----- ofPoint.h -----

%rename(Point) ofPoint;

%include "types/ofPoint.h"

// ----- ofRectangle.h -----

// %ignore ofRectangle::x;
// %ignore ofRectangle::y;

// SWIG converts the x & y float & types into pointers,
// so specify x & y as attributes using the get & set functions
%attribute(ofRectangle, float, x, getX, setX);
%attribute(ofRectangle, float, y, getY, setY);

%rename(scaleTo) ofRectangle::scaleTo(ofRectangle const &, ofScaleMode);
%rename(scaleTo) ofRectangle::scaleTo(ofRectangle const &, ofAspectRatioMode);

%rename(Rectangle) ofRectangle;

%include "types/ofRectangle.h"

// ----- MATH ------------------------------------------------------------------

// ----- ofMatrix3x3.h -----

%rename(Matrix3x3) ofMatrix3x3;

%include "math/ofMatrix3x3.h"

// ----- ofMatrix4x4.h -----

%rename(Matrix4x4) ofMatrix4x4;

ofMatrix4x4::operator()(int,int);
ofMatrix4x4::operator()(int,int) const;

// defined, but currently not implemented
%ignore ofVec4f::set(float);

%include "math/ofMatrix4x4.h"

// ----- ofQuaternion.h -----

%rename(Quaternion) ofQuaternion;

%include "math/ofQuaternion.h"

// ----- ofVecs -----

%rename(Vec2f) ofVec2f;
%rename(Vec3f) ofVec3f;
%rename(Vec4f) ofVec4f;

%include "math/ofVec2f.h"
%include "math/ofVec3f.h"
%include "math/ofVec4f.h"

// ----- ofMath.h -----

%rename(nextPow2) ofNextPow2;
%rename(seedRandom) ofSeedRandom;
%rename(random) ofRandom;
%rename(randomf) ofRandomf;
%rename(randomuf) ofRandomuf;

%rename(normalize) ofNormalize;
%rename(map) ofMap;
%rename(clamp) ofClamp;
%rename(lerp) ofLerp;
%rename(dist) ofDist;
%rename(distSquared) ofDistSquared;
%rename(sign) ofSign;
%rename(inRange) ofInRange;

%rename(radToDeg) ofRadToDeg;
%rename(degToRad) ofDegToRad;
%rename(lerpDegrees) ofLerpDegrees;
%rename(lerpRadians) ofLerpRadians;
%rename(angleDifferenceDegrees) ofAngleDifferenceDegrees;
%rename(angleDifferenceRadians) ofAngleDifferenceRadians;
%ignore ofAngleSumRadians; // defined, but currently not implemented
%rename(wrap) ofWrap;
%rename(wrapRadians) ofWrapRadians;
%rename(wrapDegrees) ofWrapDegrees;

%rename(randomWidth) ofRandomWidth;
%rename(randomHeight) ofRandomHeight;

%rename(noise) ofNoise;
%rename(signedNoise) ofSignedNoise;

%rename(insidePoly) ofInsidePoly;
%rename(lineSegmentIntersection) ofLineSegmentIntersection;

%rename(bezierPoint) ofBezierPoint;
%rename(curvePoint) ofCurvePoint;
%rename(bezierTangent) ofBezierTangent;
%rename(curveTangent) ofCurveTangent;

%ignore ofInterpolateCosine;
//ofInterpolateCosine(float y1, float y2, float pct);

%include "math/ofMath.h"

%template(interpolateCosine) ofInterpolateCosine<float>;

// ----- GRAPHICS --------------------------------------------------------------

// ----- ofPixels.h -----

%include "graphics/ofPixels.h"

%template(Pixels) ofPixels_<unsigned char>;
//%template(FloatPixels) ofPixels_<float>;
//%template(ShortPixels) ofPixels_<unsigned short>;

// ----- ofPath.h -----

// defined, but currently not implemented
%ignore ofPath::getCurveResolution() const;

%rename(Path) ofPath;

%include "graphics/ofPath.h"

// ----- ofPolyline.h -----

%rename(Polyline) ofPolyline;

%include "graphics/ofPolyline.h"

// ----- ofGraphics.h -----

// hide default define
%ignore CIRC_RESOLUTION;

// not application to lua
%ignore ofSetCurrentRenderer;
%ignore ofGetCurrentRenderer;

%rename(beginSaveScreenAsPDF) ofBeginSaveScreenAsPDF;
%rename(endSaveScreenAsPDF) ofEndSaveScreenAsPDF;

%rename(pushView) ofPushView;
%rename(popView) ofPopView;

%rename(viewport) ofViewport;

%rename(isVFlipped) ofIsVFlipped;

%rename(setupScreenPerspective) ofSetupScreenPerspective;
%rename(setupScreenOrtho) ofSetupScreenOrtho;

// deprecated (all overloaded funcs too ...)
%ignore ofSetupScreenPerspective(float, float, ofOrientation);
%ignore ofSetupScreenPerspective(float, float, ofOrientation, bool);
%ignore ofSetupScreenPerspective(float, float, ofOrientation, bool, float);
%ignore ofSetupScreenPerspective(float, float, ofOrientation, bool, float, float);
%ignore ofSetupScreenPerspective(float, float, ofOrientation, bool, float, float, float);
%ignore ofSetupScreenOrtho(float, float, ofOrientation);
%ignore ofSetupScreenOrtho(float, float, ofOrientation, bool);
%ignore ofSetupScreenOrtho(float, float, ofOrientation, bool, float);
%ignore ofSetupScreenOrtho(float, float, ofOrientation, bool, float, float);

%rename(getCurrentViewport) ofGetCurrentViewport;
%rename(getNativeViewport) ofGetNativeViewport;
%rename(getViewportWidth) ofGetViewportWidth;
%rename(getViewportHeight) ofGetViewportHeight;
%rename(orientationToDegrees) ofOrientationToDegrees;

%rename(setCoordHandedness) ofSetCoordHandedness;
%rename(getCoordHandedness) ofGetCoordHandedness;

%rename(pushMatrix) ofPushMatrix;
%rename(popMatrix) ofPopMatrix;
%rename(translate) ofTranslate;
%rename(scale) ofScale;
%rename(rotate) ofRotate;
%rename(rotateX) ofRotateX;
%rename(rotateY) ofRotateY;
%rename(rotateZ) ofRotateZ;
%rename(loadIdentity) ofLoadIdentityMatrix;
%rename(loadMatrix) ofLoadMatrix;
%rename(multMatrix) ofMultMatrix;
%rename(setMatrixMode) ofSetMatrixMode;

%rename(setupGraphicDefaults) ofSetupGraphicDefaults;
%rename(setupScreen) ofSetupScreen;

%rename(getRectmode) ofGetRectMode;

%rename(setCircleResolution) ofSetCircleResolution;
%rename(setCurveResolution) ofSetCurveResolution;

%rename(noFill) ofNoFill;
%rename(fill) ofFill;
%rename(getFill) ofGetFill;

%rename(setLineWidth) ofSetLineWidth;
%rename(setDepthTest) ofSetDepthTest;
%rename(enableDepthTest) ofEnableDepthTest;
%rename(disableDepthTest) ofDisableDepthTest;

%rename(setColor) ofSetColor;
%rename(setHexColor) ofSetHexColor;

%rename(enableBlendMode) ofEnableBlendMode;
%rename(disableBlendMode) ofDisableBlendMode;

%rename(enablePointSprites) ofEnablePointSprites;
%rename(disablePointSprites) ofDisablePointSprites;

%rename(enableAlphaBlending) ofEnableAlphaBlending;
%rename(disableAlphaBlending) ofDisableAlphaBlending;

%rename(enableSmoothing) ofEnableSmoothing;
%rename(disableSmoothing) ofDisableSmoothing;

%rename(enableAntiAliasing) ofEnableAntiAliasing;
%rename(disableAntiAliasing) ofDisableAntiAliasing;

%rename(getStyle) ofGetStyle;
%rename(setStyle) ofSetStyle;
%rename(pushStyle) ofPushStyle;
%rename(popStyle) ofPopStyle;

%rename(setPolyMode) ofSetPolyMode;
%rename(setRectMode) ofSetRectMode;

// don't need pointer in lua?
%ignore ofBgColorPtr;

%rename(getBackground) ofGetBackground;
%rename(background) ofBackground;
%rename(backgroundHex) ofBackgroundHex;
%rename(backgroundGradient) ofBackgroundGradient;

%rename(setBackgroundColor) ofSetBackgroundColor;
%rename(setBackgroundColorHex) ofSetBackgroundColorHex;

%rename(setBackgroundAuto) ofSetBackgroundAuto;

%rename(clear) ofClear;
%rename(clearAlpha) ofClearAlpha;

// not needed in lua?
%ignore ofbClearBg;

%rename(triangle) ofTriangle;
%rename(circle) ofCircle;
%rename(ellipse) ofEllipse;
%rename(line) ofLine;
%rename(rect) ofRect;
%rename(rectRounded) ofRectRounded;
%ignore ofRectRounded(float, float, float, float, float, float);
%rename(curve) ofCurve;
%rename(bezier) ofBezier;

%rename(beginShape) ofBeginShape;
%rename(vertex) ofVertex;
%rename(vertices) ofVertices;
%rename(curveVertex) ofCurveVertex;
%rename(bezierVertex) ofBezierVertex;
%rename(endShape) ofEndShape;
%rename(nextContour) ofNextContour;

%rename(setDrawBitmapMode) ofSetDrawBitmapMode;
%rename(drawBitmapString) ofDrawBitmapString;
%rename(drawBitmapStringHighlight) ofDrawBitmapStringHighlight;

%include "graphics/ofGraphics.h"

// ----- of3dGraphics.h -----

%rename(setPlaneResolution) ofSetPlaneResolution;
%rename(getPlaneResolution) ofGetPlaneResolution;
%rename(drawPlane) ofDrawPlane;

%rename(setSphereResolution) ofSetSphereResolution;
%rename(getSphereResolution) ofGetSphereResolution;
%rename(drawSphere) ofDrawSphere;

%rename(setIcoSphereResolution) ofSetIcoSphereResolution;
%rename(getIcoSphereResolution) ofGetIcoSphereResolution;
%rename(drawIcoSphere) ofDrawIcoSphere;

%rename(setCylinderResolution) ofSetCylinderResolution;
%rename(getCylinderResolution) ofGetCylinderResolution;
%rename(drawCylinder) ofDrawCylinder;

%rename(setConeResolution) ofSetConeResolution;
%rename(getConeResolution) ofGetConeResolution;
%rename(drawCone) ofDrawCone;

%rename(setBoxResolution) ofSetBoxResolution;
%rename(getBoxResolution) ofGetBoxResolution;
%rename(drawBox) ofDrawBox;

// deprecated
%ignore ofSphere;
%ignore ofCode;
%ignore ofBox;

%include "graphics/of3dGraphics.h"

// ----- 3d --------------------------------------------------------------------

// ----- of3dUtils.h -----

%rename(drawAxis) ofDrawAxis;
%rename(drawGrid) ofDrawGrid;
%rename(drawGridPlane) ofDrawGridPlane;
%rename(drawArrow) ofDrawArrow;
%rename(drawRotationAxes) ofDrawRotationAxes;

%include "3d/of3dUtils.h"

// ----- ofNode.h -----

%rename(Node) ofNode;

%include "3d/ofNode.h"

// ----- ofMesh.h -----

// defined, but currently not implemented 
%ignore ofMesh::getFace(int);

%rename(Mesh) ofMesh;

%include "3d/ofMesh.h"

// ----- ofImage.h -----

// hide helper functions
%ignore ofLoadImage;
%ignore ofSaveImage;
%ignore ofCloseFreeImage;

//%rename(Image) ofImage;

%include "graphics/ofImage.h"

%template(Image) ofImage_<unsigned char>;
//%template(FloatImage) ofImage_<float>;
//%template(ShortImage) ofImage_<unsigned short>;

// ----- ofTrueTypeFont.h -----

%rename(Font) ofTrueTypeFont;

// SWIGS fails on the static strings when including ofTrueTypeFont.h, so define
// the class to be wrapped here for now
class ofTrueTypeFont{

public:

	ofTrueTypeFont();
	virtual ~ofTrueTypeFont();
	
	static void setGlobalDpi(int newDpi);
			
	bool loadFont(string filename, int fontsize, bool _bAntiAliased=true,
		bool _bFullCharacterSet=false, bool makeContours=false,
		float simplifyAmt=0.3, int dpi=0);
	
	bool isLoaded();
	bool isAntiAliased();
	bool hasFullCharacterSet();

    int getSize();
    float getLineHeight();
  	void setLineHeight(float height);
	float getLetterSpacing();
	void setLetterSpacing(float spacing);
	float getSpaceSize();
	void setSpaceSize(float size);
	float stringWidth(string s);
	float stringHeight(string s);
	
	ofRectangle getStringBoundingBox(string s, float x, float y);
	
	void drawString(string s, float x, float y);
	void drawStringAsShapes(string s, float x, float y);
	
	int getNumCharacters();	
	
	ofTTFCharacter getCharacterAsPoints(int character, bool vflip=ofIsVFlipped());
	vector<ofTTFCharacter> getStringAsPoints(string str, bool vflip=ofIsVFlipped());
	ofMesh & getStringMesh(string s, float x, float y);
	ofTexture & getFontTexture();

	void bind();
	void unbind();

	ofTextEncoding getEncoding() const;
	void setEncoding(ofTextEncoding encoding);
};

// ----- GL --------------------------------------------------------------------

// ----- ofFbo.h -----

%rename(Fbo) ofFbo;

%include "gl/ofFbo.h"

// ----- ofLight.h -----

%rename(Light) ofLight;

%include "gl/ofLight.h"

// ----- ofMaterial.h -----

%rename(Material) ofMaterial;

%include "gl/ofMaterial.h"

// ----- ofShader.h -----

%rename(Shader) ofShader;

%include "gl/ofShader.h"

// ----- ofVbo.h -----

%rename(Vbo) ofVbo;

%include "gl/ofVbo.h"

// ----- ofVboMesh.h -----

%rename(VboMesh) ofVboMesh;

%include "gl/ofVboMesh.h"

// ----- ofTexture.h -----

%rename(getUsingArbTex) ofGetUsingArbTex;
%rename(enableArbTex) ofEnableArbTex;
%rename(disableArbTex) ofDisableArbTex;

%rename(getUsingNormalizedTexCoords) ofGetUsingNormalizedTexCoords;
%rename(enableNormalizedTexCoords) ofEnableNormalizedTexCoords;
%rename(disableNormalizedTexCoords) ofDisableNormalizedTexCoords;

// ignore these for now, need to wrap the GL enums ...
%ignore ofSetTextureWrap;
%ignore ofGetUsingCustomTextureWrap;
%ignore ofRestoreTextureWrap;
%ignore ofSetMinMagFilters;
%ignore ofGetUsingCustomMinMagFilters;
%ignore ofRestoreMinMagFilters;

%rename(TextureData) ofTextureData;
%rename(Texture) ofTexture;

// ignore hacks
%ignore ofEnableTextureEdgeHack;
%ignore ofDisableTextureEdgeHack;
%ignore ofIsTextureEdgeHackEnabled;

%include "gl/ofTexture.h"

// ----- APP -------------------------------------------------------------------

// ----- ofAppRunner.h -----

%rename(setupOpenGL) ofSetupOpenGL;
%ignore ofSetupOpenGL(ofAppBaseWindow *, int, int, int); // deprecated

%rename(runApp) ofRunApp(ofPtr<ofBaseApp>);
%ignore ofRunApp(ofBaseApp *); // deprecated

%rename(getAppPtr) ofGetAppPtr;
%ignore ofSetAppPtr; // not applicable to lua?

%rename(exit) ofExit;

%rename(getFrameRate) ofGetFrameRate;
%rename(getTargetFrameRate) ofGetTargetFrameRate;
%rename(getFrameNum) ofGetFrameNum;
%rename(setFrameRate) ofSetFrameRate;
%rename(sleepMillis) ofSleepMillis;
%rename(getLastFrameTime) ofGetLastFrameTime;

%rename(setOrientation) ofSetOrientation;
%rename(getOrientation) ofGetOrientation;

%rename(hideCursor) ofHideCursor;
%rename(showCursor) ofShowCursor;

%rename(getWindowPositionX) ofGetWindowPositionX;
%rename(getWindowPositionY) ofGetWindowPositionY;
%rename(getScreenWidth) ofGetScreenWidth;
%rename(getScreenHeight) ofGetScreenHeight;
%rename(getWindowMode) ofGetWindowMode;
%rename(getWidth) ofGetWidth;
%rename(getHeight) ofGetHeight;
%rename(getWindowWidth) ofGetWindowWidth;
%rename(getWindowHeight) ofGetWindowHeight;
%rename(doesHWOrientation) ofDoesHWOrientation;
%rename(getWindowSize) ofGetWindowSize;
%rename(getWindowRect) ofGetWindowRect;
%rename(getWindowPtr) ofGetWindowPtr;

%rename(setWindowPosition) ofSetWindowPosition;
%rename(setWindowShape) ofSetWindowShape;
%rename(setWindowTitle) ofSetWindowTitle;
%rename(enableSetupScreen) ofEnableSetupScreen;
%rename(disableSetupScreen) ofDisableSetupScreen;
%rename(setFullscreen) ofSetFullscreen;
%rename(toggleFullscreen) ofToggleFullscreen;

%rename(setVerticalSync) ofSetVerticalSync(bool bSync);

// no api-specific window objects yet
%ignore ofGetX11Display;
%ignore ofGetX11Window;
%ignore ofGetGLXContext;
%ignore ofGetEGLDisplay;
%ignore ofGetEGLContext;
%ignore ofGetEGLSurface;
%ignore ofGetNSGLContext;
%ignore ofGetCocoaWindow;
%ignore ofGetWGLContext;
%ignore ofGetWin32Window;

%include "app/ofAppRunner.h"

// ----- EVENTS ----------------------------------------------------------------

// ----- ofEvents.h -----

%rename(getMousePressed) ofGetMousePressed;
%rename(getKeyPressed) ofGetKeyPressed;
%rename(getMouseX) ofGetMouseX;
%rename(getMouseY) ofGetMouseY;
%rename(getPreviousMouseX) ofGetPreviousMouseX;
%rename(getPreviousMouseY) ofGetPreviousMouseY;
%rename(setEscapeQuitsApp) ofSetEscapeQuitsApp;

%rename(DragInfo) ofDragInfo;

// include declarations here as this is easier than including file since we'd
// need to ignore all of the internal OF event stuff
bool ofGetMousePressed(int button=-1);
bool ofGetKeyPressed(int key=-1);
int	ofGetMouseX();
int	ofGetMouseY();
int	ofGetPreviousMouseX();
int	ofGetPreviousMouseY();
void ofSetEscapeQuitsApp(bool bQuitOnEsc);
void exitApp(); 

class ofDragInfo{
	public:
		vector <string> files;
		ofPoint position;
};

// ----- SOUND -----------------------------------------------------------------

// ----- ofSoundStream.h -----

%rename(soundStreamSetup) ofSoundStreamSetup;
%rename(soundStreamStop) ofSoundStreamStop;
%rename(soundStreamStart) ofSoundStreamStart;
%rename(soundStreamClose) ofSoundStreamClose;
%rename(soundStreamListDevices) ofSoundStreamListDevices;

%rename(SoundStream) ofSoundStream;

%include "sound/ofSoundStream.h"

// ----- ofSoundPlayer.h -----

// warnings in the header say "FIX THIS SHIT", so leave them out ...
%ignore ofSoundStopAll;
%ignore ofSoundSetVolume;
%ignore ofSoundUpdate;
%ignore ofSoundGetSpectrum;
%ignore ofSoundShutdown;

%rename(SoundPlayer) ofSoundPlayer;

%include "sound/ofSoundPlayer.h"
