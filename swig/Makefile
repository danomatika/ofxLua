#
# Makefile to generate OF bindings using SWIG
#
# 2014 Dan Wilcox <danomatika@gmail.com>
#
# running `make` generates desktop os lua bindings and puts them in ../src,
# running `make ios` generates ios lua bindings, etc
#
# override any of the following variables using make,
# i.e. to generate Puthon bindings with a different
# filename and dest location:
#
#     make LANG=python NAME=ofxPythonBindings DEST_DIR=../src/bindings
#

# swig command
SWIG = swig

# default output language, see swig -h for more
LANG = lua

# default platform target, available targets are:
#   * desktop: win, linux, & mac osx
#   * ios: apple iOS using OpenGL ES
#   * linuxarm: embedded linux using OpenGL ES
TARGET = desktop

# generated bindings filename
NAME = openFrameworks_wrap

# where to copy the generated bindings
DEST_DIR = ../src

# path to OF headers
OF_HEADERS = ../../../libs/openFrameworks

# C & C++ flags
CFLAGS = -I$(OF_HEADERS)
CXXFLAGS = $(CFLAGS)

.PHONY: all debug clean desktop ios linuxarm

# generates bindings
bindings:

	@echo Generating for: desktop
	@echo LANG = $(LANG)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo NAME = $(NAME)
	@echo DEST_DIR = $(DEST_DIR)
	
	$(SWIG) -c++ -$(LANG) -fcompact -fvirtual $(CXXFLAGS) openFrameworks.i
	mv openFrameworks_wrap.cxx $(NAME).cpp

	$(SWIG) -c++ -$(LANG) -external-runtime $(NAME).h

# move generated files to DEST_DIR
move:

	mkdir -p $(DEST_DIR)/$(TARGET)
	mv *.h $(DEST_DIR)
	mv *.cpp $(DEST_DIR)/$(TARGET)

# outputs debug symbols
debug:
	$(SWIG) -c++ -$(LANG) -debug-lsymbols $(CXXFLAGS) openFrameworks.i > debug.txt
	rm -f *.cxx

clean:
	rm -f $(DEST_DIR)/$(FILENAME).h
	rm -rf $(DEST_DIR)/desktop
	rm -rf $(DEST_DIR)/ios
	rm -f debug.txt

# desktop OS generation
desktop-prepare:
	$(eval TARGET := desktop)
	$(eval CXXFLAGS := $(CFLAGS))

desktop: desktop-prepare bindings move

# iOS specific generation
ios-prepare:
	$(eval TARGET := ios)
	$(eval CXXFLAGS := $(CXXFLAGS) -DTARGET_OPENGLES -DTARGET_IOS)

ios: ios-prepare bindings move

# embedded linux specific generation
linuxarm-prepare:
	$(eval TARGET := linuxarm)
	$(eval CXXFLAGS := $(CXXFLAGS) -DTARGET_OPENGLES)

linuxarm: linuxarm-prepare bindings move
