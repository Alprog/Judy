
require 'Class'
require 'ModelDerived'
--require 'Serializer'
require 'Enums'

print(3)

local app = App.getInstance()

local window = Window.create()
local renderManager = RenderManager.getInstance()
renderManager:addRenderer(RendererType.DX)
local renderer = renderManager:getRenderer(RendererType.DX)
window:setRenderer(renderer)

local scene = window.scene
mainWindow = window

local inputSystem = InputSystem.getInstance()

function add()
	local model = ModelDerived.new()
	local scaling = model:getTransform().scaling
	scaling.x = 0.5
	scaling.y = 0.5
	scaling.z = 0.5
	model:getTransform().scaling = scaling
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