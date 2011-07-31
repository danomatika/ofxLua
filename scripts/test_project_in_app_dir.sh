#! /bin/bash

WD=$(dirname $0)

APP="ofxLuaExample-beta"

###

cd $WD

# copy example
echo -e "\n== Copying example ==\n"
mkdir -p ../../../apps/myApps/exampleTest
cp -R ../example/* ../../../apps/myApps/exampleTest

# cd
cd ../../../apps/myApps/exampleTest

# build
echo -e "== Building ==\n"
xcodebuild -project $APP.xcodeproj -alltargets
RETVAL=$? # get return value of last cmd
if [ $RETVAL -ne 0 ] ; then
	echo -e "\n== Build Failed ==\n"
	say "build failed"
	open $APP.xcodeproj
	exit 1
fi
echo -e "\n== Build Succeeded ==\n"
say "build succeeded"

# cleanup
echo -e "== Removing exampleTest ==\n"
cd ../
rm -rf exampleTest

exit $RETVAL

