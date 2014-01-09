ofxLua
======
<p align="center">
<img src="https://raw.github.com/danomatika/ofxLua/master/res/logo.png"/>
</p>

a Lua instance addon

Copyright (c) [Dan Wilcox](danomatika.com) 2011-2012

BSD Simplified License.

For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "LICENSE.txt," in this distribution.

See https://github.com/danomatika/ofxLua and the [Openframeworks Forum post](http://forum.openframeworks.cc/index.php?topic=6493.0) for documentation

Description
-----------

ofxLua is an Open Frameworks addon for running a Lua embedded scripting interpreter within an OpenFrameworks application. Using the luabind library, C++ functions and classes can be bound to the lua api allowing them to be called within a lua script. This is useful in separating the upper level logic from the lower level application and is utilized in numerous video games and applications.

In addition, ofxLua provides bindings for the OpenFrameworks API.

[Lua](http://www.lua.org/) combines simple procedural syntax with powerful data description constructs based on associative arrays and extensible semantics. Lua is dynamically typed, runs by interpreting bytecode for a register-based virtual machine, and has automatic memory management with incremental garbage collection, making it ideal for configuration, scripting, and rapid prototyping.

[Luabind](http://www.rasterbar.com/products/luabind.html) is a library that helps you create bindings between C++ and Lua. It has the ability to expose functions and classes, written in C++, to Lua. It will also supply the functionality to define classes in lua and let them derive from other lua classes or C++ classes. Lua classes can override virtual functions from their C++ baseclasses.

[OpenFrameworks](http://www.openframeworks.cc) is a cross platform open source toolkit for creative coding in C++

Build Requirements
------------------

To use ofxLua, first you need to download and install Open Frameworks. ofxPdExample-beta.xcodeproj is developed against the latest version of Open Frameworks on github (007). OF0062 support will be forth coming. 

[OF github repository](https://github.com/openframeworks/openFrameworks)

Currently, ofxLua is being developed on Mac OSX. You will need to install Xcode from the Mac Developer Tools.

For Linux, makefiles are included.

The code should work on Windows, but requires Visual Studio and/or Codeblocks project files to be built. Also, you'll need to install Boost and add paths for luabind to find it.

Installation and Build
----------------------

Place ofxLua within a folder in the apps folder of the OF dir tree:
<pre>
openframeworks/addons/ofxLua
</pre>

### Which version to use?

If you are using a stable version (0062, 007, ...) of OpenFrameworks then you want to use a git tag of ofxLua for that version. You can select the tag in the Github "Current Branch" menu or clone and check it out using git.

For example, the following commands will clone ofxLua and switch to the OF 0062 tagged version:
<pre>
git clone git://github.com/danomatika/ofxLua.git
cd ofxLua
git checkout 0062
</pre>

The master branch of ofxLua will work with the current stable version of OpenFrameworks and can be considered *relatively* stable.

### Dependencies

ofxLua includes the lua and luabind library source files. Luabind requires the [Boost C++ libraries](http://www.boost.org/). Install Boost and include the header and search paths in your project.

### Mac OSX

See the [Homebrew](http://mxcl.github.com/homebrew/) or [Macports](http://www.macports.org) package managers for easy install.

The install command for Homebrew is:
<pre>
brew install boost
</pre>

This takes a looong time.

### iOS

A precompiled Boost framework is included in lib/boost as compiling for arm is non-trivial. See [Building Boost for iOS](http://goodliffe.blogspot.com/2010/09/building-boost-framework-for-ios-iphone.html) for more info.

### Linux

Install the boost development library with your distro's package manager.

For example, in Ubuntu you can use apt-get in the terminal:
<pre>
sudo apt-get install libboost-dev
</pre>

Running the Example Project
---------------------------

The example projects are in the `example` & `exampleIOS` folders.

### OSX

Open the Xcode project, select the "example-Debug" scheme, and hit "Run".

### Linux

Open the Code::Blocks .cbp and hit F9 to build. Optionally, you can build the example with the Makefile.

To build and run it on the terminal:
<pre>
make
make run
</pre>

How to Create a New ofxLua Project
----------------------------------

To develop your own project based on ofxLua, simply copy an example project and rename it. You probably want to put it in your apps folder, for example, after copying:
<pre>
openFrameworks/addons/ofxLua/example/ => openFrameworks/apps/myApps/example/
</pre>

It must be 3 levels down in the openframeworks folder structure.

Then after renaming:
<pre>
openFrameworks/apps/myApps/myLuaProject/
</pre>

On Mac, rename the project in Xcode (do not rename the .xcodeproj file in Finder!): Long click on the project name in the project tree.

Adding ofxLua to an Existing Project
------------------------------------

If you want to add ofxLua to another project, you need to make sure you include the following src files:
<pre>
openFrameworks/addons/ofxLua/src/ofxLua.h
openFrameworks/addons/ofxLua/src/ofxLua.cpp
openFrameworks/addons/ofxLua/src/ofxLuaFileWriter.h
openFrameworks/addons/ofxLua/src/ofxLuaFileWriter.cpp
</pre>
and optionally
<pre>
openFrameworks/addons/ofxLua/src/ofxLuaWrapper.h
</pre>

On older Mac OSXs (pre 10.8), a header file which is included with the OS contains some macros which conflict with several lua macros. They can be renamed by setting this CFLAG:
<pre>
-D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0
</pre>
This is already set in the static lib Xcode project. See more details [here](http://boost-geometry.203548.n3.nabble.com/problems-with-Boost-Geometry-Xcode-compile-td437866.html).

luabind requires the header search path to the luadbind sources:
<pre>
../../addons/ofxLua/libs/lua
../../addons/ofxLua/libs/lua/lua
../../addons/ofxLua/libs/luabind
</pre>
and the header and library search paths to the Boost C++ libraries. See the Project.xconfig of the example project.

### For Xcode:

Include these src files:
<pre>
openFrameworks/addons/ofxLua/src/ofxLua.h
openFrameworks/addons/ofxLua/src/ofxLua.cpp
openFrameworks/addons/ofxLua/src/ofxLuaWrapper.h
</pre>

You also need to include the static library Xcode project for the lua and luabind libraries:
<pre>
# mac os
openFrameworks/addons/ofxLua/lib/luabind.xcodeproj
# or ios
openFrameworks/addons/ofxLua/lib/luabind-ios.xcodeproj
</pre>

Finally you need to include the header and library search paths required by luadbind. The provided static library xcode project includes the `/usr/local/lib` and `/usr/local/lib` search paths (as used by the Homebrew package manager) to the luabind static lib target. You'll need to change these if Boost is installed to a different dir.

For iOS, you can simply use the included boost.framework in lib/boost/osx. Drag and drop the file form the Finder onto your XCode project tree under addons/ofxLua.

Instructions:

* right click and create a new group "ofxLua"
* drag ofxLua/src into "ofxLua"
* * create a subgroup in ofxLua called "libs"
* drag the `ofxLua/libs/lua` and `ofxLua/libs/luabind` folders into the "ofxLua/libs" subgroup
* drag the `ofxLua/libs/luabind` or `ofxLua/libs/luabind-ios` Xcode project into the "ofxLua/libs" subgroup, make sure the checkbox is checked for your project target in the add dialog box
* under Target->Build Phases, add the static lib project to Target Dependencies and both the lua and luabind libs to Link Binary with Libraries
* under Targets->YourApp->Build->Header Search Paths (make sure All Configurations and All Settings are selected) add:
  * `../../../addons/ofxLua/libs/lua`
  * `../../../addons/ofxLua/libs/lua/lua`
  * `../../../addons/ofxLua/libs/luabind`
  * the path to the Boost headers (for Homebrew, it's `/usr/local/include`)
* under Targets->YourApp->Build->Library Search Paths (make sure All Configurations and All Settings are selected) add the path to the Boost headers

### For Linux (Ubuntu)

Compile the example by running "make".

To use ofxLua in a new project, simply add `ofxLua` to the project's addons.make file.

OF API Bindings
---------------

Luabind bindings for the OF API can be found in `src/bindings`. The implementation is split into separate .cpp files to help keep compilation down to a reasonable degree (as opposed to using all headers).

Currently, it covers *most* of the api and leaves out things involving pointers. More specific documentation may come at a future date, but for now check the example scripts on usage.

To invoke them with ofxLua, simply include ofxLuaBindings.h & call:

    #include "ofxLuaBindings.h"
    ...
    lua.bind<ofxLuaBindings>;
    
If you don't need the bindings in your project, just remove the `src/bindings` folder from your project files.

Developing
----------

You can help develop ofxLua on GitHub: [https://github.com/danomatika/ofxLua](https://github.com/danomatika/ofxLua)

Create an account, clone or fork the repo, then request a push/merge.

If you find any bugs or suggestions please log them to GitHub as well.

### Trying Newer Lib Versions

There are a number scripts in the scripts folder which are used to update the various libraries (lua, luabind, and boost for iOS) used by ofxLua. Try editing the version setting in the script header and running the script to download new sources or, in the case of boostoniphone, build a new framework.

Bugs / Issues
-------------

### No matching function for call to 'deduce_signature...'

This usually occurs when the trying to bind a function that takes more then 10 arguments. You can change this upper limit using a define when building the luabind lib: LUABIND_MAX_ARITY.

### Reference to 'object' is ambiguous compile error

Luabind has been updated to build with clang (aka LVMM) in Xcode, so this should not be an issue. See this [Github issue](https://github.com/luabind/luabind/issues/4) for details.

With older versions of ofxLua:

If you get a reference to 'object' is ambiguous error at compile time in Xcode, you need to change the compiler from clang to gcc for the luabind static library project. See the Luabind [user forum](http://sourceforge.net/mailarchive/forum.php?thread_name=9D67FA74-F0F7-4AE4-8B2D-C1873A744D51%40fysh.org&forum_name=luabind-user) for more details.

This is set by default in the luabind static library project file.
