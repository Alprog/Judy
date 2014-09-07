
#include "Transform.h"

Matrix Transform::GetMatrix()
{
    Matrix matrix = Matrix::Translation(-Pivot);
    matrix *= Matrix::Scaling(Scaling);
    matrix *= Matrix::RotationZ(Rotation);
    matrix *= Matrix::Translation(Translation);
    matrix *= Matrix::Translation(Pivot);
    return matrix;
}
