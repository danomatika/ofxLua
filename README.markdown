ofxLua: a Lua instance addon
===================================

Copyright (c) [Dan Wilcox](danomatika.com) 2011

BSD Simplified License.

For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "LICENSE.txt," in this distribution.

See https://github.com/danomatika/ofxLua for documentation

DESCRIPTION
-----------

ofxLua is an Open Frameworks addon for running a Lua embedded scripting interpreter within an OpenFrameworks application. Using the luabind library, C++ functions and classes can be bound to the lua api allowing them to be called within a lua script. This is useful in separating the upper level logic from the lower level application and is utilzied in numerous video games and applications.

[Lua](http://www.lua.org/) ombines simple procedural syntax with powerful data description constructs based on associative arrays and extensible semantics. Lua is dynamically typed, runs by interpreting bytecode for a register-based virtual machine, and has automatic memory management with incremental garbage collection, making it ideal for configuration, scripting, and rapid prototyping.

[Luabind](http://www.rasterbar.com/products/luabind.html) is a library that helps you create bindings between C++ and Lua. It has the ability to expose functions and classes, written in C++, to Lua. It will also supply the functionality to define classes in lua and let them derive from other lua classes or C++ classes. Lua classes can override virtual functions from their C++ baseclasses.

[OpenFrameworks](http://www.openframeworks.cc/) is a cross platform open source toolkit for creative coding in C++

BUILD REQUIREMENTS
------------------

To use ofxLua, first you need to download and install Open Frameworks. ofxPdExample-beta.xcodeproj is developed against the latest version of Open Frameworks on github (007). OF0062 supprot will be forth coming. 

[github repository](https://github.com/openframeworks/openFrameworks)

Currently, ofxPd is being developed on Mac OSX. You will need to install Xcode from the Mac Developer Tools.

The code should work on other platforms, but requires platform specific project files to be built.

BUILD AND INSTALLATION
----------------------

Place ofxLua within a folder in the apps folder of the OF dir tree:
<pre>
openframeworks/addons/ofxLua
</pre>

### How to Create a New ofxLua Project

To develop your own project based on ofxLua, simply copy the example project and rename it. You probably want to put it in your apps folder, for example, after copying:
<pre>
openFrameworks/addons/ofxLua/example/ => openFrameworks/apps/myApps/example/
</pre>

It must be 3 levels down in the openframeworks folder structure.

Then after renaming:
<pre>
openFrameworks/apps/myApps/myLuaProject/
</pre>

On Mac, rename the project in XCode (do not rename the .xcodeproj file in Finder!): XCode Menu->Project->Rename

### Adding ofxLua to an Existing Project

If you want to add ofxLua to another project, you need to make sure you include the src folder:
<pre>
openFrameworks/addons/ofxLua/src
</pre>

You will also need to include some additional C Flags for building the lua:

#### For XCode:

* create a new group "ofxPd" * drag these directories from ofxpd into this new group: ofxPd/src & ofxPd/libs
* add a search path to: `../../../addons/ofxPd/libs/libpd/pure-data/src` under Targets->YourApp->Build->Library Search Paths (make sure All Configurations and All Settings are selected)
* under Targets->YourApp->Build->Other C Flags (make sure All Configurations and All Settings are selected), add
	<pre>-DHAVE_UNISTD_H -DUSEAPI_DUMMY -DPD -dynamiclib -ldl -lm</pre>

#### For Linux:

* edit addons.make in your project folder and add the following line to the end of the file: 
	<pre>ofxPd</pre>
* edit config.make in your project folder and change the lines for USER_CFLAGS, USER_LDFLAGS and USER_LIBS to:
	<pre>USER_CFLAGS = -DHAVE_UNISTD_H -DUSEAPI_DUMMY -DPD -shared</pre>
	<pre>USER_LDFLAGS = --export-dynamic</pre>
	<pre>USER_LIBS = -ldl -lm</pre>

DEVELOPING
----------

You can help develop ofxLua on GitHub: [https://github.com/danomatika/ofxLua](https://github.com/danomatika/ofxLua)

Create an account, clone or fork the repo, then request a push/merge.

If you find any bugs or suggestions please log them to GitHub as well.

