
----------------------------------------------------
function setup()
  print("script setup")

  of.setLogLevel(of.LOG_VERBOSE);
  of.log(of.LOG_VERBOSE, "blah blah blah"..tostring(123.4))

  of.background(50)

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
  font:loadFont("fonts/verdana.ttf", 16)
  print("font isLoaded: "..tostring(font:isLoaded()))
  print("font lineHeight: "..font.lineHeight)

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
  
end

function update()
end

function draw()
end