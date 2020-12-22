# helper makefile to build a dynamic Lua module for use with ofxLua
#
# references:
# * http://lua-users.org/wiki/BuildingModules
# * http://www.swig.org/Doc3.0/Lua.html#Lua_nn5
#
# Dan Wilcox danomatika.com 2020
#
# basic usage:
# * create a makefile
# * fill in the required module.* variables (see below)
# * set the OF_DIR variable to the main openFrameworks directory
# * include this file
# * add any additional targets, as needed
#
# module variables:
# * module.name: module filename and Lua lib name (required)
# * module.src.swig: SWIG bindings interface (required)
# * implementation file lists (requires at least one if building .so/.dll):
#   - module.src.c: C files (.c)
#   - module.src.cpp: C++ files (.cpp)
#   - module.src.objc: Obj-C files (.m)
#   - module.src.objcpp: Obj-C++ files (.mm)
# * module.cflags: additional c flags
# * module.ldflags: additional linker flags
# * module.swigflags: additional SWIG command flags
#
# overridable targets (declare with :: in your makefile):
# * prebuild: called before linking the module
# * postbuild: called after linking the module
# * clean: remove interim build files
# * clobber: remove resulting build files
#
# quick example:
# ~~~
#
# module.name = hello
#
# module.src.swig = ofxHello.i
# module.src.cpp = ../ofxHello/src/hello.cpp ../ofxHello/src/foo.cpp
#
# module.cflags = -I../ofxHello/src
# module.ldflags = -lbar
# module.swigflags = -debug-classes
#
# OF_DIR = ../..
#
# include ../ofxLua/module/module.mk
#
# prebuild::
#     @echo starting build
#
# postbuild::
#     @echo build finished
#
# ~~~

CC=gcc

OF_DIR ?= ../../..

OF_CFLAGS = -I$(OF_DIR)/libs/openFrameworks \
			-I$(OF_DIR)/libs/openFrameworks/3d \
			-I$(OF_DIR)/libs/openFrameworks/app \
			-I$(OF_DIR)/libs/openFrameworks/gl \
			-I$(OF_DIR)/libs/openFrameworks/graphics \
			-I$(OF_DIR)/libs/openFrameworks/utils \
			-I$(OF_DIR)/libs/openFrameworks/communication \
			-I$(OF_DIR)/libs/openFrameworks/sound \
			-I$(OF_DIR)/libs/openFrameworks/types \
			-I$(OF_DIR)/libs/openFrameworks/math \
			-I$(OF_DIR)/libs/openFrameworks/events \
			-I$(OF_DIR)/libs/openFrameworks/video \
			-I$(OF_DIR)/libs/glew/include \
			-I$(OF_DIR)/libs/tess2/include \
			-I$(OF_DIR)/libs/boost/include \
			-I$(OF_DIR)/libs/utf8cpp/include \
			-I$(OF_DIR)/libs/poco/include \
			-I$(OF_DIR)/libs/cairo/include/cairo \
			-I$(OF_DIR)/libs/glfw/include \
			-I$(OF_DIR)/libs/fmodex/include \
			-I$(OF_DIR)/libs/utf8/include \
			-I$(OF_DIR)/libs/json/include \
			-I$(OF_DIR)/libs/pugixml/include

LUA_CFLAGS ?= -I$(OF_DIR)/addons/ofxLua/libs/lua

CFLAGS += $(OF_CFLAGS) $(LUA_CFLAGS) $(module.cflags)
CXXFLAGS += $(CFLAGS)
LDFLAGS += $(module.ldflags)

##### swig

SWIG = swig
LANG = lua
SWIG_FLAGS = -O -small $(module.swigflags)
SWIG_CFLAGS = -I$(OF_DIR)/libs/openFrameworks \
              -I$(OF_DIR)/addons

##### platform

UNAME = $(shell uname)
SOLIB_EXT = so

# macOS
ifeq ($(UNAME), Darwin)
CXXFLAGS += -std=c++11 -stdlib=libc++
LDFLAGS += -bundle -undefined dynamic_lookup
endif

# Windows, use Mingw
ifeq ($(UNAME), Windows_NT)
CC ?= gcc
SOLIB_EXT = dll
LDFLAGS += -shared
endif

# Linux
ifeq ($(UNAME), Linux)
LDFLAGS += -shared
endif

###### targets

MODULE = $(module.name).$(SOLIB_EXT)

BINDINGS = $(module.name)Bindings.cpp

OBJS = $(module.src.c:.c=.o) $(module.src.objc:.m=.o) \
       $(module.src.cpp:.cpp=.o) $(module.src.objcpp:.mm=.o) \
       $(BINDINGS:.cpp=.o)

.PHONY: all bindings module prebuild postbuild clean clobber

all: module

bindings: $(BINDINGS)

$(BINDINGS): $(module.src.swig)
	$(SWIG) -c++ -$(LANG) $(SWIG_FLAGS) $(SWIG_CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -O2 -fpic -c -o $@ $<

%.o: %.m
	$(CC) $(CFLAGS) -O2 -fpic -c -o $@ $<

%.o: %.cpp
	$(CC) $(CXXFLAGS) -O2 -fpic -c -o $@ $<

%.o: %.mm
	$(CC) $(CXXFLAGS) -O2 -fpic -c -o $@ $<

$(MODULE): $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

module: bindings prebuild $(MODULE) postbuild

# dummy, requires :: for use in calling makefile
prebuild:: ;

# dummy, requires :: for use in calling makefile
postbuild:: ;

clean::
	rm -f $(OBJS)

clobber::
	rm -f $(MODULE) $(BINDINGS)

##### platform-specific targets

# macOS
ifeq ($(UNAME), Darwin)

.PHONY: check

# check dylib / framework loader paths
check: $(MODULE)
	otool -L $<

endif
