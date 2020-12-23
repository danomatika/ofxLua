/*
	helloworld exmaple bindings

	2020 Dan Wilcox <danomatika@gmail.com>
*/

%module helloworld
%{
#include "helloworld.h"
%}

//%import(module="of") "../../src/bindings/ofBindings.h"

////////////////////////////////////////////////////////////////////////////////
// ----- BINDINGS --------------------------------------------------------------

// includes
%include "helloworld.h"
