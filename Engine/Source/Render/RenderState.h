
#pragma once

class Shader;
class Texture;
class ConstantBuffer;
class PipelineState;

#include <PipelineSettings.h>
#include "GL/gl.h"

class RenderState
{
public:
    RenderState();

    void setVertexShader(Shader* shader);
    void setPixelShader(Shader* shader);

    Texture* texture;
    ConstantBuffer* constantBuffer;

    void link();

    GLuint programId;

    PipelineState* getPipelineState();

private:
    PipelineSettings pipelineSettings;
    PipelineState* pipelineState;
};
