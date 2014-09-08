
local app = App:Instance()
local window = Window:Create()

local q = Quad:new()
q.Size.x = 0.3
q.Size.y = 0.3
q.Shader = "Shaders\\Color"
q.Texture = "D:/test.png"

window.scene = q


app:StartMainLoop();