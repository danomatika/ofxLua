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
#include "ofMath.h"
#include "ofMatrix3x3.h"
#include "ofMatrix4x4.h"
#include "ofxLua.h"
#include <luabind/operator.hpp>

namespace bindings {

// wrapper functions needed for overloading

// math
float map5(float value, float inputMin, float inputMax, float outputMin, float outputMax)
	{return ofMap(value, inputMin, inputMax, outputMin, outputMax);}

// matrix4x4
void matrixSetValue(ofMatrix4x4 *matrix, int row, int col, float val) {(*matrix)(row, col) = val;}
float matrixGetValue(ofMatrix4x4 *matrix, int row, int col) {return (*matrix)(row, col);}
void matrixCopy(ofMatrix4x4 *matrix, const ofMatrix4x4 &m) {(*matrix) = m;}

// point
void pointCopy(ofPoint *point, const ofPoint& p) {(*point) = p;}
void pointSet2(ofPoint* point, float x, float y)
	{point->set(x, y);}
float pointMatch1(ofPoint* point, const ofPoint& other)
	{return point->match(other);}
float pointIsAligned1(ofPoint* point, const ofPoint& other)
	{return point->isAligned(other);}
float pointIsAlignedRad1(ofPoint* point, const ofPoint& other)
	{return point->isAlignedRad(other);}
float pointIsAlignedRad2(ofPoint* point, const ofPoint& other, float tolerance)
	{return point->isAlignedRad(other, tolerance);}
float pointAlign1(ofPoint* point, const ofPoint& other)
	{return point->align(other);}
float pointAlignRad1(ofPoint* point, const ofPoint& other)
	{return point->alignRad(other);}

// point const wrappers
ofPoint pointGetRotated2(ofPoint* point, float angle, const ofPoint& axis)
	{return point->getRotated(angle, axis);}
ofPoint pointGetRotatedRad2(ofPoint* point, float angle, const ofPoint& axis)
	{return point->getRotatedRad(angle, axis);}
ofPoint pointGetRotated3(ofPoint* point, float ax, float ay, float az)
	{return point->getRotated(ax, ay, az);}
ofPoint pointGetRotatedRad3(ofPoint* point, float ax, float ay, float az)
	{return point->getRotatedRad(ax, ay, az);}
ofPoint pointGetRotated3p(ofPoint* point, float angle, const ofPoint& pivot, const ofPoint& axis)
	{return point->getRotated(angle, pivot, axis);}
ofPoint pointGetRotatedRad3p(ofPoint* point, float angle, const ofPoint& pivot, const ofPoint& axis)
	{return point->getRotatedRad(angle, pivot, axis);}

// quaternion
void quaternionCopy(ofQuaternion *quat, const ofQuaternion &q) {(*quat) = q;}
void quaternionSetValue(ofQuaternion *quat, int i, float val) {(*quat)[i] = val;}
float quaternionGetValue(ofQuaternion *quat, int i) {return (*quat)[i];}

// luabind registration
luabind::scope registerMath() {
		
	using namespace luabind;
	
	return
	
		///////////////////////////////
		/// \section ofMath.h
		
		def("nextPow2", &ofNextPow2),
		
		def("seedRandom", (void(*)(void)) &ofSeedRandom),
		def("seedRandom", (void(*)(int)) &ofSeedRandom),
		def("random", (float(*)(float)) &ofRandom),
		def("random", (float(*)(float,float)) &ofRandom),
		def("randomf", (float(*)(void)) &ofRandomf),
		def("randomuf", (float(*)(void)) &ofRandomuf),
		
		def("normalize", &ofNormalize),
		def("map", (float(*)(float,float,float,float,float)) &map5),
		def("map", (float(*)(float,float,float,float,float,bool)) &ofMap),
		def("clamp", &ofClamp),
		def("lerp", &ofLerp),
		def("dist", &ofDist),
		def("distSquared", &ofDistSquared),
		def("sign", &ofSign),
		def("inRange", &ofInRange),
		
		def("radToDeg", &ofRadToDeg),
		def("DegToRad", &ofDegToRad),
		def("lerpDegrees", &ofLerpDegrees),
		def("lerpRadians", &ofLerpRadians),
		def("angleDifferenceDegrees", &ofAngleDifferenceDegrees),
		def("angleDifferenceRadians", &ofAngleDifferenceRadians),
		def("wrap", &ofWrap),
		def("wrapRadians", &ofWrapRadians),
		def("wrapDegrees", &ofWrapDegrees),
		
		def("randomWidth", &ofRandomWidth),
		def("randomHeight", &ofRandomHeight),
		
		def("noise", (float(*)(float)) &ofNoise),
		def("noise", (float(*)(float,float)) &ofNoise),
		def("noise", (float(*)(float,float,float)) &ofNoise),
		def("noise", (float(*)(float,float,float,float)) &ofNoise),
		
		def("signedNoise", (float(*)(float)) &ofSignedNoise),
		def("signedNoise", (float(*)(float,float)) &ofSignedNoise),
		def("signedNoise", (float(*)(float,float,float)) &ofSignedNoise),
		def("signedNoise", (float(*)(float,float,float,float)) &ofSignedNoise),
		
		// TODO: needs vector
		//def("insidePoly", (bool(*)(float,float,const vector<ofPoint>&)) &ofInsidePoly),
		//def("insidePoly", (bool(*)(const ofPoint&,const vector<ofPoint>&)) &ofInsidePoly),
		
		def("lineSegmentIntersection", &ofLineSegmentIntersection),
		
		def("bezierPoint", &ofBezierPoint),
		def("curvePoint", &ofCurvePoint),
		def("bezierTangent", &ofBezierTangent),
		def("curveTangent", &ofCurveTangent),
		
		def("interpolateCosine", (float(*)(float,float,float)) &ofInterpolateCosine),
		def("interpolateCubic", (float(*)(float,float,float,float,float)) &ofInterpolateCubic),
		def("interpolateCatmullRom", (float(*)(float,float,float,float,float)) &ofInterpolateCatmullRom),
		def("interpolateHermite", (float(*)(float,float,float,float,float)) &ofInterpolateHermite),
		def("interpolateHermite", (float(*)(float,float,float,float,float,float,float)) &ofInterpolateHermite),
		
		///////////////////////////////
		/// \section ofMatrix3x3.h
		
		class_<ofMatrix3x3>("Matrix3x3")
			.def(constructor<>())
			.def(constructor<float>())
			.def(constructor<float,float>())
			.def(constructor<float,float,float>())
			.def(constructor<float,float,float,float>())
			.def(constructor<float,float,float,float,float>())
			.def(constructor<float,float,float,float,float,float>())
			.def(constructor<float,float,float,float,float,float,float>())
			.def(constructor<float,float,float,float,float,float,float,float>())
			.def(constructor<float,float,float,float,float,float,float,float,float>())
			
			.def_readwrite("a", &ofMatrix3x3::a)
			.def_readwrite("b", &ofMatrix3x3::b)
			.def_readwrite("c", &ofMatrix3x3::c)
			.def_readwrite("d", &ofMatrix3x3::d)
			.def_readwrite("e", &ofMatrix3x3::e)
			.def_readwrite("f", &ofMatrix3x3::f)
			.def_readwrite("g", &ofMatrix3x3::g)
			.def_readwrite("h", &ofMatrix3x3::h)
			.def_readwrite("i", &ofMatrix3x3::i)
			.def("set", &ofMatrix3x3::set)
			// ignore [] operator for now
			
			.def("transpose", (void(ofMatrix3x3::*)(void)) &ofMatrix3x3::transpose)
			.def("transpose", (ofMatrix3x3(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::transpose)
			
			.def("determinant", (float(ofMatrix3x3::*)(void) const) &ofMatrix3x3::determinant)
			.def("determinant", (float(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::determinant)
			
			.def("invert", (void(ofMatrix3x3::*)(void) const) &ofMatrix3x3::inverse)
			.def("invert", (ofMatrix3x3(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::inverse)
			
			.def(self + other<const ofMatrix3x3&>())
			.def(self - other<const ofMatrix3x3&>())
			.def(self * float())
			.def("entrywiseTimes", &ofMatrix3x3::entrywiseTimes)
			.def(tostring(self))
			.def(self * other<const ofMatrix3x3&>())
			.def(self / float()),
		
		///////////////////////////////
		/// \section ofMatrix4x4.h
		
		class_<ofMatrix4x4>("Matrix4x4")
			.def(constructor<>())
			.def(constructor<const ofMatrix4x4&>())
			.def(constructor<const ofQuaternion&>())
//			.def(constructor<
//				float,float,float,float,
//				float,float,float,float,
//				float,float,float,float,
//				float,float,float,float>())
			
			.def("setValue", &matrixSetValue)
			.def("getValue", &matrixGetValue)
			.def("getRowAsVec3f", (ofPoint(ofMatrix4x4::*)(int)) &ofMatrix4x4::getRowAsVec3f)
			// getRowAsVec4f
			
			.def(tostring(self))
			
			.def("isValid", &ofMatrix4x4::isValid)
			.def("isNaN", &ofMatrix4x4::isNaN)
			
			.def("copy", &matrixCopy)
			
			.def("set", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::set)
			//.def("set", (void(ofMatrix4x4::*)(float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)) &ofMatrix4x4::set)
			
			// ignoring getPtr()
			
			.def("isIdentity", &ofMatrix4x4::isIdentity)
			
			.def("makeIdentityMatrix", &ofMatrix4x4::makeIdentityMatrix)
			
			.def("makeScaleMatrix", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::makeScaleMatrix)
			.def("makeScaleMatrix", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::makeScaleMatrix)
			
			.def("makeTranslationMatrix", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::makeTranslationMatrix)
			.def("makeTranslationMatrix", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::makeTranslationMatrix)
			
			.def("makeRotationMatrix", (void(ofMatrix4x4::*)(const ofPoint&,const ofPoint&)) &ofMatrix4x4::makeRotationMatrix)
			.def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,const ofPoint&)) &ofMatrix4x4::makeRotationMatrix)
			.def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::makeRotationMatrix)
			.def("makeRotationMatrix", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::makeRotationMatrix)
			.def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,const ofPoint&,float,const ofPoint&,float,const ofPoint&)) &ofMatrix4x4::makeRotationMatrix)
			
