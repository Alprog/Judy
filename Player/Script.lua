
function TableToString( object, tab )
	local i = 1
	local str = ''
	str = str .. '{'
	tab = tab or ''
	
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
			str = str .. TableToString( value, #keys > 1 and tab .. '    ' or tab )
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

function RefCounting(objectTable, refsTable)
	refsTable[objectTable] = (refsTable[objectTable] or 0) + 1
	for _, value in pairs(objectTable) do
		if type(value) == 'table' then
			RefCounting(value, refsTable)
		end
	end
end

function SmartTableToString(objectTable)

	local refsTable = {}
	RefCounting(objectTable, refsTable)
	
	for k, v in pairs(refsTable) do
		print(k)
		print(v)
	end
	
end

local e = { "eee", "fff" }

local t = {}
t.a = "fef"
t.b = e
t.c = e

print(SmartTableToString(t))