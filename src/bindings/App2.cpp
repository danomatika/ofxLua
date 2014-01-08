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
#include "App.h"

#include "../AppCore.h"

namespace lua {

float App::getWidth() {
	return ofGetWidth();
}
float App::getHeight() {
	return ofGetHeight();
}

float App::getMouseX() {
//	if(ofGetWindowMode() == OF_FULLSCREEN)
//		return Global::instance().core->parent.mouseX + Global::instance().core->parent.getOriginX();
//	else
		return ofGetMouseX();
}
float App::getMouseY() {
//	if(ofGetWindowMode() == OF_FULLSCREEN)
//		return Global::instance().core->parent.mouseY + Global::instance().core->parent.getOriginY();
//	else
		return ofGetMouseY();
}
int App::getMouseButton() {return Global::instance().core->mouseButton;}
bool App::getMousePressed() {return Global::instance().core->bMousePressed;}

int App::getKey() {return Global::instance().core->currentKey;}
bool App::getKeyPressed() {return Global::instance().core->bKeyPressed;}

//string App::getScenePath() {
//	return Global::instance().core->sceneManager.getCurrentSceneName();
//}

} // namespace
