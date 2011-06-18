#! /bin/bash

WD=$(dirname $0)

VER=5.1.4

###

cd $WD

# get latest source
wget http://www.lua.org/ftp/lua-$VER.tar.gz
tar -xvf lua-$VER.tar.gz

# remove lua standalone console and compiler sources
rm -v lua-$VER/src/lua.c lua-$VER/src/luac.c

# create dir
mkdir -p ../src/lua

# copy license
cp -v lua-$VER/COPYRIGHT ../src/lua

# copy sources
cp -v lua-$VER/src/*.h ../src/lua
cp -v lua-$VER/src/*.c ../src/lua
cp -v lua-$VER/etc/*.hpp ../src/lua

# cleanup
rm -rfv lua*

