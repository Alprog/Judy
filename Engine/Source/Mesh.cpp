
#include "Mesh.h"

Mesh* CreateCubeMesh()
{
    auto mesh = new Mesh();

    mesh->vertices =
    {
        {{0, 0, 0}, {0, 0}},
        {{1, 0, 0}, {1, 0}},
        {{1, 1, 0}, {1, 1}},
        {{0, 1, 0}, {0, 1}}
    };

    mesh->indices =
    {
        0, 1, 2, 0, 2, 3
    };

    return mesh;
}
