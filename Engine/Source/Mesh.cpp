
#include "Mesh.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

Mesh* CreateCubeMesh()
{
    auto mesh = new Mesh();

    mesh->vertices =
    {
        {{0, 0, 1}, {0, 0}},
        {{1, 0, 1}, {1, 0}},
        {{1, 1, 1}, {1, 1}},
        {{0, 1, 1}, {0, 1}},

        {{1, 0, 1}, {0, 0}},
        {{1, 0, 0}, {1, 0}},
        {{1, 1, 0}, {1, 1}},
        {{1, 1, 1}, {0, 1}},

        {{1, 0, 0}, {0, 0}},
        {{0, 0, 0}, {1, 0}},
        {{0, 1, 0}, {1, 1}},
        {{1, 1, 0}, {0, 1}},

        {{0, 0, 0}, {0, 0}},
        {{0, 0, 1}, {1, 0}},
        {{0, 1, 1}, {1, 1}},
        {{0, 1, 0}, {0, 1}},

        {{0, 0, 0}, {0, 0}},
        {{1, 0, 0}, {1, 0}},
        {{1, 0, 1}, {1, 1}},
        {{0, 0, 1}, {0, 1}},

        {{0, 1, 1}, {0, 0}},
        {{1, 1, 1}, {1, 0}},
        {{1, 1, 0}, {1, 1}},
        {{0, 1, 0}, {0, 1}}
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
