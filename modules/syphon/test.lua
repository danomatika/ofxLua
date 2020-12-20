require "syphon"

local server = syphon.Server()
local client = syphon.Client()
local mod = 0

function setup()
	of.setWindowTitle("kaa")
	of.setCircleResolution(40)
	
	server:setName("Screen Output")

	client:setup()
	client:set("", "Test Server")
end

function update()
	mod = mod + 0.025
end

function draw()

	-- draw circle
	of.setColor(255)
	of.drawCircle(of.getWidth()/2, of.getHeight()/2, 200 * of.noise(mod))

	-- draw other client's screen
	client:draw(50, 50)

	-- update screen to server
	server:publishScreen()
end

-- try cleaning up
function exit()
	client = nil
	server = nil
end
