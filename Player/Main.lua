
--[[local app = App:Instance()
local window = Window:Create()

local q = Quad:new()
q.Size = Vector2(0.5, 0.5);
q.Shader = "Shaders\\Color"
q.Texture = "D:/test.png"

window.scene = q

local v = Vector2(3, 3)
print(v.x)]]

require "Script"

function Test(table)
	print(TableToString(table))
end

--[[local index = function(udata, key)
	local metatable = getmetatable(udata)
	return metatable['get_'..key](udata)
end

local newindex = function(udata, key, value)
	local metatable = getmetatable(udata)
	metatable['set_'..key](udata, value)
end

SubStruct.__index = index
SubStruct.__newindex = newindex
TestStruct.__index = index
TestStruct.__newindex = newindex

local ss = SubStruct.new()
ss.e = 33

local ts = TestStruct.new(3, 3, 'f', ss)

print(ts)
print(ts.d)
print(ts.d.e)]]

local node = Node.constructor0()

local child = Node.constructor1(42)

print(node:ChildCount())
node:AddChild(child)

print(node:ChildCount())
node:RemoveChild(child)

print(node:ChildCount())

--app:StartMainLoop();