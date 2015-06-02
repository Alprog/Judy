
function TableToString( object, tab, replaceTable )
	local i = 1
	local str = ''
	str = str .. '{'
	tab = tab or ''
	replaceTable = replaceTable or {}
	
	local keys, values = {}, {}
	for k, v in pairs(object) do
		local pos = k == '@' and 1 or #keys + 1
		table.insert(keys, pos, k)
		table.insert(values, pos, v)
	end
	
	local first = true
	for j = 1, #keys do
		local key = keys[j]
		local value = values[j]
	
		if first then
			first = false
		else
			str = str .. ','
		end
	    if #keys > 1 then
			str = str .. '\r\n' .. tab .. '    '
		end
		if key == i then
			i = i + 1
		else
			str = str .. key .. ' = '
		end
		if type( value ) == 'table' then
			if replaceTable[value] then
				str = str .. replaceTable[value]
			else
				str = str .. TableToString( value, #keys > 1 and tab .. '    ' or tab )
			end
		elseif type( value ) == 'string' then
			str = str .. '\'' .. value .. '\''
		else
			str = str .. value
		end
	end

	if not first and #keys > 1 then
		str = str .. '\r\n' .. tab
	end
	str = str .. '}'

	return str
end

function RefCounting(objectTable, refsTable, orderTable)
	refsTable[objectTable] = (refsTable[objectTable] or 0) + 1
	if refsTable[objectTable] == 1 then
		table.insert(orderTable, objectTable)
	end
	for _, value in pairs(objectTable) do
		if type(value) == 'table' then
			RefCounting(value, refsTable, orderTable)
		end
	end
end

function SmartTableToString(objectTable)

	local refsTable = {}
	local orderTable = {}
	RefCounting(objectTable, refsTable, orderTable)
	
	local str = ''
	local index = 0
	local replaceTable = {}
	for i = #orderTable, 1, -1 do
		local object = orderTable[i]
		if i == 1 or refsTable[object] > 1 then
			index = index + 1
			local name = 'object' .. index
			str = str .. 'local ' .. name .. ' = \n'
			str = str .. TableToString(object, nil, replaceTable) .. '\n\n'
			replaceTable[object] = name 
		end
	end
	
	return str
end

--[[local d = { "111", "222" }
local e = { "eee", d }

local t = {}
t.a = "fef"
t.b = e
t.c = e
t.d = d]]

--print(SmartTableToString(t))