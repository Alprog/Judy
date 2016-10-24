
Class('ModelDerived', Model)	
local base = Model

local yaw, pitch, roll = 0, 0, 0

function ModelDerived:update(dt)
	base.update(self, dt)		
	
	local inputSystem = InputSystem.getInstance()
	local speed = 0.3
	if inputSystem:isPressed(Keys.Key_L_Shift) then
		speed = 1.0
	end
	local shift = speed * dt

	local pos = self:getTransform().translation
    if inputSystem:isPressed(Keys.Key_A) then pos.x = pos.x - shift end		
    if inputSystem:isPressed(Keys.Key_D) then pos.x = pos.x + shift end
    if inputSystem:isPressed(Keys.Key_W) then pos.y = pos.y + shift end		
    if inputSystem:isPressed(Keys.Key_S) then pos.y = pos.y - shift end
    if inputSystem:isPressed(Keys.Key_Tab) then pos.z = pos.z + shift end		
    if inputSystem:isPressed(Keys.Key_CapsLock) then pos.z = pos.z - shift end
	self:getTransform().translation = pos

	if inputSystem:isPressed(Keys.Key_Left) then yaw = yaw - shift end
	if inputSystem:isPressed(Keys.Key_Right) then yaw = yaw + shift end	if inputSystem:isPressed(Keys.Key_Down) then pitch = pitch - shift end
	if inputSystem:isPressed(Keys.Key_Up) then pitch = pitch + shift end
	if inputSystem:isPressed(Keys.Key_Q) then roll = roll - shift end
	if inputSystem:isPressed(Keys.Key_E) then roll = roll + shift end
	
	if inputSystem:onPressed(Keys.Key_F1) then
		self:switchRenderType()
	end

	self:getTransform().rotation = Quaternion.yawPitchRoll(yaw, pitch, roll)
end

function ModelDerived:switchRenderType()
	local app = App.getInstance()
	app.window:switchRenderType()
end
