
----------------------------------------------------
function setup()
  print("script setup")

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
  --print("c: "..c.R.." "..c.G.." " ..c.B.." "..c.A)
  print(tostring(c))

  pixels = of.Pixels()
  pixels:clear()

  path = of.Path()
  path:clear()

  polyline = of.Polyline()
  polyline:clear()

  of.Font.setGlobalDpi(96)
  font = of.Font()
  print("font isLoaded: "..tostring(font:isLoaded()))

  player = of.SoundPlayer()
  stream = of.SoundStream()

  node = of.Node()
  mesh = of.Mesh()

  light = of.Light()
  material = of.Material()
  fbo = of.Fbo()
  vbo = of.Vbo()
  vboMesh = of.VboMesh()
  shader = of.Shader()

  txtData = of.TextureData()
  txt = of.Texture()

  if not of.Image then
    print "of.Image function doesn't exist"
  end
  img = of.Image()
  
end