
#pragma once

#include <Node.h>
#include <Mesh.h>
#include <RenderState.h>
#include <Path.h>

class [[Meta]] Sprite : public Node
{
public:
    Sprite();

    virtual void render(Matrix matrix, RendererFrontend* renderer) override;

    Mesh* mesh;
    RenderState* renderState;

    Property [[Bind, Inspect]] imagePath;
    Path getImagePath() const;
    void setImagePath(Path);

private:
    [[Ignore]] Path imagePath;
};
