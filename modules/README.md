Lua Modules
===========

Lua supports loading dynamic modules which are pre-compiled bits of code which
add new functionality (aka "libraries" or "plugins"). THey can be loaded using
the lua `require` mechanism.

An ofxLua project can add additional functionality to the Lua environment by:

1. compiling in custom Lua bindings to C/C++ code
2. loading a dynamic module created from custom Lua bindings & C/C++ code\*

\* _Note: Unfortunately, mixing static (compiled in) and dynamic SWIG-generated Lua modules is unstable (ie. random crashes when reloading, etc). It is best to init ofxLua with the ofBindings disabled when using custom SWIG-generated modules. See the [SWIG documentation](http://swig.org/Doc4.0/Modules.html#Modules_nn4) for more info._

Creating A Module for ofxLua
----------------------------

To save time, the `modules/module.mk` helper makefile wraps up most of the steps needed. See the header documentation in the makefile for more info.

### Dynamic Module

The basics for building a dynamic Lua module are found here: http://lua-users.org/wiki/BuildingModules

See the example projects on building a dynamic module.

_Note: If the Lua version used by ofxLua is changed, the module may need to be rebuilt in order to be loaded again. For instance, if loaf uses 5.3.5 and a module is compiled for 5.3.6 it may work, however if loaf uses 5.4.2 if probably won't._

### Static Module

As documented in the the main ofxLua readme, you can use SWIG to generate a \*Bindings.cpp bindings file which can be compiled into your project directly (statically). The `modules/module.mk` helper makefile can also be used to generate this file when running `make bindings` which requires only the `module.name` and `module.src.swig` variables. Next, add \*Bindings.cpp to your project when building and call it's lib init function when initing the Lua state.

helloworld Example Module
-------------------------

The `modules/helloworld` example project will build hellworld.cpp as a dynamic module. See `modules/helloworld/Makefile` for how it calls `module.mk`.

To build `helloworld.so` or `helloworld.dll`:

~~~
cd modules/helloworld
make
~~~

If all went well, there should now be a `helloworld.so` or `helloworld.dll` Lua module in the directory. The module should be loadable in a Lua script using if the module is in the same location:

```lua
require "helloworld"
```

See `modules/helloworld/test.lua` for an example Lua script which will work with the luaExample, assuming ofxLua is inited with ofBindings = false.
