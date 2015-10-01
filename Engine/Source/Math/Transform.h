
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include "Matrix.h"

struct Transform
{
    Transform();

    Vector3 getTranslation() const;
    Quaternion getRotation() const;
    Vector3 getScaling() const;

    void setTranslation(Vector3 translation);
    void setRotation(Quaternion quaternion);
    void setScaling(Vector3 scaling);

    Matrix getMatrix();

private:
    Vector3 translation;
    Quaternion rotation;
    Vector3 scaling;

    void CalcMatrix();

    bool invalidateMatrix;
    Matrix matrix;
};
