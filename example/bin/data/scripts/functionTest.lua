
----------------------------------------------------
function setup()

	of.setWindowTitle("function test")

	local testString = "/hello/this/is/a/fake/path"
	print("test: "..testString)

	local testSplitStrings = of.splitString(testString, "/")
	--testSplitStrings.size()
	print("test split: "..tostring(testSplitStrings:size()))
	for i=0,#testSplitStrings do
		print(testSplitStrings[i])
	end
	print('/n')

	local testJoinStrings = of.joinString(testSplitStrings, "/")
	print("test join: "..testJoinStrings)

end