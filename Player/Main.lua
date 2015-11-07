
require 'ModelDerived'
--require 'Serializer'

local app = App.Instance()

local window = WindowM.Create()

--[[local mt = {}
mt.__call = function(t, ...)
	local count = ... and #... or 0
	return t["new"..count]()
end
setmetatable(Node, mt)]]

local scene = window.scene
print(scene:ChildCount())

local model = ModelDerived.new()
scene:AddChild(model)

--model.foo = 'abr'
--print(model.foo)


--local c = scene:Child(2)
--print(c)

--print(scene:Child(2).foo)

print(scene:ChildCount())

scene:RemoveChild(model)
--scene:AddChild(model)

print(scene:ChildCount())

app:StartMainLoop()