/*
	ofxSyphon bindings

	2020 Dan Wilcox <danomatika@gmail.com>
*/

%module syphon
%{
#include "../../../ofxSyphon/src/ofxSyphon.h"
%}

%include <attribute.i>

// STL types
%include <std_string.i>

// ----- Renaming -----

// strip "ofxSyphon" prefix from classes
%rename("%(strip:[ofxSyphon])s", %$isclass) "";

// strip "ofxSyphon" prefix from global functions & make first char lowercase
%rename("%(regex:/ofxSyphon(.*)/\\l\\1/)s", %$isfunction) "";

////////////////////////////////////////////////////////////////////////////////
// ----- BINDINGS --------------------------------------------------------------

// ofxSyphon is still using "string" instead of "std::string"
typedef std::string string;

// dummy typedef for ofxSyphonServerDirectoryEventArgs
class ofEventArgs {};

// includes
%include "../../../ofxSyphon/src/ofxSyphonClient.h"
%include "../../../ofxSyphon/src/ofxSyphonServer.h"
%include "../../../ofxSyphon/src/ofxSyphonServerDirectory.h"
