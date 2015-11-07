
require 'ModelDerived'
--require 'Serializer'

local app = App.Instance()
local window = WindowM.Create()
local scene = window.scene

function add()
	local model = ModelDerived.new()
	print(model)
	model.foo = 'abr'
	print(model.foo)
	scene:AddChild(model)
end

add()

collectgarbage()

function remove()
	local model = scene:Child(2)
	print(model)
	model.foo = 'abr'
	print(model.foo)
	scene:RemoveChild(model)
end

remove()

collectgarbage()

print('---')

app:StartMainLoop()