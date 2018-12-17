
require 'Class'
require 'ModelDerived'
--require 'Serializer'
require 'Enums'

print('a1')

local app = App.getInstance()

local window = Window.create()
local renderManager = RenderManager.getInstance()
renderManager:addRenderer(RendererType.GL)
local renderer = renderManager:getRenderer(RendererType.GL)
window:setRenderer(renderer)

print('a2')

local scene = window.scene
mainWindow = window

print('a3')

function add()
        print('b1')
	local model = ModelDerived.new0()
	print('b2')
	local scaling = model:getTransform().scaling
	scaling.x = 0.5
	scaling.y = 0.5
	scaling.z = 0.5
	model:getTransform().scaling = scaling
	print(model)
	--model.foo = 'abr'
	print(model.foo)
	scene:addChild(model)
	print('b3')
end

print('a4')

local virtualDevice = VirtualDevice.new0()
virtualDevice:addKeySource(0, nil, 0)
virtualDevice:addKeySource(0, nil, 1)

local b = virtualDevice:isPressed(0)

add()

print('a5')

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
