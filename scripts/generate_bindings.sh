#! /bin/bash
#
# generate Lua bindings for all platforms
#

WD=$(dirname $0)



###

cd $WD/../swig

make desktop NAME=ofxLuaBindings ATTRIBUTES=false $@
make ios NAME=ofxLuaBindings ATTRIBUTES=false $@
make linuxarm NAME=ofxLuaBindings ATTRIBUTES=false $@
