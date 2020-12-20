Lua Modules
===========

Lua supports loading dynamic modules which are pre-compiled bits of code which
add new functionality (aka "libraries" or "plugins"). THey can be loaded using
the lua `require` mechanism.

An ofxLua project can add additional functionality to the Lua environment by:

1. compiling in custom Lua bindings to C/C++ code
2. loading a dynamic module created from custom Lua bindings & C/C++ code

Creating A Module for ofxLua
----------------------------

The basics for building a dynamic Lua module are found here: http://lua-users.org/wiki/BuildingModules

To save time, the `modules/module.mk` helper makefile wraps up most of the steps needed. See the header documentation in the makefile for more info.

_Note: If the Lua version used by ofxLua is changed, the module may need to be rebuilt in order to be loaded again._

ofxSyphon Module
----------------

The `modules/syphon` example project will build ofxSyphon as a module (macOS only). See `modules/syphon/Makefile` for how it calls `module.mk`.

To build `syphon.so`, install ofxSyphon to the root OF `addons` directory, then:

~~~
cd modules/syphon
make
~~~

If all went well, there should now be a `syphon.so` Lua module and `Syphon.framework` in the directory. The module should be loadable in a Lua script using if the module is in the same location:

```lua
require "syphon"
```

See `modules/syphon/test.lua` for an example Lua script which will work with the luaExample.

_Note: The framework is required by the module and must be located in the same directory as `syphon.so`. You can move them, but they must be kept together._
