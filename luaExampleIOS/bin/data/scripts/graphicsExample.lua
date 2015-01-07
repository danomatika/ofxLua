print("Hello World!")

counter = 0
bSmooth = false

----------------------------------------------------
function setup()
	print("script setup")

	of.setCircleResolution(50)
	of.background(255, 255, 255, 255)
	of.setWindowTitle("graphics example")
	
	of.setFrameRate(60) -- if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps
end

----------------------------------------------------
function update()
	counter = counter + 0.033
end

----------------------------------------------------
function draw()

	-- CIRCLES
	-- let's draw a circle
	of.setColor(255, 130, 0)
	local radius = 50 + 10 * math.sin(counter)
	of.fill()
	of.circle(100, 400, radius)
	
	-- now just an outline
	of.noFill()
	of.setHexColor(0xCCCCCC)
	of.circle(100, 400, 80)

	-- label
	of.setHexColor(0x000000)
	of.drawBitmapString("circle", 75, 500)

	-- RECTANGLES
	of.fill()
	for i=0,200 do
		of.setColor(of.random(0, 255), of.random(0, 255),
					of.random(0, 255))
		of.rect(of.random(250, 350), of.random(350, 450),
				of.random(10, 20), of.random(10, 20))
	end
	of.setHexColor(0x000000)
	of.drawBitmapString("rectangles", 275, 500)

	-- TRANSPARENCY
	of.setHexColor(0x00FF33)
	of.rect(400, 350, 100, 100)
	-- alpha is usually turned off - for speed puposes.  let's turn it on!
	of.enableAlphaBlending()
	of.setColor(255, 0, 0, 127)   -- red, 50% transparent
	of.rect(450, 430, 100, 33)
	of.setColor(255, 0, 0, math.fmod(counter*10, 255))	-- red, variable transparent
	of.rect(450, 370, 100, 33)
	of.disableAlphaBlending()

	of.setHexColor(0x000000)
	of.drawBitmapString("transparency", 410, 500)

	-- LINES
	-- a bunch of red lines, make them smooth if the flag is set

	if bSmooth then
		of.enableSmoothing()
	end

	of.setHexColor(0xFF0000)
	for i=0,20 do
		of.line(600, 300 + (i*5), 800, 250 + (i*10))
	end

	if bSmooth then
		of.disableSmoothing()
	end

	of.setHexColor(0x000000)
	of.drawBitmapString("lines\npress 's' to toggle smoothness", 600, 500)
	
end

----------------------------------------------------
function exit()
	print("script finished")
end

-- input callbacks

----------------------------------------------------
function keyPressed(key)
	print("script keyPressed \""..tostring(key).."\"")
	if key == string.byte("s") then
		bSmooth = not bSmooth
	end
end

