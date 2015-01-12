-- some variables in a lua script

-- variables
abool = true
afloat = 123.45 -- lua numbers are all floats
astring = "hello world"

-- an array of simple variables using tables
boolTable = { true, true, false }
floatTable = { 1.23, 2.34, 4.56 }
stringTable = { "hello", "some text", "cha cha" }

-- an array of mixed variable types
mixedTable = { true, 1, 2.34, "kaa" }

-- variables within a table
atable = {} -- create an empty table

atable.abool = true
atable.afloat = 1.234
atable.astring = "hello again"

atable.boolTable = { true, true, false }
atable.floatTable = { 1.23, 2.34, 4.56 }
atable.stringTable = { "hello", "some text", "cha cha" }
atable.mixedTable = { true, 1, 2.34, "kaa" }
atable.hashTable = {["one"] = "foo", ["two"] = "bar" }

atable.afunction = function() print("hey") end

-- another table for clearing
anotherTable = {}

anotherTable.b = false
anotherTable.f = 44.4
anotherTable.s = "howdy ho"
anotherTable.t = { 1, 2, 3, 4, 5 }
