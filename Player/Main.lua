
local app = App.Instance()
local window = Window.Create()

local a = Node.new0()
local b = Node.new1(4)
a:AddChild(b)
local count = a:ChildCount()
print(count)

app:StartMainLoop()