
local base = Model

ModelDerived = {}
ModelDerived.__index = ModelDerived
setmetatable(ModelDerived, base)

function ModelDerived:new()
	SetForceLuaClass('ModelDerived')
	return Model.new0()
end

function ModelDerived:Update(dt)
	base.Update(self, dt)
	print(dt)
end