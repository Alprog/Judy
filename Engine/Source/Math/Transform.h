
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include "Matrix.h"
#include "Attributes.h"

struct [[Meta]] Transform
{
    friend class Meta;

    Transform();

    Property [[Bind, Inspect]] translation;
    void setTranslation(Vector3 translation);
    Vector3 getTranslation() const;

    Property [[Bind, Inspect]] rotation;
    Quaternion getRotation() const;
    void setRotation(Quaternion quaternion);

    Property [[Bind, Inspect]] scaling;
    Vector3 getScaling() const;
    void setScaling(Vector3 scaling);

    Matrix getMatrix();

private:
    [[Serialize]] Vector3 translation;
    [[Serialize]] Quaternion rotation;
    [[Serialize]] Vector3 scaling;

    bool invalidateMatrix;
    Matrix matrix;
};
