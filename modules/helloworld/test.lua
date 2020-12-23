-- 2020 Dan Wilcox <danomatika@gmail.com>
require "helloworld"

-- say hello
helloworld.greet()

-- create class
local greet = helloworld.BitmapGreet()

-- draw hello
function draw()
	greet:draw(10, 50)
end
