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
#include "ofColor.h"
#include "ofTypes.h"
#include "ofRectangle.h"
#include "ofxLua.h"
#include <luabind/operator.hpp>

namespace bindings {

// wrapper functions needed for overloading

// color
void colorSet1(ofColor* color, float gray) {color->set(gray);}
void colorSet3(ofColor* color, float r, float g, float b) {color->set(r, g, b);}
void colorSetHsb3(ofColor* color, float hue, float saturation, float brightness)
	{color->setHsb(hue, saturation, brightness);}
void colorCopyColor(ofColor* color, ofColor &c) {(*color) = c;}
void colorCopyFloat(ofColor* color, float val) {(*color) = val;}
ofColor colorFromHsb3(float hue, float saturation, float brightness)
	{return ofColor::fromHsb(hue, saturation, brightness);}
ofColor colorFromHex1(int hexColor) {return ofColor::fromHex(hexColor);}

// rectangle
void rectScaleTo2(ofRectangle* rect, const ofRectangle& targetRect,
	ofAspectRatioMode subjectAspectRatioMode)
	{rect->scaleTo(targetRect, subjectAspectRatioMode);}
void rectScaleTo3(ofRectangle* rect, const ofRectangle& targetRect,
	ofAspectRatioMode subjectAspectRatioMode, ofAlignHorz sharedHorzAnchor)
	{rect->scaleTo(targetRect, subjectAspectRatioMode, sharedHorzAnchor);}

void rectAlignToHorzFloat(ofRectangle* rect, const float& targetX)
	{rect->alignToHorz(targetX);}
void rectAlignToHorzRect(ofRectangle* rect, const ofRectangle& targetRect)
	{rect->alignToHorz(targetRect);}

void rectAlignToVertFloat(ofRectangle* rect, const float& targetY)
	{rect->alignToVert(targetY);}
void rectAlignToVertRect(ofRectangle* rect, const ofRectangle& targetRect)
	{rect->alignToVert(targetRect);}

void rectAlignToPoint1(ofRectangle* rect, const ofPoint& targetPoint)
	{rect->alignTo(targetPoint);}
void rectAlignToPoint2(ofRectangle* rect, const ofPoint& targetPoint,
	ofAlignHorz thisHorzAnchor)
	{rect->alignTo(targetPoint, thisHorzAnchor);}
    
void rectAlignToRect1(ofRectangle* rect, const ofRectangle& targetRect,
	ofAlignHorz sharedHorzAnchor)
	{rect->alignTo(targetRect, sharedHorzAnchor);}
void rectAlignToRect2(ofRectangle* rect, const ofRectangle& targetRect)
	{rect->alignTo(targetRect);}

void rectCopy(ofRectangle *rect, const ofRectangle &r) {(*rect) = r;}

// luabind registration
luabind::scope registerTypes() {

	using namespace luabind;

	return
		
		///////////////////////////////
		/// \section ofColor.h
		
		class_<ofColor>("Color")
			.def(constructor<>())
			.def(constructor<float,float,float>())
			.def(constructor<float,float,float,float>())
			.def(constructor<ofColor&>())
			.def(constructor<ofColor&,float>())
			.def(constructor<float>())
			.def(constructor<float,float>())
			
			.def("set", &colorSet1)
			.def("set", (void(ofColor::*)(float,float)) &ofColor::set)
			.def("set", &colorSet3)
			.def("set", (void(ofColor::*)(float,float,float,float)) &ofColor::set)
			.def("setHex", &ofColor::setHex)
			.def("getHex", &ofColor::getHex)
			
			.def("clamp", &ofColor::clamp)
			.def("invert", &ofColor::invert)
			.def("normalize", &ofColor::normalize)
			.def("lerp", &ofColor::lerp)
			
			.def("getClamped", &ofColor::getClamped)
			.def("getInverted", &ofColor::getInverted)
			.def("getNormalized", &ofColor::getNormalized)
			.def("getLerped", &ofColor::getLerped)
			
			.def("getHue", &ofColor::getHue)
			.def("getSaturation", &ofColor::getSaturation)
			.def("getBrightness", &ofColor::getBrightness)
			.def("getLightness", &ofColor::getLightness)
			//.def("getHsb", &ofColor::getHsb) // float refs , works in lua?
			
			.def("setHue", &ofColor::setHue)
			.def("setSaturation", &ofColor::setSaturation)
			.def("setBrightness", &ofColor::setBrightness)
			.def("setHsb", &colorSetHsb3)
			.def("setHsb", &ofColor::setHsb)
			
			.def("copy", &colorCopyColor) // operator =
			.def("copy", &colorCopyFloat) // operator =
			
			.def(self == other<const ofColor&>())
			.def(self + other<const ofColor&>())
			.def(self + other<const float>())
			.def(self - other<const ofColor&>())
			.def(self - other<const float>())
			.def(self * other<const ofColor&>())
			.def(self * other<const float>())
			.def(self / other<const ofColor&>())
			.def(self / other<const float>())
			.def(tostring(self)) // uses ostream << operator
			.def("limit", &ofColor::limit)
			.def_readwrite("r", &ofColor::r)
			.def_readwrite("g", &ofColor::g)
			.def_readwrite("b", &ofColor::b)
			.def_readwrite("a", &ofColor::a),
			// TODO: make the static color bindings work
			//.def_readonly("white", &ofColor::white)
			//.def_readonly("gray", &ofColor::gray)
			//.def_readonly("black", &ofColor::black)
			//.def_readonly("red", &ofColor::red)
			//.def_readonly("green", &ofColor::green)
			//.def_readonly("blue", &ofColor::blue)
			//.def_readonly("cyan", &ofColor::cyan)
			//.def_readonly("magenta", &ofColor::magenta)
			//.def_readonly("yellow", &ofColor::yellow),
			
		/// static color creators
		def("colorFromHsb", &colorFromHsb3),
		def("colorFromHsb", &ofColor::fromHsb),
		def("colorFromHex", &colorFromHex1),
		def("colorFromHex", &ofColor::fromHex),
			
		///////////////////////////////
		/// \section ofRectangle.h
		
		class_<ofRectangle>("Rectangle")
			.def(constructor<>())
			.def(constructor<float,float,float,float>())
			.def(constructor<const ofPoint&,float,float>())
			.def(constructor<const ofRectangle&>())
			.def(constructor<const ofPoint&,const ofPoint&>())
			
			.def("set", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::set)
			.def("set", (void(ofRectangle::*)(const ofPoint&,const ofPoint&)) &ofRectangle::set)
			.def("set", (void(ofRectangle::*)(const ofPoint&,float,float)) &ofRectangle::set)
			.def("set", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::set)
			
			.def("setFromCenter", (void(ofRectangle::*)(const ofPoint&,float,float)) &ofRectangle::setFromCenter)
			.def("setFromCenter", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::setFromCenter)
			
			.def("translate", (void(ofRectangle::*)(float,float)) &ofRectangle::translate)
			.def("translate", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::translate)
			
			.def("translateX", &ofRectangle::translateX)
			.def("translateY", &ofRectangle::translateY)
			
			.def("scale", (void(ofRectangle::*)(float)) &ofRectangle::scale)
			.def("scale", (void(ofRectangle::*)(float,float)) &ofRectangle::scale)
			.def("scale", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::scale)
			
			.def("scaleWidth", &ofRectangle::scaleWidth)
			.def("scaleHeight", &ofRectangle::scaleHeight)
			
			.def("scaleFromCenter", (void(ofRectangle::*)(float)) &ofRectangle::scaleFromCenter)
			.def("scaleFromCenter", (void(ofRectangle::*)(float,float)) &ofRectangle::scaleFromCenter)
			.def("scaleFromCenter", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::scaleFromCenter)
			
			.def("scaleTo", &rectScaleTo2)
			.def("scaleTo", &rectScaleTo3)
			.def("scaleTo", (void(ofRectangle::*)(const ofRectangle&,ofAspectRatioMode,ofAlignHorz,ofAlignVert)) &ofRectangle::scaleTo)
			.def("scaleTo", (void(ofRectangle::*)(const ofRectangle&,ofAspectRatioMode,ofAlignHorz,ofAlignVert,ofAlignHorz,ofAlignVert)) &ofRectangle::scaleTo)
			
			.def("alignToHorz", &rectAlignToHorzFloat)
			.def("alignToHorz", (void(ofRectangle::*)(const float&,ofAlignHorz)) &ofRectangle::alignToHorz)
			.def("alignToHorz", &rectAlignToHorzRect)
			.def("alignToHorz", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz)) &ofRectangle::alignToHorz)
			.def("alignToHorz", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz,ofAlignHorz)) &ofRectangle::alignToHorz)
			
			.def("alignToVert", &rectAlignToVertFloat)
			.def("alignToVert", (void(ofRectangle::*)(const float&,ofAlignVert)) &ofRectangle::alignToVert)
			.def("alignToVert", &rectAlignToVertRect)
			.def("alignToVert", (void(ofRectangle::*)(const ofRectangle&,ofAlignVert)) &ofRectangle::alignToVert)
			.def("alignToVert", (void(ofRectangle::*)(const ofRectangle&,ofAlignVert,ofAlignVert)) &ofRectangle::alignToVert)
			
			.def("alignTo", &rectAlignToPoint1)
			.def("alignTo", &rectAlignToPoint2)
			.def("alignTo", (void(ofRectangle::*)(const ofPoint&,ofAlignHorz,ofAlignVert)) &ofRectangle::alignTo)
			
			.def("alignTo", &rectAlignToRect1)
			.def("alignTo", &rectAlignToRect2)
			.def("alignTo", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz,ofAlignVert)) &ofRectangle::alignTo)
			
			.def("alignTo", (void(ofRectangle::*)(const ofRectangle&,ofAlignHorz,ofAlignVert,ofAlignHorz,ofAlignVert)) &ofRectangle::alignTo)
			
			.def("inside", (bool(ofRectangle::*)(float,float) const) &ofRectangle::inside)
			.def("inside", (bool(ofRectangle::*)(const ofPoint&) const) &ofRectangle::inside)
			.def("inside", (bool(ofRectangle::*)(const ofRectangle&) const) &ofRectangle::inside)
			.def("inside", (bool(ofRectangle::*)(const ofPoint&,const ofPoint&) const) &ofRectangle::inside)
			
			.def("intersects", (bool(ofRectangle::*)(const ofRectangle&) const) &ofRectangle::intersects)
			.def("intersects", (bool(ofRectangle::*)(const ofPoint&,const ofPoint&) const) &ofRectangle::intersects)
			
			.def("growToInclude", (void(ofRectangle::*)(const ofPoint&)) &ofRectangle::growToInclude)
			.def("growToInclude", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::growToInclude)
			.def("growToInclude", (void(ofRectangle::*)(float,float)) &ofRectangle::growToInclude)
			.def("growToInclude", (void(ofRectangle::*)(const ofPoint&,const ofPoint&)) &ofRectangle::growToInclude)
			
			.def("getIntersection", &ofRectangle::getIntersection)
			.def("getUnion", &ofRectangle::getUnion)
			
			.def("standardize", &ofRectangle::standardize)
			.def("getStandardized", &ofRectangle::getStandardized)
			.def("isStandardized", &ofRectangle::isStandardized)
			
			.def("getArea", &ofRectangle::getArea)
			.def("getPerimeter", &ofRectangle::getPerimeter)
			.def("getAspectRatio", &ofRectangle::getAspectRatio)
			
			.def("isEmpty", &ofRectangle::isEmpty)
			
			.def("getMin", &ofRectangle::getMin)
			.def("getMax", &ofRectangle::getMax)
			
			.def("getMinX", &ofRectangle::getMinX)
			.def("getMaxX", &ofRectangle::getMaxX)
			.def("getMinY", &ofRectangle::getMinY)
			.def("getMaxY", &ofRectangle::getMaxY)
			
			.def("getLeft", &ofRectangle::getLeft)
			.def("getRight", &ofRectangle::getRight)
			.def("getTop", &ofRectangle::getTop)
			.def("getBottom", &ofRectangle::getBottom)
			
			.def("getTopLeft", &ofRectangle::getTopLeft)
			.def("getTopRight", &ofRectangle::getTopRight)
			.def("getBottomLeft", &ofRectangle::getBottomLeft)
			.def("getBottomRight", &ofRectangle::getBottomRight)
			
			.def("getHorzAnchor", &ofRectangle::getHorzAnchor)
			.def("getVertAnchor", &ofRectangle::getVertAnchor)
			
			.def("getCenter", &ofRectangle::getCenter)
			
			.def("copy", &rectCopy)
			.def(self + other<const ofPoint&>())
			.def(self == other<const ofRectangle&>())
			
			.def_readwrite("position", &ofRectangle::position)
			.def("getX", &ofRectangle::getX)
			.def("setX", &ofRectangle::setX)
			.property("x", &ofRectangle::getX, &ofRectangle::setX)
			.def("getY", &ofRectangle::getY)
			.def("setY", &ofRectangle::setY)
			.property("y", &ofRectangle::getY, &ofRectangle::setY)
			.def("getWidth", &ofRectangle::getWidth)
			.def_readwrite("width", &ofRectangle::width)
			.def("getHeight", &ofRectangle::getHeight)
			.def_readwrite("height", &ofRectangle::height)
			
			.def(tostring(self)),
			
		///////////////////////////////
		/// \section ofTypes.h
		
		class_<ofStyle>("Style")
			.def(constructor<>())
			
			.def_readwrite("color", &ofStyle::color)
			.def_readwrite("bgColor", &ofStyle::bgColor)
			.def_readwrite("polyMode", &ofStyle::polyMode)
			.def_readwrite("rectMode", &ofStyle::rectMode)
			.def_readwrite("bFill", &ofStyle::bFill)
			.def_readwrite("drawBitmapMode", &ofStyle::drawBitmapMode)
			
			.def_readwrite("blendingMode", &ofStyle::blendingMode)
			
			.def_readwrite("smoothing", &ofStyle::smoothing)
			.def_readwrite("circleResolution", &ofStyle::circleResolution)
			.def_readwrite("sphereResolution", &ofStyle::sphereResolution)
			.def_readwrite("curveResolution", &ofStyle::curveResolution)
			.def_readwrite("lineWidth", &ofStyle::lineWidth)
	;
}

} // namespace
