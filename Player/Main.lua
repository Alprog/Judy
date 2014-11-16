
--[[local app = App:Instance()
local window = Window:Create()

local q = Quad:new()
q.Size = Vector2(0.5, 0.5);
q.Shader = "Shaders\\Color"
q.Texture = "D:/test.png"

window.scene = q

local v = Vector2(3, 3)
print(v.x)]]

function TableToString( table, tab )
	local i = 1
	local str = ''
	str = str .. '{'
	tab = tab or ''

	local first = true
  
	for k, v in pairs( table ) do
		if first then
			first = false
		else
			str = str .. ','
		end
		str = str .. '\r\n' .. tab .. '  '
		if k == i then
			i = i + 1
		else
			str = str .. k .. ' = '
		end
		if type( v ) == 'table' then
			str = str .. TableToString( v, tab .. '  ' )
		elseif type( v ) == 'string' then
			str = str .. '\'' .. v .. '\''
		else
			str = str .. v
		end
	end
  
	if not first then
		str = str .. '\r\n' .. tab
	end
	str = str .. '}'

	return str
end

function Test(table)
	print(TableToString(table))
end

--[[local index = function(udata, key)
	local metatable = getmetatable(udata)
	return metatable['get_'..key](udata)
end

local newindex = function(udata, key, value)
	local metatable = getmetatable(udata)
	metatable['set_'..key](udata, value)
end

SubStruct.__index = index
SubStruct.__newindex = newindex
TestStruct.__index = index
TestStruct.__newindex = newindex

local ss = SubStruct.new()
ss.e = 33

local ts = TestStruct.new(3, 3, 'f', ss)

print(ts)
print(ts.d)
print(ts.d.e)]]

local node = Node.constructor0()

local child = Node.constructor1(42)

print(node:ChildCount())
node:AddChild(child)

print(node:ChildCount())
node:RemoveChild(child)

print(node:ChildCount())

--app:StartMainLoop();