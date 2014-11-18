

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
		str = str .. '\r\n' .. tab .. '  '
		if key == i then
			i = i + 1
		else
			str = str .. key .. ' = '
		end
		if type( value ) == 'table' then
			str = str .. TableToString( value, tab .. '  ' )
		elseif type( value ) == 'string' then
			str = str .. '\'' .. value .. '\''
		else
			str = str .. value
		end
	end

	if not first then
		str = str .. '\r\n' .. tab
	end
	str = str .. '}'

	return str
end