
Class('ModelDerived', Model)	
local base = Modellocal a = 0local b = nil
function ModelDerived:update(dt)
	base.update(self, dt)		
    if InputSystem.getInstance():onPressed(Keys.Key_Q) then		print('yo')
	end
end