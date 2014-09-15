
local app = App:Instance()
local window = Window:Create()

local q = Quad:new()
q.Size = Vector2(0.5, 0.5);
q.Shader = "Shaders\\Color"
q.Texture = "D:/test.png"

window.scene = q

local v = Vector2()
print(v.x)

local t = 
{
	["@"] = "Quad",
	Size = { 0.3, 0.3 },
	Shader = "Shaders\\Color",
	Texture = "D:/test.png",
	Childs = 
	{
		{
			Class = "Quad",
			Size = { 0.3, 0.3 },
			Shader = "Shaders\\Color",
			Texture = "D:/test.png",
			Childs = {}
		}
	}
}

app:StartMainLoop();