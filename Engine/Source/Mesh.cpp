
#include "Mesh.h"

#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

Mesh* createCubeMesh()
{
    auto mesh = new Mesh();

    mesh->vertices =
    {
        {{-1, -1, 1}, {0.33f, 0.5f}},
        {{1,  -1, 1}, {0.00f, 0.5f}},
        {{1,   1, 1}, {0.00f, 0.0f}},
        {{-1,   1, 1}, {0.33f, 0.0f}},

        {{1, -1,  1}, {0.66f, 0.5f}},
        {{1, -1, -1}, {0.33f, 0.5f}},
        {{1,  1, -1}, {0.33f, 0.0f}},
        {{1,  1,  1}, {0.66f, 0.0f}},

        {{1,  -1, -1}, {0.33f, 1.0f}},
        {{-1, -1, -1}, {0.00f, 1.0f}},
        {{-1,  1, -1}, {0.00f, 0.5f}},
        {{1,   1, -1}, {0.33f, 0.5f}},

        {{-1, -1, -1}, {0.66f, 1.0f}},
        {{-1, -1,  1}, {0.33f, 1.0f}},
        {{-1,  1,  1}, {0.33f, 0.5f}},
        {{-1,  1, -1}, {0.66f, 0.5f}},

        {{-1, -1, -1}, {0.66f, 1.0f}},
        {{1,  -1, -1}, {1.00f, 1.0f}},
        {{1,  -1,  1}, {1.00f, 0.5f}},
        {{-1, -1,  1}, {0.66f, 0.5f}},

        {{-1, 1,  1}, {0.66f, 0.5f}},
        {{1,  1,  1}, {1.00f, 0.5f}},
        {{1,  1, -1}, {1.00f, 0.0f}},
        {{-1, 1, -1}, {0.66f, 0.0f}}
    };

    mesh->vertexBuffer = new VertexBuffer();
    mesh->vertexBuffer->vertices = mesh->vertices;
    mesh->vertexBuffer->Load();

    mesh->indices =
    {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };

    mesh->indexBuffer = new IndexBuffer();
    mesh->indexBuffer->indices = mesh->indices;
    mesh->indexBuffer->Load();

    return mesh;
}

Mesh* createQuadMesh()
{
    auto mesh = new Mesh();

    mesh->vertices =
    {
        {{0, 0, 0}, {0.0f, 0.0f}},
        {{1, 0, 0}, {1.0f, 0.0f}},
        {{0, 1, 0}, {0.0f, 1.0f}},
        {{1, 1, 0}, {1.0f, 1.0f}}
    };

    mesh->vertexBuffer = new VertexBuffer();
    mesh->vertexBuffer->vertices = mesh->vertices;
    mesh->vertexBuffer->Load();

    mesh->indices = {0, 1, 2, 0, 2, 3};

    mesh->indexBuffer = new IndexBuffer();
    mesh->indexBuffer->indices = mesh->indices;
    mesh->indexBuffer->Load();

    return mesh;
}
