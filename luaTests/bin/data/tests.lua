--[[
  nothing exciting here, just a bunch of stuff to see if the interpreter chokes
  on any of the following lines (aka something isn't wrapped correctly, etc)

  TODO: more comprehensive unit tests?
]] 

-- test that require is working
require "lib/test"

local font

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
  for i = 1, testSplitStrings:size()-1 do
    print("\t"..testSplitStrings[i])
  end

  local testJoinStrings = of.joinString(testSplitStrings, "/")
  print("test join: "..testJoinStrings)

  local style = of.Style()

  local rect = of.Rectangle()
  local m3x3 = of.Matrix3x3()
  local m4x4 = of.Matrix4x4()
  local quat = of.Quaternion()

  local v2f = of.Vec2f()
  local v3f = of.Vec3f()
  local v4f = of.Vec4f()

  local c = of.Color()
  c:set(127.0, 127.0, 255.0)
  print("c: "..c:getR().." "..tostring(c.g).." " ..tostring(c.b).." "..tostring(c.a))
  c.r = 255
  c.g = 200
  c.b = 100
  c.a = 50
  print("c: "..c:getR().." "..tostring(c.g).." " ..tostring(c.b).." "..tostring(c.a))
  print(tostring(c))

  local pixels = of.Pixels()
  pixels:clear()

  local path = of.Path()
  path:clear()

  local polyline = of.Polyline()
  polyline:addVertex(1, 1)
  polyline:addVertex(1, 2)
  polyline:addVertex(1, 3)
  print("polyline # "..polyline:size())
  local polyVertices = polyline:getVertices()
  print("polyline vertices "..swig_type(polyVertices))
  --print("polyline # vertices "..polyVertices:size()) -- not working
  polyline:clear()

  of.TrueTypeFont.setGlobalDpi(96)
  font = of.TrueTypeFont()
  font:load("fonts/verdana.ttf", 16, true, true, true)
  print("font isLoaded: "..tostring(font:isLoaded()))
  print("font lineHeight: "..font:getLineHeight())
  local stringPoints = font:getStringAsPoints("hello")
  print("font string points for \"hello\": "..stringPoints:size())
  stringPoints = nil

  local player = of.SoundPlayer()
  local stream = of.SoundStream()

  local node = of.Node()
  local mesh = of.Mesh()
  mesh:addVertex(glm.vec3(1, 2, 3))
  mesh:setMode(of.PRIMITIVE_POINTS)
  local top = glm.vec3(100.0, 50.0, 0.0)
  mesh:addVertex(top)

  local light = of.Light()
  local material = of.Material()
  local fbo = of.Fbo()
  print("fbo allocated: "..tostring(fbo:isAllocated()))
  local vbo = of.Vbo()
  local vboMesh = of.VboMesh()
  local shader = of.Shader()

  local icoSphere = of.IcoSpherePrimitive()
  local icoMesh = icoSphere:getMesh()
  print("icoMesh vertices: "..tostring(icoMesh:getNumVertices()))
  local icoVertices = icoMesh:getVertices()
  print("icoVertices is "..swig_type(icoVertices))
  print("  number of vertices: "..tostring(icoVertices:size()))
  icoMesh:setMode(of.PRIMITIVE_TRIANGLES)
  local icoTriangles = icoMesh:getUniqueFaces()
  print("icoTriangles is "..swig_type(icoTriangles))
  print("  number of triangles: "..tostring(icoTriangles:size()))

  local txtData = of.TextureData()
  local txt = of.Texture()
  txt:clear()
  print("texture allocated: "..tostring(txt:isAllocated()))

  if not of.Image then
    print "of.Image function doesn't exist"
  end
  local img = of.Image()

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
  local buffer = of.Buffer("hello\0world")
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
  local file = of.File("tests.lua")

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
  local dir = of.Directory("./")
  print("dir absolute path: "..dir:getAbsolutePath())

  -- glm vector types
  local point = of.Point(10, 20)
  print("point: "..point.x.." "..point.y)
  point.x = point.x + 10
  point.y = point.y + 10
  print("point+10: "..point.x.." "..point.y)
  print("point len: "..point:length())

  touch = of.TouchEventArgs(of.TouchEventArgs.up, 10, 20, 123)
  print(swig_type(touch))
  print("touch: "..touch.x.." "..touch.y)

  -- glm types
  local pos = glm.vec2(of.getWidth()/2 - 50, of.getHeight()/2 - 50)
  print("pos "..tostring(pos).." is a "..swig_type(pos))
  pos.x = 30
  pos.y = 40
  print("pos x:"..pos.x.." y:"..pos.y)
  print("pos[1]:"..pos[1].." pos[2]:"..pos[2])
  print("glm.pi: "..glm.pi())

  local v1 = glm.vec3(1, 2, 3)
  local v2 = glm.vec3(4, 5, 6)
  print("v1: "..tostring(v1))
  print("v2: "..tostring(v2))
  print("v1 + v2: "..tostring(v1 + v2))
  print("v1 dot v2: "..glm.dot(v1, v2))

  local v3 = glm.vec4(1, 2, 3, 4)
  local m3 = glm.mat3(1, 2, 3, 4, 5, 6, 7, 8, 9)
  local m4 = glm.mat4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
  local q = glm.quat(5, 6, 7, 8)
  print("v3: "..tostring(v3))
  print("m3:\n"..tostring(m3))
  print("m4:\n"..tostring(m4))
  print("quat: "..tostring(q))

  -- glm functions
  print("fma f: "..tostring(glm.fma(1, 2, 3)))
  print("fma v3: "..tostring(glm.fma(v1, v2, glm.vec3(7, 8, 9))))

  -- fbo settings
  local fboSettings = of.FboSettings()
  fboSettings.width = of.getWidth()
  fboSettings.height = of.getHeight()
  fbo:allocate(fboSettings)
  fbo:clear()

  -- math constants
  print("pi: "..of.PI)
  print("two pi: "..of.TWO_PI)
  print("m two pi: "..of.M_TWO_PI)
  print("half pi: "..of.HALF_PI)

  -- old math type compatibility
  local ov2 = of.Vec2f(1, 2)
  local ov3 = of.Vec3f(3, 4, 5)
  local ov4 = of.Vec4f(6, 7, 8, 9)
  local om3 = of.Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)
  local om4 = of.Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
  local oq = of.Quaternion(1, 2, 3, 4)
  print("ofVec2f: "..tostring(ov2))
  print("ofVec3f: "..tostring(ov3))
  print("ofVec4f: "..tostring(ov4))
  print("ofMatrix3x3:\n"..tostring(om3))
  print("ofMatrix4x4:\n"..tostring(om4))
  print("ofQuaternion:\n"..tostring(oq))
  ov2 = ov2:vec2()
  ov3 = ov3:vec3()
  ov4 = ov4:vec4()
  om3 = om3:mat3()
  om4 = om4:mat4()
  oq = oq:quat()
  print("converted vec2: "..tostring(ov2))
  print("converted vec3: "..tostring(ov3))
  print("converted vec4: "..tostring(ov4))
  print("converted mat3:\n"..tostring(om3))
  print("converted mat4:\n"..tostring(om4))
  print("converted quat:\n"..tostring(oq))

  -- ofBoundingBox
  local bb = of.BoundingBox()
  print("bb min: "..tostring(bb.min))
  print("bb max: "..tostring(bb.max))
  local s = of.SpherePrimitive()
  bb = s:getBoundingBox()
  print("sphere bb min: "..tostring(bb.min))
  print("sphere bb max: "..tostring(bb.max))

  -- ofCubeMap
  local cm = of.CubeMap()
  print("cube map: "..tostring(cm))

  -- ofTimeMode
  print("time mode enum")
  print("  system: "..tostring(of.TimeMode_System))
  print("  fixed rate: "..tostring(of.TimeMode_FixedRate))
  print("  filtered: "..tostring(of.TimeMode_Filtered))

  -- ofTime::Mode
  print("time enum")
  print("  system: "..tostring(of.Time_System))
  print("  fixed rate: "..tostring(of.Time_FixedRate))

  of.setLogLevel("ofURLFileLoader", of.LOG_VERBOSE)

  -- http get
  -- check with: curl -X GET "http://httpbin.org/get
  local http = of.URLFileLoader()
  local res = http:get("http://httpbin.org/get")
  print("http get: "..res.status.. " "..res.error)
  if res.data ~= "" then
    print(res.data:getText())
  end

  -- http post
  -- check with: curl -X POST -d '{"foo":"bar","baz":123}' "http://httpbin.org/post"
  local req = of.HttpRequest("http://httpbin.org/post", "test1")
  req.body = '{"foo":"bar","baz":123}'
  req.contentType = "application/json"
  req.method = of.HttpRequest_POST
  req.verbose = true
  res = http:handleRequest(req)
  print("http post: "..res.status.. " "..res.error)
  if res.data ~= "" then
    print(res.data:getText())
  end

end

function update()
end

function draw()
  of.drawBitmapString("tests", 20, 20)

  --local red = of.Color.red
  --local gray = of.Color.lightGray
  --print("red: "..tostring(red))

  -- see if the named color class leaks memory...
  of.fill()
  --of.setColor(gray)
  of.drawRectangle(glm.vec2(of.getWidth()/2 - 50, of.getHeight()/2 - 50), 100, 100)
  of.drawRectangle(touch, 20, 20)
  of.drawRectangle(of.Vec2f(100, 100):vec2(), 10, 10)

  -- see if bounding box rect leaks memory...
  --of.setColor(red)
 -- local box = font:getStringBoundingBox("hello world", 0, 0)
  --font:drawString("hello world", of.getWidth()/2 - box.width/2, of.getHeight()/2)
  --print("box before:"..tostring(box))

  -- box = nil
  -- red = nil
  -- gray = nil
  --print("box after :"..tostring(box))
end
