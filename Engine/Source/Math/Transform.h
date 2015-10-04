
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include "Matrix.h"

#define __Meta__
#define __Serialize__

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
    __Serialize__ Vector3 translation;
    __Serialize__ Quaternion rotation;
    __Serialize__ Vector3 scaling;

    bool invalidateMatrix;
    Matrix matrix;
};
