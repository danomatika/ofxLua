#!/bin/bash

LUAJIT=luajit-2.0

### You must cd into the scripts folder for this to work! #############

#need absolute path for proper jit installation
CUR_DIR=$(pwd)
JIT_DEST=../libs/luajit
INSTALL_DIR=$CUR_DIR/$JIT_DEST

# Download jitlua
git clone http://luajit.org/git/luajit-2.0.git

# Create folder for installation files
mkdir -p $JIT_DEST

### BUILD LuaJIT-2.0 #################
cd $(LUAJIT)-2.0
# Build a 32-bit binary even if native machine is 64 bit, OF is 32 only.
make CC="gcc -m32"

### INSTALL LuaJIT-2.0 ###############
make install PREFIX=$INSTALL_DIR
mv COPYRIGHT $INSTALL_DIR/.
mv README $INSTALL_DIR/.

### Clean build files ###############
cd ../
rm -R $(LUAJIT)

### Clean install files ##############
rm -R $JIT_DEST/bin