			.def("makeInvertOf", &ofMatrix4x4::makeInvertOf)
			.def("makeOrthoNormalOf", &ofMatrix4x4::makeOrthoNormalOf)
			.def("makeFromMultiplicationOf", &ofMatrix4x4::makeFromMultiplicationOf)
			.def("getInverse", &ofMatrix4x4::getInverse)
			
			.def("makeOrthoMatrix", &ofMatrix4x4::makeOrthoMatrix)
			.def("makeOrtho2DMatrix", &ofMatrix4x4::makeOrtho2DMatrix)
			.def("makeFrustumMatrix", &ofMatrix4x4::makeFrustumMatrix)
			.def("makePerspectiveMatrix", &ofMatrix4x4::makePerspectiveMatrix)
			.def("makeLookAtMatrix", &ofMatrix4x4::makeLookAtMatrix)
			.def("makeLookAtViewMatrix", &ofMatrix4x4::makeLookAtViewMatrix)
			
			.def("getOrtho", &ofMatrix4x4::getOrtho)
			.def("getFrustum", &ofMatrix4x4::getFrustum)
			.def("getPerspective", &ofMatrix4x4::getPerspective)
			.def("getLookAt", &ofMatrix4x4::getLookAt)
			
			.def("decompose", &ofMatrix4x4::decompose)
			
