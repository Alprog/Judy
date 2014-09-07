
#include "Transform.h"

Transform::Transform()
    : Pivot {Vector3::Zero}
    , Translation {Vector3::Zero}
    , Rotation {0}
    , Scaling {Vector3::One}
{
}

Matrix Transform::GetMatrix()
{
    Matrix matrix = Matrix::Translation(-Pivot);
    matrix *= Matrix::Scaling(Scaling);
    matrix *= Matrix::RotationZ(Rotation);
    matrix *= Matrix::Translation(Translation);
    matrix *= Matrix::Translation(Pivot);
    return matrix;
}
