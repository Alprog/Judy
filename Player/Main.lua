
local app = App.Instance()
local window = WindowM.Create()

local a = Node.new0()
local b = Node.new1(4)
a:AddChild(b)
local count = a:ChildCount()
print(count)


local a = 3;

function b()
	return 3;
end

b()

print('-------------------')

print(window)
window:Update()

--window.Update(window, 0)

--print(window.scene)

app:StartMainLoop()