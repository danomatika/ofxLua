/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "ofUtils.h"
#include "ofImage.h"
#include "ofxLua.h"

namespace bindings {

// dummy classes for empty class enums

struct LoopType {};
struct WindowMode {};
struct AspectRatioMode {};
struct Alignment {};
struct RectMode {};
struct ScaleMode {};
struct ImageEnum {};
struct PixelFormat {};
struct BlendMode {};
struct Orientation {};
struct GradientMode {};
struct PolyWindingMode {};
struct HandednessLeft {};
struct HandednessRight {};
struct MatrixMode {};
struct MouseVars {};
struct KeyboardVars {};
struct DrawBitmapMode {};
struct _TextEncoding {};

// luabind registration
luabind::scope registerUtils() {
		
	using namespace luabind;
	
	return
	
		// TODO: wrap ofFileUtils.h, ofLog.h, ofSystemUtils.h, ofThread.h,
		//       ofURLFileLoader.h, ofXml.h
	
		///////////////////////////////
		/// \section ofConstants.h
		
		class_<LoopType>("LOOP")
			.enum_("enum") [
				value("NONE", OF_LOOP_NONE),
				value("PALINDROME", OF_LOOP_PALINDROME),
				value("NORMAL", OF_LOOP_NORMAL)
			],
			
		// skipping ofFillFlag, of.getFill() returns a bool
		
		class_<WindowMode>("WINDOWMODE")
			.enum_("mode") [
				value("WINDOW", OF_WINDOW),
				value("FULLSCREEN", OF_FULLSCREEN),
				value("GAME_MODE", OF_GAME_MODE)
			],
			
		class_<AspectRatioMode>("ASPECT")
			.enum_("ratio") [
				value("RATIO_IGNORE", OF_ASPECT_RATIO_IGNORE),
				value("RATIO_KEEP", OF_ASPECT_RATIO_KEEP),
				value("RATIO_KEEP_BY_EXPANDING", OF_ASPECT_RATIO_KEEP_BY_EXPANDING)
			],
			
		// we can mix these here since they aren't *real* enums in lua
		class_<Alignment>("ALIGN")
			.enum_("mode") [
				value("VERT_IGNORE", OF_ALIGN_VERT_IGNORE),
				value("VERT_TOP", OF_ALIGN_VERT_TOP),
				value("VERT_BOTTOM", OF_ALIGN_VERT_BOTTOM),
				value("VERT_CENTER", OF_ALIGN_VERT_CENTER),
				
				value("HORZ_IGNORE", OF_ALIGN_HORZ_IGNORE),
				value("HORZ_LEFT", OF_ALIGN_HORZ_LEFT),
				value("HORZ_RIGHT", OF_ALIGN_HORZ_RIGHT),
				value("HORZ_CENTER", OF_ALIGN_HORZ_CENTER)
			],
			
		class_<RectMode>("RECTMODE")
			.enum_("mode") [
				value("CORNER", OF_RECTMODE_CORNER),
				value("CENTER", OF_RECTMODE_CENTER)
			],
			
		class_<ScaleMode>("SCALEMODE")
			.enum_("mode") [
				value("FIT", OF_SCALEMODE_FIT),
				value("FILL", OF_SCALEMODE_FILL),
				value("CENTER", OF_SCALEMODE_CENTER),
				value("STRETCH_TO_FILL", OF_SCALEMODE_STRETCH_TO_FILL)
			],
			
		// we can mix these here since they aren't *real* enums in lua
		class_<ImageEnum>("IMAGE")
			.enum_("enum") [
				value("GRAYSCALE", OF_IMAGE_GRAYSCALE),
				value("COLOR", OF_IMAGE_COLOR),
				value("COLOR_ALPHA", OF_IMAGE_COLOR_ALPHA),
				value("UNDEFINED", OF_IMAGE_UNDEFINED),
			
				// from ofImage.h
				value("QUALITY_BEST", OF_IMAGE_QUALITY_BEST),
				value("QUALITY_HIGH", OF_IMAGE_QUALITY_HIGH),
				value("QUALITY_MEDIUM", OF_IMAGE_QUALITY_MEDIUM),
				value("QUALITY_LOW", OF_IMAGE_QUALITY_LOW),
				value("QUALITY_WORST", OF_IMAGE_QUALITY_WORST)
			],
			
		class_<PixelFormat>("PIXELS")
			.enum_("format") [
				value("MONO", OF_PIXELS_MONO),
				value("RGB", OF_PIXELS_RGB),
				value("RGBA", OF_PIXELS_RGBA),
				value("BGRA", OF_PIXELS_BGRA),
				value("RGB565", OF_PIXELS_RGB565),
				value("UNKNOWN", OF_PIXELS_UNKNOWN)
			],
			
		class_<BlendMode>("BLENDMODE")
			.enum_("mode") [
				value("DISABLED", OF_BLENDMODE_DISABLED),
				value("ALPHA", OF_BLENDMODE_ALPHA),
				value("ADD", OF_BLENDMODE_ADD),
				value("SUBTRACT", OF_BLENDMODE_SUBTRACT),
				value("MULTIPLY", OF_BLENDMODE_MULTIPLY),
				value("SCREEN", OF_BLENDMODE_SCREEN)
			],
			
		class_<Orientation>("ORIENTATION")
			.enum_("type") [
				value("DEFAULT", OF_ORIENTATION_DEFAULT),
				value("180", OF_ORIENTATION_180),
				value("90_LEFT", OF_ORIENTATION_90_LEFT),
				value("90_RIGHT", OF_ORIENTATION_90_RIGHT),
				value("UNKNOWN", OF_ORIENTATION_UNKNOWN)
			],
			
		class_<GradientMode>("GRADIENT")
			.enum_("mode") [
				value("LINEAR", OF_GRADIENT_LINEAR),
				value("CIRCULAR", OF_GRADIENT_CIRCULAR),
				value("BAR", OF_GRADIENT_BAR)
			],
			
		class_<PolyWindingMode>("POLY")
			.enum_("mode") [
				value("WINDING_ODD", OF_POLY_WINDING_ODD),
				value("WINDING_NONZERO", OF_POLY_WINDING_NONZERO),
				value("WINDING_POSITIVE", OF_POLY_WINDING_POSITIVE),
				value("WINDING_NEGATIVE", OF_POLY_WINDING_NEGATIVE),
				value("WINDING_ABS_GEQ_TWO", OF_POLY_WINDING_ABS_GEQ_TWO)
			],
			
		// this is a hack but gets us the same name order as the OF enums
		class_<HandednessLeft>("LEFT")
			.enum_("type")[value("HANDED", OF_LEFT_HANDED)],
		class_<HandednessRight>("RIGHT")
			.enum_("type")[value("HANDED", OF_RIGHT_HANDED)],
			
		class_<MatrixMode>("MATRIX")
			.enum_("mode") [
				value("MODELVIEW", OF_MATRIX_MODELVIEW),
				value("PROJECTION", OF_MATRIX_PROJECTION),
				value("TEXTURE", OF_MATRIX_TEXTURE)
			],
			
		class_<MouseVars>("MOUSE")
			.enum_("button") [
				value("BUTTON_1", OF_MOUSE_BUTTON_1),
				value("BUTTON_2", OF_MOUSE_BUTTON_2),
				value("BUTTON_3", OF_MOUSE_BUTTON_3),
				value("BUTTON_4", OF_MOUSE_BUTTON_4),
				value("BUTTON_5", OF_MOUSE_BUTTON_5),
				value("BUTTON_6", OF_MOUSE_BUTTON_6),
				value("BUTTON_7", OF_MOUSE_BUTTON_7),
				value("BUTTON_8", OF_MOUSE_BUTTON_8),
				value("BUTTON_LAST", OF_MOUSE_BUTTON_LAST),
				value("BUTTON_LEFT", OF_MOUSE_BUTTON_LEFT),
				value("BUTTON_LAST", OF_MOUSE_BUTTON_LAST),
				value("BUTTON_MIDDLE", OF_MOUSE_BUTTON_MIDDLE),
				value("BUTTON_RIGHT", OF_MOUSE_BUTTON_RIGHT)
			],
		
		class_<KeyboardVars>("KEY")
			.enum_("sym") [
				value("MODIFIER", OF_KEY_MODIFIER),
				value("RETURN", OF_KEY_RETURN),
				value("ESC", OF_KEY_ESC),
				value("TAB", OF_KEY_TAB),
				value("COMMAND", OF_KEY_COMMAND),
				
				value("BACKSPACE", OF_KEY_BACKSPACE),
				value("DEL", OF_KEY_DEL),
			
				value("F1", OF_KEY_F1),
				value("F2", OF_KEY_F2),
				value("F3", OF_KEY_F3),
				value("F4", OF_KEY_F4),
				value("F5", OF_KEY_F5),
				value("F6", OF_KEY_F6),
				value("F7", OF_KEY_F7),
				value("F8", OF_KEY_F8),
				value("F9", OF_KEY_F9),
				value("F10", OF_KEY_F10),
				value("F11", OF_KEY_F11),
				value("F12", OF_KEY_F12),
			
				value("LEFT", OF_KEY_LEFT),
				value("UP", OF_KEY_UP),
				value("RIGHT", OF_KEY_RIGHT),
				value("DOWN", OF_KEY_DOWN),
				
				value("PAGE_UP", OF_KEY_PAGE_UP),
				value("PAGE_DOWN", OF_KEY_PAGE_DOWN),
				value("HOME", OF_KEY_HOME),
				value("END", OF_KEY_END),
				value("INSERT", OF_KEY_INSERT),
				
				value("CONTROL", OF_KEY_CONTROL),
				value("ALT", OF_KEY_ALT),
				value("SHIFT", OF_KEY_SHIFT),
				value("SUPER", OF_KEY_SUPER),
				
				value("LEFT_SHIFT", OF_KEY_LEFT_SHIFT),
				value("RIGHT_SHIFT", OF_KEY_RIGHT_SHIFT),
				value("LEFT_CONTROL", OF_KEY_LEFT_CONTROL),
				value("RIGHT_CONTROL", OF_KEY_RIGHT_CONTROL),
				value("LEFT_ALT", OF_KEY_LEFT_ALT),
				value("RIGHT_ALT", OF_KEY_RIGHT_ALT),
				value("LEFT_SUPER", OF_KEY_LEFT_SUPER),
				value("RIGHT_SUPER", OF_KEY_RIGHT_SUPER),
				value("LEFT_COMMAND", OF_KEY_LEFT_COMMAND),
				value("RIGHT_COMMAND", OF_KEY_RIGHT_COMMAND)
			],
		
		class_<DrawBitmapMode>("BITMAPMODE")
			.enum_("mode") [
				value("SIMPLE", OF_BITMAPMODE_SIMPLE),
				value("SCREEN", OF_BITMAPMODE_SCREEN),
				value("VIEWPORT", OF_BITMAPMODE_VIEWPORT),
				value("MODEL", OF_BITMAPMODE_MODEL),
				value("MODEL_BILLBOARD", OF_BITMAPMODE_MODEL_BILLBOARD)
			],
		
		class_<_TextEncoding>("ENCODING")
			.enum_("type") [
				value("UTF8", OF_ENCODING_UTF8),
				value("ISO_8859_15", OF_ENCODING_ISO_8859_15)
			],
	
		///////////////////////////////
		/// \section ofUtils.h
		
		def("resetElapsedTimeCounter", &ofResetElapsedTimeCounter),
		def("getElapsedTimef", &ofGetElapsedTimef),
		def("getElapsedTimeMillis", &ofGetElapsedTimeMillis),
		def("getElapsedTimeMicros", &ofGetElapsedTimeMicros),
		//def("getFrameNum", &ofGetFrameNum), // this is also in App.h
		
		def("getSeconds", &ofGetSeconds),
		def("getMinutes", &ofGetMinutes),
		def("getHours", &ofGetHours),
		
		def("getUnixTime", &ofGetUnixTime),
		def("getSystemTime", &ofGetSystemTime),
		def("getSystemTimeMicros", &ofGetSystemTimeMicros),
		
		def("getTimestampString", (string(*)(void)) &ofGetTimestampString),
		def("getTimestampString", (string(*)(string)) &ofGetTimestampString),
		
		def("getYear", &ofGetYear),
		def("getMonth", &ofGetMonth),
		def("getDay", &ofGetDay),
		def("getWeekday", &ofGetWeekday),
		
		def("launchBrowser", (void(*)(string)) &ofLaunchBrowser),
		def("launchBrowser", (void(*)(string,bool)) &ofLaunchBrowser),
		
		def("enableDataPath", &ofEnableDataPath),
		def("disableDataPath", &ofDisableDataPath),
		def("toDataPath", (void(*)(string)) &ofToDataPath),
		def("toDataPath", (void(*)(string,bool)) &ofToDataPath),
		
		// ignoring templated vector algorithm wrappers
		
		def("setWorkingDirectoryToDefault", &ofSetWorkingDirectoryToDefault),
		def("setDataPathRoot", &ofSetDataPathRoot),
		
		// ignoring type conversion functions for now
		
		def("getVersionInfo", &ofGetVersionInfo),
		def("getVersionMajor", &ofGetVersionMajor),
		def("getVersionMinor", &ofGetVersionMinor),
		def("getVersionPatch", &ofGetVersionPatch),
		
		def("saveScreen", &ofSaveScreen),
		def("saveFrame", (void(*)(void)) &ofSaveFrame),
		def("saveFrame", (void(*)(bool)) &ofSaveFrame),
		def("saveViewport", &ofSaveViewport),
		
		// ignoring string functions, use lua string lib
		
		// no VAArgs in lua
		
		def("system", &ofSystem)
		
		// ignoring getTargetPlatform for now
	;
}

static string constants =
"PI = 3.14159265358979323846\n" \
"TWO_PI = 6.28318530717958647693\n" \
"FOUR_PI = 12.56637061435917295385\n" \
"HALF_PI = 1.57079632679489661923\n" \
"of.CLOSE = true\n" \
"of.MAX_LIGHTS = 8"
;

// add some special constants
void addUtilsConstants(lua_State *L) {
	luaL_loadstring(L, constants.c_str());
	lua_pcall(L, 0, LUA_MULTRET, 0);
}

} // namespace
