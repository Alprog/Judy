
--[[local app = App.Instance()
local window = Window.Create()

local a = Node.new0()
local b = Node.new1(4)
a:AddChild(b)
local count = a:ChildCount()
print(count)]]

require "Data/Math"



function d()
	local a = 3;
	return a;
end

function r()
	local a = 3;
	local e = d()
	print("3")
	return 4
end

r()

local a = sum(3, 3)
print("sum: "..a)

--[[function a()
	while (true) do
		local a = 0;
		for i = 1, 60000 do
			for j = 1, 5 do
				a = a + 1
				a = a - 1
			end
		end
		print("one")
	end
end

function b()
	a()
end]]

--app:StartMainLoop()