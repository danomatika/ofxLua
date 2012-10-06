#! /bin/bash

WD=$(dirname $0)

VER=0.9.1

###

cd $WD

# get latest source
git clone git://github.com/luabind/luabind.git

# create dir
mkdir -p ../src/luabind

# copy license
cp -v luabind/LICENSE ../src/luabind

# copy sources
cp -Rv luabind/luabind ../src/luabind
cp -Rv luabind/src ../src/luabind

# cleanup
#rm  v$VER
rm -rf luabind*

