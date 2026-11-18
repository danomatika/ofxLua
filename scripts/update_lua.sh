#! /bin/sh

# stop on error
set -e

VER=5.5.1

SRC=lua-$VER
DEST=../libs/lua

###

cd $(dirname $0)

# get latest source
curl -O https://www.lua.org/ftp/$SRC.tar.gz
tar -xvf $SRC.tar.gz

# remove lua standalone console and compiler sources
rm -v $SRC/src/lua.c $SRC/src/luac.c

# create dir
mkdir -p $DEST

# copy license
test -f $SRC/COPYRIGHT && cp -v $SRC/COPYRIGHT $DEST

# copy sources
cp -v $SRC/src/*.h $DEST
cp -v $SRC/src/*.c $DEST
cp -v $SRC/src/*.hpp $DEST

# cleanup
rm -rf $SRC $SRC.tar.gz
