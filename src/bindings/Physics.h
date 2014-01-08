/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/robotcowboy for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxLua.h"
#include "ofxBox2d.h"

#include "../Global.h"

namespace lua {

class Physics {

	public:
	
		static void bind(ofxLua& lua) {
		
			using namespace luabind;
			
			module(lua, "physics")
			[
				///////////////////////////////
				/// \section World
				
				class_<ofxBox2d>("World")
					.def(constructor<>())
					.def("setup", &ofxBox2d::init)
					.def("frameRate", &ofxBox2d::setFPS)
					.def("wakeupShapes", &ofxBox2d::wakeupShapes)
					.def("numBodies", &ofxBox2d::getBodyCount)
					.def("numJoints", &ofxBox2d::getJointCount)
					.def("setIterations", &ofxBox2d::setIterations)
					.def("setGravity", (void(ofxBox2d::*)(ofPoint p)) &ofxBox2d::setGravity)
					.def("setGravity", (void(ofxBox2d::*)(float,float)) &ofxBox2d::setGravity)
					.def("getGravity", &ofxBox2d::getGravity)
					.def("getGravityX", &worldGetGravityX)
					.def("getGravityY", &worldGetGravityY)
					.def("grabbing", &ofxBox2d::enableGrabbing)
					.def("noGrabbing", &ofxBox2d::disableGrabbing)
					.def("createBounds", &worldCreateBounds0)
					.def("createBounds", (void(ofxBox2d::*)(float,float,float,float)) &ofxBox2d::createBounds)
					.def("createBounds", (void(ofxBox2d::*)(ofRectangle&)) &ofxBox2d::createBounds)
					.def("createGround", &worldCreateGround0)
					.def("createGround", (void(ofxBox2d::*)(const ofPoint&,const ofPoint&)) &ofxBox2d::createGround)
					.def("createGround", (void(ofxBox2d::*)(float,float,float,float)) &ofxBox2d::createGround)
					.def("update", &ofxBox2d::update)
					.def("draw", &ofxBox2d::draw),
				
				///////////////////////////////
				/// \section Shape
				
				class_<ofxBox2dBaseShape>("Shape")
					.def(constructor<>())
					.def("clear", &ofxBox2dBaseShape::destroy)
					.def("isBody", &ofxBox2dBaseShape::isBody)
					.def("isFixed", &ofxBox2dBaseShape::isFixed)
					.def("isSleeping", &ofxBox2dBaseShape::isSleeping)
					.def("setPhysics", &ofxBox2dBaseShape::setPhysics)
					.def("gravity", &shapeGravity)
					.def("noGravity", &shapeNoGravity)
					.def("fixedRotation", &shapeFixedRotation)
					.def("noFixedRotation", &shapeNoFixedRotation)
					.def("setRotationFriction", &ofxBox2dBaseShape::setRotationFriction)
					.def("getRotation", &ofxBox2dBaseShape::getRotation)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float)) &ofxBox2dBaseShape::setDamping)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float,float)) &ofxBox2dBaseShape::setDamping)
					.def("addForce", &shapeAddForce)
					.def("addImpulseForce", &shapeAddImpulseForce)
					.def("addRepulsionForce", &shapeAddRepulsionForce)
					.def("update", &ofxBox2dBaseShape::update)
					.def("draw", &ofxBox2dBaseShape::draw)
					.def_readwrite("body", &ofxBox2dBaseShape::body)
					.def_readwrite("density", &ofxBox2dBaseShape::density)
					.def_readwrite("bounce", &ofxBox2dBaseShape::bounce)
					.def_readwrite("friction", &ofxBox2dBaseShape::friction)
					.property("position", &shapeGetPos, &shapeSetPos)
					.property("velocity", &shapeGetVel, &shapeSetVel),
				
				///////////////////////////////
				/// \section Circle
				
				class_<ofxBox2dCircle,ofxBox2dBaseShape>("Circle")
					.def(constructor<>())
					.def("setup", &circleSetup2)
					.def("setup", &circleSetup3)
					.def("addAttractionPoint", &circleAddAttractionPoint2)
					.def("addAttractionPoint", (void(ofxBox2dCircle::*)(float,float,float)) &ofxBox2dCircle::addAttractionPoint)
					.def("addRepulsionForce", &circleAddRepulsionForce2)
					.def("addRepulsionForce", (void(ofxBox2dCircle::*)(float,float,float)) &ofxBox2dCircle::addRepulsionForce)
					.property("radius", &ofxBox2dCircle::getRadius, &ofxBox2dCircle::setRadius)
					// copied from shape
					.def("clear", &ofxBox2dBaseShape::destroy)
					.def("isBody", &ofxBox2dBaseShape::isBody)
					.def("isFixed", &ofxBox2dBaseShape::isFixed)
					.def("isSleeping", &ofxBox2dBaseShape::isSleeping)
					.def("setPhysics", &ofxBox2dBaseShape::setPhysics)
					.def("gravity", &shapeGravity)
					.def("noGravity", &shapeNoGravity)
					.def("fixedRotation", &shapeFixedRotation)
					.def("noFixedRotation", &shapeNoFixedRotation)
					.def("setRotationFriction", &ofxBox2dBaseShape::setRotationFriction)
					.def("getRotation", &ofxBox2dBaseShape::getRotation)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float)) &ofxBox2dBaseShape::setDamping)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float,float)) &ofxBox2dBaseShape::setDamping)
					.def("addForce", &shapeAddForce)
					.def("addImpulseForce", &shapeAddImpulseForce)
					.def("addRepulsionForce", &shapeAddRepulsionForce)
					.def("update", &ofxBox2dBaseShape::update)
					.def("draw", &ofxBox2dBaseShape::draw)
					.def_readwrite("body", &ofxBox2dBaseShape::body)
					.def_readwrite("density", &ofxBox2dBaseShape::density)
					.def_readwrite("bounce", &ofxBox2dBaseShape::bounce)
					.def_readwrite("friction", &ofxBox2dBaseShape::friction)
					.property("position", &shapeGetPos, &shapeSetPos)
					.property("velocity", &shapeGetVel, &shapeSetVel),
					
				///////////////////////////////
				/// \section Rectangle
				
				class_<ofxBox2dRect,ofxBox2dBaseShape>("Rectangle")
					.def(constructor<>())
					.def("setup", &rectSetup1)
					.def("setup", &rectSetup4)
					.def("addAttractionPoint", &rectAddAttractionPoint2)
					.def("addAttractionPoint", (void(ofxBox2dRect::*)(float,float,float)) &ofxBox2dRect::addAttractionPoint)
					.def("addRepulsionForce", &rectAddRepulsionForce2)
					.def("addRepulsionForce", (void(ofxBox2dRect::*)(float,float,float)) &ofxBox2dRect::addRepulsionForce)
					.def_readonly("width", &ofxBox2dRect::getWidth)
					.def_readonly("height", &ofxBox2dRect::getHeight)
					.def_readonly("shape", &ofxBox2dRect::getRectangleShape)
					// copied from shape
					.def("clear", &ofxBox2dBaseShape::destroy)
					.def("isBody", &ofxBox2dBaseShape::isBody)
					.def("isFixed", &ofxBox2dBaseShape::isFixed)
					.def("isSleeping", &ofxBox2dBaseShape::isSleeping)
					.def("setPhysics", &ofxBox2dBaseShape::setPhysics)
					.def("gravity", &shapeGravity)
					.def("noGravity", &shapeNoGravity)
					.def("fixedRotation", &shapeFixedRotation)
					.def("noFixedRotation", &shapeNoFixedRotation)
					.def("setRotationFriction", &ofxBox2dBaseShape::setRotationFriction)
					.def("getRotation", &ofxBox2dBaseShape::getRotation)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float)) &ofxBox2dBaseShape::setDamping)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float,float)) &ofxBox2dBaseShape::setDamping)
					.def("addForce", &shapeAddForce)
					.def("addImpulseForce", &shapeAddImpulseForce)
					.def("addRepulsionForce", &shapeAddRepulsionForce)
					.def("update", &ofxBox2dBaseShape::update)
					.def("draw", &ofxBox2dBaseShape::draw)
					.def_readwrite("body", &ofxBox2dBaseShape::body)
					.def_readwrite("density", &ofxBox2dBaseShape::density)
					.def_readwrite("bounce", &ofxBox2dBaseShape::bounce)
					.def_readwrite("friction", &ofxBox2dBaseShape::friction)
					.property("position", &shapeGetPos, &shapeSetPos)
					.property("velocity", &shapeGetVel, &shapeSetVel),
					
				///////////////////////////////
				/// \section Polygon
				
				class_<ofxBox2dPolygon, bases<ofxBox2dBaseShape,ofPolyline> >("Polygon")
					.def(constructor<>())
					.def("setup", &polygonSetup)
					.def("addTriangle", &polygonAddTriangle)
					//.def("addVertexes", &ofxBox2dPolygon::addVertexes) // TODO: needs vector
					.def("addPolyline", (void(ofxBox2dPolygon::*)(ofPolyline&)) &ofxBox2dPolygon::addVertexes)
					.def("simplify", &poylgonSimplify0)
					.def("simplify", &ofxBox2dPolygon::simplify)
					.def("triangulate", &polygonTriangulate0)
					.def("triangulate", &ofxBox2dPolygon::triangulate)
					.def("getCenter", &polygonGetCenter)
					.def("getArea", &ofxBox2dPolygon::getArea)
					.def("isGoodShape", &ofxBox2dPolygon::isGoodShape)
					.def("setAsEdge", &ofxBox2dPolygon::setAsEdge)
					.def("update", &ofxBox2dPolygon::updateShape)
					.def("draw", &ofxBox2dPolygon::draw)
					.def("addAttractionPoint", &polygonAddAttractionPoint2)
					.def("addAttractionPoint", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::addAttractionPoint)
					.def("addRepulsionForce", &polygonAddRepulsionForce2)
					.def("addRepulsionForce", (void(ofxBox2dPolygon::*)(float,float,float)) &ofxBox2dPolygon::addRepulsionForce)
					// coped from shape
					.def("clear", &ofxBox2dBaseShape::destroy)
					.def("isBody", &ofxBox2dBaseShape::isBody)
					.def("isFixed", &ofxBox2dBaseShape::isFixed)
					.def("isSleeping", &ofxBox2dBaseShape::isSleeping)
					.def("setPhysics", &ofxBox2dBaseShape::setPhysics)
					.def("gravity", &shapeGravity)
					.def("noGravity", &shapeNoGravity)
					.def("fixedRotation", &shapeFixedRotation)
					.def("noFixedRotation", &shapeNoFixedRotation)
					.def("setRotationFriction", &ofxBox2dBaseShape::setRotationFriction)
					.def("getRotation", &ofxBox2dBaseShape::getRotation)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float)) &ofxBox2dBaseShape::setDamping)
					.def("setDamping", (void(ofxBox2dBaseShape::*)(float,float)) &ofxBox2dBaseShape::setDamping)
					.def("addForce", &shapeAddForce)
					.def("addImpulseForce", &shapeAddImpulseForce)
					.def("addRepulsionForce", &shapeAddRepulsionForce)
					//.def("update", &ofxBox2dBaseShape::update)
					//.def("draw", &ofxBox2dBaseShape::draw)
					.def_readwrite("body", &ofxBox2dBaseShape::body)
					.def_readwrite("density", &ofxBox2dBaseShape::density)
					.def_readwrite("bounce", &ofxBox2dBaseShape::bounce)
					.def_readwrite("friction", &ofxBox2dBaseShape::friction)
					.property("position", &shapeGetPos, &shapeSetPos)
					.property("velocity", &shapeGetVel, &shapeSetVel)
					// copied form polyline
					//.def("clear", &ofPolyline::clear)
					.def("addVertex", (void(ofPolyline::*)(const ofPoint&)) &ofPolyline::addVertex)
					.def("addVertex", &polylineAddVertex2)
					.def("addVertex", (void(ofPolyline::*)(float,float,float)) &ofPolyline::addVertex)
					.def("lineTo", (void(ofPolyline::*)(const ofPoint&)) &ofPolyline::lineTo)
					.def("lineTo", &polylineLineTo2)
					.def("lineTo", (void(ofPolyline::*)(float,float,float)) &ofPolyline::lineTo)
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
					.def("curveTo", &polyLineCurveToPoint1)
					.def("curveTo", (void(ofPolyline::*)(const ofPoint&,int)) &ofPolyline::curveTo)
					.def("curveTo", &polyLineCurveToFloat2)
					.def("curveTo", &polyLineCurveToFloat3)
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
					.def("inside", (bool(ofPolyline::*)(const ofPoint&)) &ofPolyline::inside)
					.def("inside", (bool(ofPolyline::*)(float,float)) &ofPolyline::inside)
					//.def("inside", (bool(ofPolyline::*)(const ofPoint&,const ofPolyline&)) &ofPolyline::inside) // TODO: these are static
					//.def("inside", (bool(ofPolyline::*)(float,float,const ofPolyline&)) &ofPolyline::inside) // TODO: static
					.def("simplify", &polylineSimplify0)
					.def("simplify", &ofPolyline::simplify)
					.def("getPoint", &polylineGetPoint)
					.def("setPoint", &polylineSetPoint)
					.def("resize", &ofPolyline::resize) // needed? too low level?
					.def("setClosed", &ofPolyline::setClosed)
					.def("isClosed", &ofPolyline::isClosed)
					.def("close", &ofPolyline::close)
					.def("hasChanged", &ofPolyline::hasChanged)
					//.def("getVertices", &ofPolyline::getVertices) // TODO: returns vector
					.def("getPerimeter", &ofPolyline::getPerimeter)
					.def("getArea", &ofPolyline::getArea)
					.def("getCenter", &ofPolyline::getCentroid2D)
					//.def("draw", &ofPolyline::draw)
					.def_readonly("size", &ofPolyline::size),
					
					///////////////////////////////
					/// \section Joint
					
					class_<ofxBox2dJoint>("Joint")
						.def(constructor<>())
						.def("setup", &jointSetup2)
						.def("setup", &jointSetup5)
						.def("setup", &jointSetupAnchored4)
						.def("setup", &jointSetupAnchored7)
						.def("wasSetup", &ofxBox2dJoint::isSetup)
						.def("draw", &ofxBox2dJoint::draw)
						.def("getReactionForce", &jointGetReactionForce)
						.def("getReactionTorque", &ofxBox2dJoint::getReactionTorque)
						.def_readwrite("joint", &ofxBox2dJoint::joint)
						.def_readwrite("jointType", &ofxBox2dJoint::jointType)
						.def_readwrite("alive", &ofxBox2dJoint::alive)
						.property("length", &ofxBox2dJoint::getLength, &ofxBox2dJoint::setLength)
						.property("frequency", &ofxBox2dJoint::getFrequency, &ofxBox2dJoint::setFrequency)
						.property("damping", &ofxBox2dJoint::getDamping, &ofxBox2dJoint::setDamping),
					
				///////////////////////////////
				/// \section b2Body
				
				class_<b2Body>("Body")
			];
		}
		
		/// \section Function & Object Wrappers

		/// world
		static float worldGetGravityX(ofxBox2d* box2d) {
			return box2d->getGravity().x;
		}
		static float worldGetGravityY(ofxBox2d* box2d) {
			return box2d->getGravity().y;
		}
		static void worldCreateBounds0(ofxBox2d* box2d) {
			box2d->createBounds();
		}
		static void worldCreateGround0(ofxBox2d* box2d) {
			box2d->createGround();
		}
		
		/// shape
		static void shapeGravity(ofxBox2dBaseShape *shape) {
			shape->enableGravity(true);
		}
		static void shapeNoGravity(ofxBox2dBaseShape *shape) {
			shape->enableGravity(false);
		}
		static void shapeFixedRotation(ofxBox2dBaseShape *shape) {
			shape->setFixedRotation(true);
		}
		static void shapeNoFixedRotation(ofxBox2dBaseShape *shape) {
			shape->setFixedRotation(false);
		}
		static ofPoint shapeGetPos(ofxBox2dBaseShape *shape) {
			ofVec2f p = shape->getPosition();
			return ofPoint(p.x, p.y);
		}
		static void shapeSetPos(ofxBox2dBaseShape *shape, ofPoint p) {
			shape->setPosition(p.x, p.y);
		}
		static ofPoint shapeGetVel(ofxBox2dBaseShape *shape) {
			ofVec2f p = shape->getVelocity();
			return ofPoint(p.x, p.y);
		}
		static void shapeSetVel(ofxBox2dBaseShape *shape, ofPoint p) {
			shape->setVelocity(p.x, p.y);
		}
		static void shapeAddForce(ofxBox2dBaseShape *shape, ofPoint f, float scale) {
			shape->addForce(ofVec2f(f.x, f.y), scale);
		}
		static void shapeAddImpulseForce(ofxBox2dBaseShape *shape, ofPoint p, ofPoint amt) {
			shape->addImpulseForce(ofVec2f(p.x, p.y), ofVec2f(amt.x, amt.y));
		}
		static void shapeAddRepulsionForce(ofxBox2dBaseShape *shape, ofPoint p, float radius, float amt) {
			shape->addRepulsionForce(ofVec2f(p.x, p.y), radius, amt);
		}
		
		/// circle
		static void circleSetup2(ofxBox2dCircle *circle, ofxBox2d& box2d, ofPoint& p, float radius) {
			circle->setup(box2d.world, p.x, p.y, radius);
		}
		static void circleSetup3(ofxBox2dCircle *circle, ofxBox2d& box2d, float x, float y, float radius) {
			circle->setup(box2d.world, x, y, radius);
		}
		static void circleAddAttractionPoint2(ofxBox2dCircle *circle, ofPoint& p, float amt) {
			circle->addAttractionPoint(ofVec2f(p.x, p.y), amt);
		}
		static void circleAddRepulsionForce2(ofxBox2dCircle *circle, ofPoint& p, float amt) {
			circle->addRepulsionForce(ofVec2f(p.x, p.y), amt);
		}
		
		/// rect
		static void rectSetup1(ofxBox2dRect *rect, ofxBox2d& box2d, ofRectangle r) {
			rect->setup(box2d.world, r);
		}
		static void rectSetup4(ofxBox2dRect *rect,ofxBox2d& box2d, float x, float y, float w, float h) {
			rect->setup(box2d.world, x, y, w, h);
		}
		static void rectAddAttractionPoint2(ofxBox2dRect *rect, ofPoint& p, float amt) {
			rect->addAttractionPoint(ofVec2f(p.x, p.y), amt);
		}
		static void rectAddRepulsionForce2(ofxBox2dRect *rect, ofPoint& p, float amt) {
			rect->addRepulsionForce(ofVec2f(p.x, p.y), amt);
		}
		
		/// joint
		static void jointSetup2(ofxBox2dJoint *joint, ofxBox2d& box2d, b2Body *body1, b2Body *body2) {
			joint->setup(box2d.world, body1, body2);
		}
		static void jointSetup5(ofxBox2dJoint *joint, ofxBox2d& box2d, b2Body *body1, b2Body *body2, float frequencyHz, float damping, bool bCollideConnected) {
			joint->setup(box2d.world, body1, body2, frequencyHz, damping, bCollideConnected);
		}
		static void jointSetupAnchored4(ofxBox2dJoint *joint, ofxBox2d& box2d, b2Body *body1, b2Body *body2, ofPoint anchor1, ofPoint anchor2) {
			joint->setup(box2d.world, body1, body2,
				b2Vec2(anchor1.x, anchor1.y), b2Vec2(anchor2.x, anchor2.y));
		}
		static void jointSetupAnchored7(ofxBox2dJoint *joint, ofxBox2d& box2d, b2Body *body1, b2Body *body2, ofPoint anchor1, ofPoint anchor2, float frequencyHz, float damping, bool bCollideConnected) {
			joint->setup(box2d.world, body1, body2,
				b2Vec2(anchor1.x, anchor1.y), b2Vec2(anchor2.x, anchor2.y),
				frequencyHz, damping, bCollideConnected);
		}
		static ofPoint jointGetReactionForce(ofxBox2dJoint *joint, float inv_dt) {
			ofVec2f p = joint->getReactionForce(inv_dt);
			return ofPoint(p.x, p.y);
		}
		
		/// polygon
		static void polygonSetup(ofxBox2dPolygon *poly, ofxBox2d& box2d) {
			poly->create(box2d.world);
		}
		static void polygonAddTriangle(ofxBox2dPolygon *poly, const ofPoint& a, const ofPoint& b, const ofPoint& c) {
			poly->addTriangle(ofVec3f(a.x, a.y), ofVec3f(b.x, b.y), ofVec3f(c.x, c.y));
		}
		static void poylgonSimplify0(ofxBox2dPolygon *poly) {
			poly->simplify();
		}
		static void polygonTriangulate0(ofxBox2dPolygon *poly) {
			poly->triangulate();
		}
		static ofPoint polygonGetCenter(ofxBox2dPolygon *poly) {
			ofVec2f p = poly->getCenter();
			return ofPoint(p.x, p.y);
		}
		static void polygonAddAttractionPoint2(ofxBox2dPolygon *poly, ofPoint& p, float amt){
			poly->addAttractionPoint(ofVec2f(p.x, p.y), amt);
		}
		static void polygonAddRepulsionForce2(ofxBox2dPolygon *poly, ofPoint& p, float amt) {
			poly->addRepulsionForce(ofVec2f(p.x, p.y), amt);
		}
		
		/// copied from polyline
		/// polyline
		static void polylineAddVertex2(ofPolyline* line, float x, float y) {
			line->addVertex(x, y);
		}
		static void polylineLineTo2(ofPolyline* line, float x, float y) {
			line->lineTo(x, y);
		}
		static void polylineArcPoint5(ofPolyline* line, const ofPoint & center, float radiusX, float radiusY, float angleBegin, float angleEnd) {
			line->arc(center, radiusX, radiusY, angleBegin, angleEnd);
		}
		static void polylineArcPoint6(ofPolyline* line, const ofPoint & center, float radiusX, float radiusY, float angleBegin, float angleEnd, bool clockwise) {
			line->arc(center, radiusX, radiusY, angleBegin, angleEnd, clockwise);
		}
		static void polylineArcFloat6(ofPolyline* line, float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd) {
			line->arc(x, y, radiusX, radiusY, angleBegin, angleEnd);
		}
		static void polylineArcFloat7(ofPolyline* line, float x, float y, float z, float radiusX, float radiusY, float angleBegin, float angleEnd) {
			line->arc(x, y, z, radiusX, radiusY, angleBegin, angleEnd);
		}
		static void polylineArcNegativePoint5(ofPolyline* line, const ofPoint & center, float radiusX, float radiusY, float angleBegin, float angleEnd) {
			line->arcNegative(center, radiusX, radiusY, angleBegin, angleEnd);
		}
		static void polylineArcNegativeFloat6(ofPolyline* line, float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd) {
			line->arcNegative(x, y, radiusX, radiusY, angleBegin, angleEnd);
		}
		static void polylineArcNegativeFloat7(ofPolyline* line, float x, float y, float z, float radiusX, float radiusY, float angleBegin, float angleEnd) {
			line->arcNegative(x, y, z, radiusX, radiusY, angleBegin, angleEnd);
		}
		static void polyLineCurveToPoint1(ofPolyline* line, const ofPoint& to) {line->curveTo(to);}
		static void polyLineCurveToFloat2(ofPolyline* line, float x, float y) {line->curveTo(x, y);}
		static void polyLineCurveToFloat3(ofPolyline* line, float x, float y, float z) {line->curveTo(x, y, z);}
		
		static void polylineBezierToPoint3(ofPolyline* line, const ofPoint & cp1, const ofPoint & cp2, const ofPoint & to) {
			line->bezierTo(cp1, cp2, to);
		}
		static void polylineBezierToFloat6(ofPolyline* line, float cx1, float cy1, float cx2, float cy2, float x, float y) {
			line->bezierTo(cx1, cy1, cx2, cy2, x, y);
		}
		static void polylineBezierToFloat9(ofPolyline* line, float cx1, float cy1, float cz1, float cx2, float cy2, float cz2, float x, float y, float z) {
			line->bezierTo(cx1, cy1, cz1, cx2, cy2, cz2, x, y, z);
		}
		static void polylineQuadBezierToPoint3(ofPolyline* line, const ofPoint & cp1, const ofPoint & cp2, const ofPoint & to) {
			line->quadBezierTo(cp1, cp2, to);
		}
		static void polylineQuadBezierToFloat6(ofPolyline* line, float cx1, float cy1, float cx2, float cy2, float x, float y) {
			line->quadBezierTo(cx1, cy1, cx2, cy2, x, y);
		}
		static void polylineQuadBezierToFloat9(ofPolyline* line, float cx1, float cy1, float cz1, float cx2, float cy2, float cz2, float x, float y, float z) {
			line->quadBezierTo(cx1, cy1, cz1, cx2, cy2, cz2, x, y, z);
		}
		static ofPolyline polylineGetSmoothed1(ofPolyline* line, float smoothingSize) {
			return line->getSmoothed(smoothingSize);
		}
		static ofPoint polylineGetClosestPoint1(ofPolyline* line, const ofPoint& target) {
			return line->getClosestPoint(target);
		}
		static unsigned int polylineGetClosestPointIndex(ofPolyline* line, const ofPoint& target) {
			unsigned int index = 0;
			line->getClosestPoint(target, &index);
			return index;
		}
		static void polylineSimplify0(ofPolyline* line) {
			line->simplify();
		}
		static ofPoint polylineGetPoint(ofPolyline* line, unsigned int index) {
			return line->getVertices()[index];
		}
		static void polylineSetPoint(ofPolyline* line, unsigned int index, const ofPoint& p) {
			line->getVertices()[index] = p;
		}
};

} // namespace
