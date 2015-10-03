
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include "Matrix.h"

#define __Meta__

struct __Meta__ Transform
{
    friend class Meta;

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

    bool invalidateMatrix;
    Matrix matrix;
};
