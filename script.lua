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