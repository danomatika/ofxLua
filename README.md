ofxLua
======
<p align="center">
<img src="https://raw.github.com/danomatika/ofxLua/master/res/logo.png"/>
</p>

a Lua instance addon

Copyright (c) [Dan Wilcox](danomatika.com) 2011,2015

BSD Simplified License.

For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "LICENSE.txt," in this distribution.

See <https://github.com/danomatika/ofxLua> and the [Openframeworks Forum post](http://forum.openframeworks.cc/t/ofxlua/6493) for documentation

Description
-----------

ofxLua is an Open Frameworks addon for running a Lua embedded scripting interpreter within an OpenFrameworks application. Using the SWIG (Simple Wrapper and Interface Generator) tool, C++ functions and classes can be bound to the Lua api allowing them to be called within a Lua script. This is useful in separating the upper level logic from the lower level application and is utilized in numerous video games and applications.

In addition, ofxLua provides bindings for the OpenFrameworks API.

[Lua](http://www.lua.org/) combines simple procedural syntax with powerful data description constructs based on associative arrays and extensible semantics. Lua is dynamically typed, runs by interpreting bytecode for a register-based virtual machine, and has automatic memory management with incremental garbage collection, making it ideal for configuration, scripting, and rapid prototyping.

[SWIG](http://www.swig.org) is a software development tool that connects programs written in C and C++ with a variety of high-level programming languages. It is used to generate the C++ bindings which wrap the OpenFrameworks API for Lua.

(Optional) [LuaJIT](http://luajit.org/luajit.html) is a Just-In-Time Compiler (JIT) for the Lua programming language. It implements the Lua API but is optimized for performance over the standard Lua distribution. It is recommended to use LuaJIT when speed is a concern and it is enabled on embedded Linux in `addon_config.mk` for this reason.

[OpenFrameworks](http://www.openframeworks.cc) is a cross platform open source toolkit for creative coding in C++

Build Requirements
------------------

To use ofxLua, first you need to download and install OpenFrameworks. The examples are developed against the latest release version of OpenFrameworks on <openframeworks.cc/download>.

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

You'll need to checkout the swig-openframeworks submodule as well using:

    git submodule init
    git submodule update

### Dependencies

For embedded Linux (arm, Raspberry Pi, etc), [LuaJIT](http://luajit.org/luajit.html) is used for better performance. Make sure you have the **luajit-5.1** development package installed.

Running the Example Projects
----------------------------

The example projects are in the `luaExample` & `luaExampleIOS` folders.

Project files for the examples are not included so you will need to generate the project files for your operating system and development environment using the OF ProjectGenerator which is included with the OpenFrameworks distribution.

Point the ProjectGenerator to `addons/ofxLua`, change the project name to the **exact** name of the example you want to generate (ie `luaExample`), and make sure to choose `ofxLua` from the addons. Hitting "Generate Project" will populate that example with the project files you will need to build it.

### OSX

Open the Xcode project, select the "luaExample Debug" scheme, and hit "Run".

### Linux

Open the Code::Blocks .cbp and hit F9 to build. Optionally, you can build the example with the Makefile.

To build and run it on the terminal:
<pre>
make
make run
</pre>

How to Create a New ofxLua Project
----------------------------------

### ProjectGenerator

Simply select ofxLua from the available addons in the ProjectGenerator before generating a new project.

### Manual Method

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

### ProjectGenerator

Select ofxLua and other addons used by your project from the available addons in the ProjectGenerator, select the parent folder of your project, and set the *exact* name of the existing project in the text box. This will overwrite the existing project files with new ones that now include ofxLua.

*Note: you will lose any custom settings you've added manually to your project.*

### Manual Method

If you want to add ofxLua to another project, you need to make sure you include the following src files:
<pre>
openFrameworks/addons/ofxLua/src/ofxLua.h
openFrameworks/addons/ofxLua/src/ofxLua.cpp
openFrameworks/addons/ofxLua/src/ofxLuaFileWriter.h
openFrameworks/addons/ofxLua/src/ofxLuaFileWriter.cpp
</pre>
and optionally
<pre>
openFrameworks/addons/ofxLua/src/bindings/ofxLuaBindings.h
openFrameworks/addons/ofxLua/src/bindings/YOURPLATFORM/ofxLuaBindings.cpp
</pre>

On older Mac OSXs (pre 10.8), a header file which is included with the OS contains some macros which conflict with several lua macros. They can be renamed by setting this CFLAG:
<pre>
-D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0
</pre>

#### For Xcode:

Include these src files:
<pre>
openFrameworks/addons/ofxLua/src/ofxLua.h
openFrameworks/addons/ofxLua/src/ofxLua.cpp
openFrameworks/addons/ofxLua/src/ofxLuaFileWriter.h
openFrameworks/addons/ofxLua/src/ofxLuaFileWriter.cpp
openFrameworks/addons/ofxLua/src/bindings/ofxLuaBindings.h
</pre>

You also need to include the platform specific OF API bindings:
<pre>
# mac os
openFrameworks/addons/ofxLua/src/bindings/desktop/ofxLuaBindings.cpp
# or ios
openFrameworks/addons/ofxLua/src/bindings/ios/ofxLuaBindings.cpp
</pre>

Finally you need to include the header and library search paths required by luadbind. The provided static library xcode project includes the `/usr/local/lib` and `/usr/local/lib` search paths (as used by the Homebrew package manager) to the luabind static lib target. You'll need to change these if Boost is installed to a different dir.

Instructions:

* right click and create a new group "ofxLua"
* drag ofxLua/src into "ofxLua"
* remove bindings files that do not match your platform aka remove `src/bindings/desktop` for iOS

OF API Bindings
---------------

SWIG generated bindings for the OF API can be found in `src/bindings`. Currently it covers *most* of the api while leaving out base classes. More specific documentation may come at a future date, but for now check the example scripts on usage.

### Basic documentation:

There is a main "of" module and functions, classes, constants, & enums are renamed:
	
* **function**: ofBackground -> of.background
* **class**: ofColor -> of.Color
* **constant**: OF_LOG_VERBOSE -> of.LOG_VERBOSE
* **enum**: ofShader::POSITION_ATTRIBUTE -> of.Shader.POSITION_ATTRIBUTE

Functions that return a std::vector return a wrapped std::vector in Lua. As with Lua tables, indexes start at 1.

To see the main differences with the OF C++ API run the following:

    grep DIFF swig/openFrameworks.i
     
   
To see work to be done on the bindings run:

    grep TODO swig/openFrameworks.i


### Classes

Simple Lua class support is provided by the class() function from the [Lua Users wiki](http://lua-users.org/wiki/SimpleLuaClasses). This implementation allows for inheritance and usage is as follows:

    -- class declaration
    MyClass = class()
    
    -- constructor & attributes
    function MyClass:__init(x, y)
       self.x = x
       self.y = y
       self.bBeingDragged = false
       self.bOver = false
       self.radius = 4
    end

    -- create instance & access attribute
    myclass = MyClass(10, 10)
    myclass.x = 100 
    
    -- inherit first class and add an attribute
    MyClass2 = class(MyClass)
    function MyClass2:__init(x, y, z)
    	self.z = z
    end
    
    -- create instance of derived class & access attributes
    myclass2 = MyClass2(10, 10, 5)
    myclass2.x = 100
    myclass2.z = 100

Making Your Own Bindings
------------------------

### SWIG Interface

Create a SWIG interface file (*.i) with includes headers for the functions and classes which you want to bind. You then run SWIG with this file to generate the  *.cpp wrapper.

It could be as simple as the following:.

*MyCode.h*, your custom code:

    #pragma once
    
	#include "ofMain.h"
    
    float myFunction(float aNumber) {
        return aNumber+1;
	}
    
    class MyCoolClass {
    	public:
    		
    		MyCoolClass() {
			    myFloat = 0;
				myInt = 0;
				aString = "hello world";
			}
    		MyCoolClass(float aNumber) {
			    myFloat = aNumber;
				myInt = (int) aNumber;
				aString = "foo bar";
			}
    		
    		// member function
    		void doSomething() {
				ofLog() << "did something: " << aString;
			}
    		
    		// getter/setter
    		void setInt(int newInt) {myInt = newInt;}
    		int getInt() {return myInt;}
    		
    		// member variable, read/write
    		string aString;

		protected:

            // some protected member variables, won't be wrapped
		    float myFloat;
			int myInt;
    };

*MyBindings.i*, your custom SWIG interface file:

   	%module my
    %{
        // include any needed headers here
		#include "MyCode.h"
    %}
    
    // include custom code you want to be wrapped,
    // note the '%' instead of '#' as '%include' is a SWIG
    // command to wrap code in the given header
    %include "MyCode.h"
    
    // that's it, swig will handle the rest!

### Generate .cpp Wrapper

Now call SWIG to generate your .cpp wrapper:

    swig -c++ -lua -fcompact -fvirtual -I../../../libs/openFrameworks MyBindings.i
    
*Make sure to add search paths to headers used by your code (aka the "-I" line in the command above).*

If all went well, SWIG will have generated the `MyBindings_wrap.cxx` C++ file. Put this into your project's source directory and build it with your project.

### Opening Your Lua Library

You will need to open your new Lua library provided by the SWIG-generated .cpp file in order to use it in your lua state.

SWIG creates a "luaopen" C function using your module name which, in this case, will be "luaopen_my". This function needs to be defined in C++ in order to be used, so add it to the top of the .cpp file where you initialize your ofxLua object:

    // declare the module bindings
    extern "C" {
	    int luaopen_my(lua_State* L);
    }

Then call this function after initing ofxLua:

    lua.init(true);
	luaopen_my(lua); // open bindings

### Using Your Lua Library
    
If everything is working, you should be able to call your bindings in Lua using your new "my" module:
    
    aNumber = my.function(3.45)
    
    -- class
    coolClass = my.CoolClass() -- constructor
    coolClass = my.CoolClass(1.23) -- constructor with float
    
    -- note: use ':' not '.' to call class instance member functions
    coolClass:doSomething()
    
    -- properties are access with a '.'
    coolClass.anInt = 10
    coolClass.aString = "hello world"

See the SWIG interface file in `swig` and the [SWIG and Lua](http://swig.org/Doc1.3/Lua.html) documentation for more information. SWIG will handle most genral cases for you, but there are plenty of details to get into if you want greater customization.

If you end up having lots of custom code to bind, it's recommended to create multiple SWIG interface files which are included into a single *.i using the %include command. Do not create seaprate files with the same module name, only set the module in the main file as SWIG is designed for 1 module per main interface.

**Do not** open issues or bug reports if the problem is in writing your own bindings as this is all handled by SWIG. Be sure to search online for similar errors with "swig" as part of your search. More likely than not, it's an issue with your bindings and not with ofxLua.

Developing
----------

You can help develop ofxLua on GitHub: <https://github.com/danomatika/ofxLua>

Create an account, clone or fork the repo, then request a push/merge.

If you find any bugs or suggestions please log them to GitHub as well.

Known Issues
------------

### ld: -pie error on iOS

If you get the following error after generating an iOS app:

    ld: -pie can only be used when targeting iOS 4.2 or later

change the deployment target in your project settings under the General Tab to something higher than 4.2, say 7.0.
