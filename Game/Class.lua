
function Class(name, base)
	local class = {}
	class.__index = class
	setmetatable(class, base)
	
	class.new = function()
		setForceLuaClass(name)
		return base.new0()
	end
	
	_G[name] = class

	return class, base
end