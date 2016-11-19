

math.randomseed(3)

local a = math.random(1, 100)
local b = math.random(1, 100)
local c = math.random(1, 100)

print(a, b, c)

math.randomseed(2)

a = math.random(1, 100)
b = math.random(1, 100)
c = math.random(1, 100)

print(a, b, c)

math.randomseed(3)

a = math.random(1, 100)
b = math.random(1, 100)
c = math.random(1, 100)

print(a, b, c)

math.randomseed(2)

a = math.random(1, 100)
b = math.random(1, 100)
c = math.random(1, 100)

print(a, b, c)

require 'Class'
require 'ModelDerived'
--require 'Serializer'
require 'Keys'

print(3)

local app = App.getInstance()
local window = Window.create()
local scene = window.scene

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