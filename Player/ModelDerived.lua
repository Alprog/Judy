
Class('ModelDerived', Model)	
local base = Model
function ModelDerived:update(dt)
	base.update(self, dt)
end