
-- create new images
bikers = of.image()
gears = of.image()
tdf = of.image()
tdfSmall = of.image()
transparency = of.image()
bikeIcon = of.image()

----------------------------------------------------
function setup()
	print("script setup")

	of.setWindowTitle("image loader example")	
	of.setFrameRate(30)

	bikers:loadImage("images/bikers.jpg")
	gears:loadImage("images/gears.gif")
	tdf:loadImage("images/tdf_1972_poster.jpg")

	tdfSmall:loadImage("images/tdf_1972_poster.jpg")
	tdfSmall:resize(tdfSmall.width / 4, tdfSmall.height / 4)
	tdfSmall:setImageType(of.image.GRAYSCALE)

	transparency:loadImage("images/transparency.png")
	bikeIcon:loadImage("images/bike_icon.png")
	bikeIcon:setImageType(of.image.GRAYSCALE)
end

----------------------------------------------------
function update()
	of.background(255)
end

----------------------------------------------------
function draw()
	of.setColor(255)

	bikers:draw(0, 0)
	gears:draw(600, 0)
	tdf:draw(600, 300)

	of.setColor(220, 50, 50)
	tdfSmall:draw(200, 300)
	
	of.setColor(255)
	of.enableAlphaBlending()
	local wave = math.sin(of.getElapsedTime())
	transparency:draw(500 + (wave * 100), 20)
	of.disableAlphaBlending()

	-- getting the ofColors from an image,
	-- using the brightness to draw circles
	local w = bikeIcon:getWidth()
	local h = bikeIcon:getHeight()
	local diameter = 10
	of.setColor(255, 0, 0)
	for y=1,h-1 do
		for x=1,w-1 do
			local cur = bikeIcon:getColor(x, y)
			local size = 1 - (cur:getBrightness() / 255)
			of.circle(x * diameter, 500 + y * diameter,
					  1 + size * diameter / 2)
		end
	end

	-- same as above, but this time
	-- use the raw data directly with getPixels()
	local pixels = bikeIcon:getPixels()
	of.setColor(0, 0, 255)
	for y=1,h-1 do
		for x=1,w-1 do
			local index = y * w + x
			cur = pixels:getPixel(index)
			size = 1 - (cur / 255)
			of.circle(200 + x * diameter, 500 + y * diameter,
					  1 + size * diameter / 2)		
		end
	end

	of.setColor(255)
	bikeIcon:draw(190, 490, 20, 20)
end

----------------------------------------------------
function exit()
	print("script finished")
end

