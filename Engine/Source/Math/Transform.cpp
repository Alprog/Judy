
#include "Transform.h"

Transform::Transform()
    : invalidateMatrix{true}
    , translation{Vector3::Zero}
    , rotation{Quaternion::Identity}
    , scaling{Vector3::One}
{
}

Vector3 Transform::getTranslation() const
{
    return translation;
}

Quaternion Transform::getRotation() const
{
    return rotation;
}

Vector3 Transform::getScaling() const
{
    return scaling;
}

void Transform::setTranslation(Vector3 translation)
{
    this->translation = translation;
    invalidateMatrix = true;
}

void Transform::setRotation(Quaternion rotation)
{
    this->rotation = rotation;
    invalidateMatrix = true;
}

void Transform::setScaling(Vector3 scaling)
{
    this->scaling = scaling;
    invalidateMatrix = true;
}

Matrix Transform::getMatrix()
{
    //if (invalidateMatrix)
    {
        matrix = Matrix::TRS(translation, rotation, scaling);
        invalidateMatrix = false;
    }
    return matrix;
}