			// skipping static creation functions for now
			
			.def("postMult", (ofPoint(ofMatrix4x4::*)(const ofPoint&) const) &ofMatrix4x4::postMult)
			.def(self * other<const ofPoint&>())
			.def("preMult", (ofPoint(ofMatrix4x4::*)(const ofPoint&) const) &ofMatrix4x4::preMult)
			// need ofVec4f versions
			
			.def("setRotate", &ofMatrix4x4::setRotate)
			.def("setTranslation", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::setTranslation)
			.def("setTranslation", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::setTranslation)
			
			.def("rotate", (void(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::rotate)
			.def("rotateRad", &ofMatrix4x4::rotateRad)
			.def("rotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::rotate)
			.def("translate", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::translate)
			.def("translate", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::translate)
			.def("scale", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::scale)
			.def("scale", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::scale)
			
			.def("glRotate", (void(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::glRotate)
			.def("glRotateRad", &ofMatrix4x4::glRotateRad)
			.def("glRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::glRotate)
			.def("glTranslate", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::glTranslate)
			.def("glTranslate", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::glTranslate)
			.def("glScale", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::glScale)
			.def("glScale", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::glScale)
			
			.def("getRotate", &ofMatrix4x4::getRotate)
			.def("getTranslation", &ofMatrix4x4::getTranslation)
			.def("getScale", &ofMatrix4x4::getScale)
			
			// ignore transform3x3 & 4x4 static functions for now
			
			.def("postMult", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::postMult)
			.def(self * other<const ofMatrix4x4&>())
			.def("preMult", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::preMult)
			
			.def("postMultTranslate", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::postMultTranslate)
			.def("postMultScale", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::postMultScale)
			.def("postMultRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::postMultRotate)
			
			.def("postMultTranslate", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::postMultTranslate)
			.def("postMultRotate", (void(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::postMultRotate)
			.def("postMultScale", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::postMultScale)
			
			.def("preMultScale", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::preMultScale)
			.def("preMultTranslate", (void(ofMatrix4x4::*)(const ofPoint&)) &ofMatrix4x4::preMultTranslate)
			.def("preMultRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::preMultRotate),
		
		///////////////////////////////
		/// \section ofQuaternion.h
		
		class_<ofQuaternion>("Quaternion")
			.def(constructor<>())
			.def(constructor<float,float,float,float>())
			//.def(constructor<const ofVec4f&>()) // needs ofVec4f
			.def(constructor<float,const ofPoint&>())
			.def(constructor<float,const ofPoint&,float,const ofPoint&,float,const ofPoint&>())
			
			.def("copy", &quaternionCopy) // operator =
			.def(self == other<const ofQuaternion&>())
			
			.def(tostring(self))
			
			//.def("asVec4", &ofQuaternion::asVec4) // needs ofVec4f
			.def("asVec3", &ofQuaternion::asVec3)
			
			.def("set", (void(ofQuaternion::*)(float,float,float,float)) &ofQuaternion::set)
			//.def("set", (void(ofQuaternion::*)(const ofVec4f&)) &ofQuaternion::set) // needs ofVec4f
			.def("set", (void(ofQuaternion::*)(const ofMatrix4x4&)) &ofQuaternion::set)
			.def("get", &ofQuaternion::get)
			
			.def("setValue", &quaternionSetValue)
			.def("getValue", &quaternionGetValue)
			
			.property("x", (float(ofQuaternion::*)(void) const) &ofQuaternion::x)
			.property("y", (float(ofQuaternion::*)(void) const) &ofQuaternion::y)
			.property("z", (float(ofQuaternion::*)(void) const) &ofQuaternion::z)
			.property("w", (float(ofQuaternion::*)(void) const) &ofQuaternion::w)
			
			.def("zeroRotation", &ofQuaternion::zeroRotation)
			
			.def(self * float())
			.def(self * other<const ofQuaternion&>())
			.def(self / float())
			.def(self / other<const ofQuaternion&>())
			.def(self + other<const ofQuaternion&>())
			.def(self - other<const ofQuaternion&>())
			.def(self * other<const ofPoint&>())
			
			.property("length", &ofQuaternion::length)
			.property("length2", &ofQuaternion::length2)
			
			.def("conj", &ofQuaternion::conj)
			.def("inverse", &ofQuaternion::inverse)
			
			.def("makeRotate", (void(ofQuaternion::*)(float,float,float,float)) &ofQuaternion::makeRotate)
			.def("makeRotate", (void(ofQuaternion::*)(float,const ofPoint&)) &ofQuaternion::makeRotate)
			.def("makeRotate", (void(ofQuaternion::*)(float,const ofPoint&,float,const ofPoint&,float,const ofPoint&)) &ofQuaternion::makeRotate)
			
			.def("makeRotate", (void(ofQuaternion::*)(const ofPoint&,const ofPoint&)) &ofQuaternion::makeRotate)
			.def("makeRotate_original", (void(ofQuaternion::*)(const ofPoint&,const ofPoint&)) &ofQuaternion::makeRotate)
			
			// ignoring getRotate functions for now
			
			.def("getEuler", (ofPoint(ofQuaternion::*)(void)) &ofQuaternion::getEuler)
			.def("slerp", &ofQuaternion::slerp)
			.def("normalize", &ofQuaternion::normalize),
		
		///////////////////////////////
		/// \section ofPoint.h
		
		class_<ofPoint>("Point")
			.def_readwrite("x", &ofPoint::x)
			.def_readwrite("y", &ofPoint::y)
			.def_readwrite("z", &ofPoint::z)
			
			.def(constructor<>())
			.def(constructor<float,float>())
			.def(constructor<float,float,float>())
			.def(constructor<float>())
			.def(constructor<const ofPoint&>())
			
			// ignore getPtr() & operator []
			
			.def("set", &pointSet2)
			.def("set", (void(ofPoint::*)(float,float,float)) &ofPoint::set)
			.def("set", (void(ofPoint::*)(const ofPoint&)) &ofPoint::set)
			.def("set", (void(ofPoint::*)(float)) &ofPoint::set)
			.def("copy", &pointCopy) // operator =
			
			.def(self == other<const ofPoint&>())
			.def("match", &pointMatch1)
			.def("match", (bool(ofPoint::*)(const ofPoint&,float)) &ofPoint::match)
			
			.def("isAligned", &pointIsAligned1)
			.def("isAligned", (bool(ofPoint::*)(const ofPoint&,float)) &ofPoint::isAligned)
			.def("align", &pointAlign1)
			.def("align", (bool(ofPoint::*)(const ofPoint&,float)) &ofPoint::align)
			.def("isAlignedRad", &pointIsAlignedRad1)
			.def("isAlignedRad", &pointIsAlignedRad2)
			.def("alignRad", &pointAlignRad1)
			.def("alignRad", (bool(ofPoint::*)(const ofPoint&,float)) &ofPoint::alignRad)
			
			.def(self + other<const ofPoint&>())
			.def(self - other<const ofPoint&>())
			.def(self * other<const ofPoint&>())
			.def(self / other<const ofPoint&>())
			.def(self + other<const float>())
			.def(self - other<const float>())
			.def(self * other<const float>())
			.def(self / other<const float>())
			
			.def(tostring(self))
			
			.def("getScaled", (ofPoint(ofPoint::*)(const float)) &ofPoint::getScaled)
			.def("scale", (ofPoint&(ofPoint::*)(const float)) &ofPoint::scale)
			
			.def("getRotated", &pointGetRotated3)
			.def("getRotatedRad", &pointGetRotatedRad3)
			.def("rotate", (ofPoint&(ofPoint::*)(float,float,float)) &ofPoint::rotate)
			.def("rotateRad", (ofPoint&(ofPoint::*)(float,float,float)) &ofPoint::rotateRad)
			.def("getRotated", &pointGetRotated2)
			.def("getRotatedRad", &pointGetRotatedRad2)
			.def("rotate", (ofPoint&(ofPoint::*)(float,const ofPoint&)) &ofPoint::rotate)
			.def("rotateRad", (ofPoint&(ofPoint::*)(float,const ofPoint&)) &ofPoint::rotateRad)
			
			.def("getRotated", &pointGetRotated3p)
			.def("rotate", (ofPoint&(ofPoint::*)(float,const ofPoint&,const ofPoint&)) &ofPoint::rotate)
			.def("getRotatedRad", &pointGetRotatedRad3p)
			.def("rotateRad", (ofPoint&(ofPoint::*)(float,const ofPoint&,const ofPoint&)) &ofPoint::rotateRad)
			
			.def("getMapped", (ofPoint(ofPoint::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofPoint::getMapped)
			.def("map", (ofPoint&(ofPoint::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofPoint::map)
			
			.def("distance", (float(ofPoint::*)(const ofPoint&)) &ofPoint::distance)
			.def("squareDistance", (float(ofPoint::*)(const ofPoint&)) &ofPoint::squareDistance)
			
			.def("getInterpolated", (ofPoint(ofPoint::*)(const ofPoint&,float)) &ofPoint::getInterpolated)
			.def("interpolate", (ofPoint&(ofPoint::*)(const ofPoint&,float)) &ofPoint::interpolate)
			.def("getMiddle", (ofPoint(ofPoint::*)(const ofPoint&)) &ofPoint::getMiddle)
			.def("midddle", (ofPoint&(ofPoint::*)(const ofPoint&)) &ofPoint::middle)
			//.def("average", (ofPoint&(ofPoint::*)(const ofPoint*,int)) &ofPoint::average) // TODO: takes point array
			
			.def("getNormalized", (ofPoint(ofPoint::*)(void)) &ofPoint::getNormalized)
			.def("normalize", (ofPoint&(ofPoint::*)(void)) &ofPoint::normalize)
			
			.def("getLimited", (ofPoint(ofPoint::*)(float)) &ofPoint::getLimited)
			.def("limit", (ofPoint&(ofPoint::*)(float)) &ofPoint::limit)
			
			.def("getCrossed", (ofPoint(ofPoint::*)(const ofPoint&)) &ofPoint::getCrossed)
			.def("cross", (ofPoint&(ofPoint::*)(const ofPoint&)) &ofPoint::cross)
			
			.def("getPerpendicular", (ofPoint(ofPoint::*)(void)) &ofPoint::getPerpendicular)
			.def("perpendicular", (ofPoint&(ofPoint::*)(void)) &ofPoint::perpendicular)
			
			.def("length", (float(ofPoint::*)(void)) &ofPoint::length)
			.def("lengthSquared", (float(ofPoint::*)(void)) &ofPoint::lengthSquared)
			
			.def("angle", (float(ofPoint::*)(const ofPoint&)) &ofPoint::angle)
			.def("angleRad", (float(ofPoint::*)(const ofPoint&)) &ofPoint::angleRad)
			
			.def("dot", (float(ofPoint::*)(const ofPoint&)) &ofPoint::dot)
	;
}

} // namespace
