#! /bin/bash

WD=$(dirname $0)

VER=0.9.1

###

cd $WD

# get latest source
wget "http://sourceforge.net/projects/luabind/files/luabind/$VER/luabind-$VER.tar.gz/download"
tar -xvf luabind-$VER.tar.gz

# create dir
mkdir -p ../src/luabind

# copy license
cp -v luabind-$VER/LICENSE ../src/luabind

# copy sources
cp -Rv luabind-$VER/luabind ../src/luabind
cp -Rv luabind-$VER/src ../src/luabind

# cleanup
rm -rfv luabind*

