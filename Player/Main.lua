
require 'Serializer'

local app = App.Instance()
local window = WindowM.Create()

local a = Node.new0()
local b = Node.new1(4)
a:AddChild(b)
local count = a:ChildCount()
print(count)

--[[Node.__newindex = function(table, key, value)
	
end]]

print(window.scene)

window.scene = a

a.foo = 3
print(a.foo)
print(b.foo)

print(getmetatable(a).foo)
print(getmetatable(b).foo)

--print(getmetatable(getmetatable(a)).foo)
--print(getmetatable(getmetatable(b)).foo)

--[[local t = {}
local m = {}

setmetatable(t, m)
m.__index = m
m.foo = 100
--m.__newindex = m

print(t.foo)
t.foo = 200
print(t.foo)
t.foo = nil
print(t.foo)]]

--[[local a = 3;

function b()
	return 3;
end

b()]]

--[[print('-------------------')

print(window)
window:Update()]]

--window.Update(window, 0)

--print(window.scene)

app:StartMainLoop()