#! /bin/bash
#
# generate Lua bindings for all platforms
#

WD=$(dirname $0)

###

cd $WD/../swig

make desktop NAME=ofxLuaBindings ATTRIBUTES=true
make ios NAME=ofxLuaBindings ATTRIBUTES=true
make linuxarm NAME=ofxLuaBindings ATTRIBUTES=true
