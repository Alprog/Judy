
dofile "req.lua"

function myluafunction(x)  
	x = x + 1
	x = x + 2
	return x + cppvar + fun()
end

myluafunction(3)