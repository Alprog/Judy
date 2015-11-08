
local base = Model
Class('ModelDerived', base)

function ModelDerived:Update(dt)
	base.Update(self, dt)
	--print(dt)
end