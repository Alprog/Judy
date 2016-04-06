
#pragma once

class Shader;
class Texture;

class RenderState
{
public:
    Shader* vertexShader;
    Shader* pixelShader;
    Texture* texture;
};
