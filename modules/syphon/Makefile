# build ofxSyphon as a dynamic Lua module for use with ofxLua
#
# this addon is a little tricky as it requires Syphon.framework
#
# Dan Wilcox danomatika.com 2020

OF_DIR = ../../../..
SYPHON_DIR = ../../../ofxSyphon

module.name = syphon

module.src.swig = syphon.i
module.src.objc = $(SYPHON_DIR)/libs/Syphon/src/SyphonNameboundClient.m
module.src.objcpp = $(SYPHON_DIR)/src/ofxSyphonClient.mm \
                      $(SYPHON_DIR)/src/ofxSyphonServer.mm \
                      $(SYPHON_DIR)/src/ofxSyphonServerDirectory.mm

module.cflags = -I$(SYPHON_DIR)/src \
                -I$(SYPHON_DIR)/libs/Syphon/src \
                -F$(SYPHON_DIR)/libs/Syphon/lib/osx

module.ldflags = -framework Syphon

include ../module.mk

# copy framework to this dir
Syphon.framework:
	cp -R $(SYPHON_DIR)/libs/Syphon/lib/osx/$< .

# change framework loader path to look in same dir as module
postbuild:: $(MODULE) Syphon.framework
	install_name_tool $< -change \
		@loader_path/../Frameworks/Syphon.framework/Versions/A/Syphon \
		@loader_path/Syphon.framework/Versions/A/Syphon

clobber::
	rm -rf Syphon.framework
