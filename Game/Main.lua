
require 'Class'
require 'ModelDerived'
--require 'Serializer'
require 'Keys'

print(3)

local app = App.getInstance()
local window = Window.create()
local scene = window.scene

local n = Node.new0()

function f()	
	local t = n:getTransform()
	t.custom = "feg"
	print(t.custom)
	
end

f()
collectgarbage()
print(n:getTransform().custom)

app.window = window

local inputSystem = InputSystem.getInstance()

function add()
	local model = ModelDerived.new()
	print(model)
	--model.foo = 'abr'
	print(model.foo)
	scene:addChild(model)
end

local virtualDevice = VirtualDevice.new0()
virtualDevice:addKeySource(0, nil, 0)
virtualDevice:addKeySource(0, nil, 1)

local b = virtualDevice:isPressed(0)

add()

collectgarbage()

function remove()
	local model = scene:getChild(2)
	print(model)
	print(model.foo)
	scene:removeChild(model)
end

--remove()

collectgarbage()

print('---')

app:startMainLoop()