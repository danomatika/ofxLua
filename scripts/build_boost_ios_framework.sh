#! /bin/bash

WD=$(dirname $0)

VER=1.47.0
VER_FILE=1_47_0

IOS_VER=4.3

###

cd $WD

# get latest source
git clone git://gitorious.org/boostoniphone/boostoniphone.git

# cd
cd boostoniphone

# edit script for ios and boost version
perl -pi -e "s/IPHONE_SDKVERSION:=4.2/IPHONE_SDKVERSION:=$IOS_VER/g" boost.sh
perl -pi -e "s/1_44_0/$VER_FILE/g" boost.sh

# update boost sources to desired version
rm -rf boost_*.tar.bz2
wget http://sourceforge.net/projects/boost/files/boost/$VER/boost_$VER_FILE.tar.bz2/download

# build
./boost.sh

# copy framework
mkdir -p ../../lib/boost/ios
cp -Rv framework/* ../../lib/boost/ios

# cleanup
cd ../
rm -rf boostoniphone

