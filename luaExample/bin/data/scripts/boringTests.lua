--[[
  nothing exciting here, just a bunch of stuff to see if the interpreter chokes
  on any of the following lines (aka something isn't wrapped correctly, etc)
]] 

-- test that require is working
require "lib/test"

----------------------------------------------------
function setup()
  print("script setup")

  of.setLogLevel(of.LOG_VERBOSE);
  of.log(of.LOG_VERBOSE, "blah blah blah "..tostring(123.4))

  of.setWindowTitle("function test")

  local testString = "/hello/this/is/a/fake/path"
  print("test: "..testString)

  -- splitString returns a wrapped C++ std::vector<string>
  local testSplitStrings = of.splitString(testString, "/")
  print("test split: "..tostring(testSplitStrings:size()))
  for i = 0, testSplitStrings:size()-1 do
    print("\t"..testSplitStrings[i])
  end

  local testJoinStrings = of.joinString(testSplitStrings, "/")
  print("test join: "..testJoinStrings)

  --mutex = of.Mutex()
  --lock = of.ScopedLock()
  style = of.Style()

  rect = of.Rectangle()
  m3x3 = of.Matrix3x3()
  m4x4 = of.Matrix4x4()
  quat = of.Quaternion()

  v2f = of.Vec2f()
  v3f = of.Vec3f()
  v4f = of.Vec4f()

  c = of.Color()
  c:set(127.0, 127.0, 255.0)
  print("c: "..c:getR().." "..tostring(c.g).." " ..tostring(c.b).." "..tostring(c.a))
  print(tostring(c))

  pixels = of.Pixels()
  pixels:clear()

  path = of.Path()
  path:clear()

  polyline = of.Polyline()
  polyline:clear()

  of.TrueTypeFont.setGlobalDpi(96)
  font = of.TrueTypeFont()
  font:load("fonts/verdana.ttf", 16)
  print("font isLoaded: "..tostring(font:isLoaded()))
  print("font lineHeight: "..font:getLineHeight())

  player = of.SoundPlayer()
  stream = of.SoundStream()

  node = of.Node()
  mesh = of.Mesh()

  light = of.Light()
  material = of.Material()
  fbo = of.Fbo()
  print("fbo allocated: "..tostring(fbo:isAllocated()))
  vbo = of.Vbo()
  vboMesh = of.VboMesh()
  shader = of.Shader()

  txtData = of.TextureData()
  txt = of.Texture()
  txt:clear()
  print("texture allocated: "..tostring(txt:isAllocated()))

  if not of.Image then
    print "of.Image function doesn't exist"
  end
  img = of.Image()

  -- GL type defines added by the swig interface (don't exist in OF)
  print("of.CLAMP_TO_EDGE: "..string.format("0x%X", of.CLAMP_TO_EDGE))
  print("of.CLAMP_TO_BORDER: "..string.format("0x%X", of.CLAMP_TO_BORDER))
  print("of.REPEAT: "..string.format("0x%X", of.REPEAT))
  print("of.MIRRORED_REPEAT: "..string.format("0x%X", of.MIRRORED_REPEAT))
  print("of.TEXTURE_LUMINANCE: "..string.format("0x%X", of.TEXTURE_LUMINANCE))
  print("of.TEXTURE_RGB: "..string.format("0x%X", of.TEXTURE_RGB))
  print("of.TEXTURE_RGBA: "..string.format("0x%X", of.TEXTURE_RGBA))
  print("of.NEAREST: "..string.format("0x%X", of.NEAREST))
  print("of.LINEAR: "..string.format("0x%X", of.LINEAR))

  -- function loaded from separate script via require
  requireTest()

  -- size_t
  local haystack = "ka12ka34ka56ka"
  print("'ka' is found "..of.stringTimesInString(haystack, "ka").." times in '"..haystack.."'")

  -- uint_64t
  print("elapsed millis: "..of.getElapsedTimeMillis())

  -- util stuff
  of.restoreWorkingDirectoryToDefault()

  -- of.Buffer, test binary data in strings
  buffer = of.Buffer("hello\0world")
  print("buffer size (11): "..buffer:size())
  buffer:clear()
  print("buffer size (0): "..buffer:size())
  buffer:set("abc\0de")
  print("buffer size (6): "..buffer:size())
  buffer:append("fg\0hij")
  print("buffer size (12): "..buffer:size())
  local data = buffer:getData()
  if data then
    io.write("buffer data (hex): ")
    for i = 1,#data do
      io.write(string.format("%.2X ", string.byte(data:sub(i,i))))
    end
    io.write("\n")
  end
  buffer:set("foo bar")
  print("buffer size (7): "..buffer:size())
  print("buffer text: "..buffer:getText())

  -- of.FilePath
  print("filepath current dir: "..of.FilePath.getCurrentWorkingDirectory())
  print("filepath joining /Users/foo with bar.txt: "..of.FilePath.join("/Users/foo", "bar.txt"))

  -- of.File
  file = of.File("scripts/boringTests.lua")

  print("file path: "..file:path())
  print("file extension: "..file:getExtension())
  print("file name: "..file:getFileName())
  print("file basename: "..file:getBaseName())
  print("file enclosing directory: "..file:getEnclosingDirectory())
  print("file absolute path: "..file:getAbsolutePath())

  print("file can read?: "..tostring(file:canRead()))
  print("file can write?: "..tostring(file:canWrite()))
  print("file can execute?: "..tostring(file:canExecute()))

  print("file is file?: "..tostring(file:isFile()))
  print("file is link?: "..tostring(file:isLink()))
  print("file is directory?: "..tostring(file:isDirectory()))
  print("file is device?: "..tostring(file:isDevice()))
  print("file is hidden?: "..tostring(file:isHidden()))

  print("file size: "..file:getSize())

  -- of.Directory
  dir = of.Directory("./")
  print("dir absolute path: "..dir:getAbsolutePath())

end

function update()
end

function draw()
  of.drawBitmapString("boring tests", 20, 20)
end
