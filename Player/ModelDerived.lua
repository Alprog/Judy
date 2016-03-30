
Class('ModelDerived', Model)	

local base = Model

function ModelDerived:Update(dt)
	base.Update(self, dt)
end