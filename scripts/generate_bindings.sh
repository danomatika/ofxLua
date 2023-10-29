#! /bin/sh
#
# generate Lua bindings for all platforms
#

# stop on error
set -e

SWIG_FLAGS="DEST_DIR=../src/bindings"

###

cd $(dirname $0)/../swig

make desktop $SWIG_FLAGS $@
make ios $SWIG_FLAGS $@
make linuxarm $SWIG_FLAGS $@
make header $SWIG_FLAGS $@
make libs $SWIG_FLAGS $@
