#! /bin/bash
#
# generate Lua bindings for all platforms
#

WD=$(dirname $0)

###

cd $WD/../swig

make desktop NAME=ofxLuaBindings
make ios NAME=ofxLuaBindings
make linuxarm NAME=ofxLuaBindings
