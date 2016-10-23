
Class('ModelDerived', Model)	
local base = Model
local a = 0
local b = nil
function ModelDerived:update(dt)
	base.update(self, dt)		
	
	--print(self:getTransform())
	local a = self:getTransform().translation
	
	a.x = a.x - 0.001
	
	print(a.x)
	
	self:getTransform().translation = a
	
	collectgarbage()
	
	--print(self:getTransform().rotation)

    if InputSystem.getInstance():isPressed(Keys.Key_Q) then
		print('yo')
	end
end