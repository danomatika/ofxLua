#
# Makefile to generate OF bindings using SWIG
#
# 2014 Dan Wilcox <danomatika@gmail.com>
#

SWIG = swig
LANG = lua
TARGET = desktop

SRC_DIR = ../src
DEST_DIR = $(SRC_DIR)/$(TARGET)

OF_HEADERS = ../../../libs/openFrameworks

CFLAGS = -I$(OF_HEADERS)
CXXFLAGS = $(CFLAGS)

.PHONY: all debug clean desktop ios

# generates ofxLuaBindings.h & ofxLuaBindings.cpp
bindings:

	@echo Generating for: desktop
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo DEST_DIR = $(DEST_DIR)
	
	$(SWIG) -c++ -$(LANG) -fcompact -fvirtual $(CXXFLAGS) openFrameworks.i
	mv openFrameworks_wrap.cxx ofxLuaBindings.cpp

	$(SWIG) -c++ -$(LANG) -external-runtime ofxLuaBindings.h
	
	mkdir -p $(DEST_DIR)
	mv *.h $(SRC_DIR)
	mv *.cpp $(DEST_DIR)

# outputs debug symbols
debug:
	$(SWIG) -c++ -$(LANG) -debug-lsymbols $(CXXFLAGS) openFrameworks.i > debug.txt
	rm -f *.cxx

clean:
	rm -f $(SRC_DIR)/ofxLuaBindings.h
	rm -rf $(SRC_DIR)/desktop
	rm -rf $(SRC_DIR)/ios
	rm -f debug.txt

# desktop OS generation
desktop-prepare:
	$(eval TARGET := desktop)
	$(eval CXXFLAGS := $(CFLAGS))
	$(eval DEST_DIR := $(SRC_DIR)/desktop)

desktop: desktop-prepare bindings

# iOS specific generation
ios-prepare:
	$(eval TARGET := ios)
	$(eval CXXFLAGS := $(CXXFLAGS) -DTARGET_OPENGLES -DTARGET_IOS)
	$(eval DEST_DIR := $(SRC_DIR)/ios)

ios: ios-prepare bindings
