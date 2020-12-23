# build helloworld example as a dynamic Lua module for use with ofxLua
#
# Dan Wilcox danomatika.com 2020

OF_DIR = ../../../..

module.name = helloworld

module.src.swig = helloworld.i
module.src.cpp = helloworld.cpp

module.cflags= -I./

include ../module.mk
