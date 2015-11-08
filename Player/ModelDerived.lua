
ModelDerived = {}
ModelDerived.__index = ModelDerived
setmetatable(ModelDerived, Model)

function ModelDerived:new()
	SetForceLuaClass('ModelDerived')
	return Model.new0()
end

function ModelDerived:Update(dt)
	print(dt)
end