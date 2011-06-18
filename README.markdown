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

[Lua](http://www.lua.org/) combines simple procedural syntax with powerful data description constructs based on associative arrays and extensible semantics. Lua is dynamically typed, runs by interpreting bytecode for a register-based virtual machine, and has automatic memory management with incremental garbage collection, making it ideal for configuration, scripting, and rapid prototyping.

[Luabind](http://www.rasterbar.com/products/luabind.html) is a library that helps you create bindings between C++ and Lua. It has the ability to expose functions and classes, written in C++, to Lua. It will also supply the functionality to define classes in lua and let them derive from other lua classes or C++ classes. Lua classes can override virtual functions from their C++ baseclasses.

[OpenFrameworks](http://www.openframeworks.cc/) is a cross platform open source toolkit for creative coding in C++

BUILD REQUIREMENTS
------------------

To use ofxLua, first you need to download and install Open Frameworks. ofxPdExample-beta.xcodeproj is developed against the latest version of Open Frameworks on github (007). OF0062 support will be forth coming. 

[OF github repository](https://github.com/openframeworks/openFrameworks)

Currently, ofxLua is being developed on Mac OSX. You will need to install Xcode from the Mac Developer Tools.

The code should work on other platforms, but requires platform specific project files to be built.

BUILD AND INSTALLATION
----------------------

Place ofxLua within a folder in the apps folder of the OF dir tree:
<pre>
openframeworks/addons/ofxLua
</pre>

### Dependencies

ofxLua includes the lua and luabind library source files. Luabind requires the [Boost C++ libraries](http://www.boost.org/). Install Boost and include the header and search paths in your project.

For Mac OSX, see the [Homebrew](http://mxcl.github.com/homebrew/) or [Macports](http://www.macports.org/) package managers for easy install.

The install command for Homebrew is:
<pre>
brew install boost
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

If you want to add ofxLua to another project, you need to make sure you include the src files in:
<pre>
openFrameworks/addons/ofxLua/src
</pre>

You will also need to include some additional C Flags for building the lua:
<pre>
-DLUA_USE_LINUX
</pre>

Mac OSX has a header file which includes some macros which conflict with several lua macros. They can be renamed by setting this cflag:
<pre>
-D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0
</pre>
This is already set in the static lib xcode project. See more details [here](http://boost-geometry.203548.n3.nabble.com/problems-with-Boost-Geometry-Xcode-compile-td437866.html).

luabind requires the header search path to the luadbind sources:
<pre>
../../addons/ofxLua/src/luabind
</pre>
and the header and library search paths to the Boost C++ librarys.

#### For XCode:

Include these src files:
<pre>
openFrameworks/addons/ofxLua/src/ofxLua.h
openFrameworks/addons/ofxLua/src/ofxLua.cpp
openFrameworks/addons/ofxLua/src/ofxLuaWrapper.h
</pre>

You also need to include the static library xcode project for the lua and luabind libraries:
<pre>
openFrameworks/addons/ofxLua/lib/ofxLuaStaticLib.xcodeproj
</pre>

Finally you need to include the header and library search paths required by luadbind. The provided static library xcode project includes the `/usr/local/lib` and `/usr/local/lib` search paths (as used by the Homebrew package manager) to the luabind static lib target. You'll need to change these if Boost is installed to a different dir.

Instructions:

* right click and create a new group "ofxLua"
* create a subgroup in ofxLua called "src"
* drag the *.h and *.cpp files in ofxLua/src into the src subgroup (do not add the lua or luabind folders)
* drag the ofxLua/ofxLuaStaticLib xcode project into the ofxLua/src subgroup, make sure the checkbox is checked for your project target in the add dialog box
* drag the 2 libs under the ofxLuaStaticLib reference you just added into the Link Binary with Libraries under your project app target 
* under Targets->YourApp->Build->Header Search Paths (make sure All Configurations and All Settings are selected) add `../../../addons/ofxLua/src/luabind` and the path to the Boost headers
* under Targets->YourApp->Build->Library Search Paths (make sure All Configurations and All Settings are selected) add the path to the Boost headers

DEVELOPING
----------

You can help develop ofxLua on GitHub: [https://github.com/danomatika/ofxLua](https://github.com/danomatika/ofxLua)

Create an account, clone or fork the repo, then request a push/merge.

If you find any bugs or suggestions please log them to GitHub as well.

### luabind Source Modifications

The luabind source has been modified to make sure the exported names are not lost when linking (from this [message board entry](http://osdir.com/ml/lang.lua.bind.user/2007-06/msg00013.html)):

<pre>
class_registry.cpp lines 112-113: 
add luabind::detail:: before create_cpp_cpass_metatable
</pre>
