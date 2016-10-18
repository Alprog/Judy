
#include "Transform2D.h"

Transform2D::Transform2D()
    : pivot {Vector3::Zero}
    , translation {Vector3::Zero}
    , rotation {0}
    , scaling {Vector3::One}
{
}

Matrix Transform2D::GetMatrix()
{
    Matrix matrix = Matrix::Translation(-pivot);
    matrix *= Matrix::Scaling(scaling);
    matrix *= Matrix::RotationZ(rotation);
    matrix *= Matrix::Translation(translation);
    matrix *= Matrix::Translation(pivot);
    return matrix;
}
