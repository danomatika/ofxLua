#! /bin/sh
#
# generate Lua bindings for all platforms
#

# stop on error
set -e

SWIG_FLAGS="DEST_DIR=../src/bindings"

# all targets, specify a single target as $1
TARGETS="desktop ios linuxarm header libs"
if [[ "$1" != "" && $(echo $TARGETS | grep -w $1) && true ]] ; then
	TARGETS=$1
	shift
fi

###

cd $(dirname $0)/../swig

for target in $TARGETS ; do
	make $target $SWIG_FLAGS $@
done
