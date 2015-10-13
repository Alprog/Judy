
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include "Matrix.h"
#include "Attributes.h"

struct _(Meta)__ Transform
{
    friend class Meta;

    Transform();

    Property _(Bind, Inspect)__ translation;
    void setTranslation(Vector3 translation);
    Vector3 getTranslation() const;

    Property _(Bind, Inspect)__ rotation;
    Quaternion getRotation() const;
    void setRotation(Quaternion quaternion);

    Property _(Bind, Inspect)__ scaling;
    Vector3 getScaling() const;
    void setScaling(Vector3 scaling);

    Matrix getMatrix();

private:
    _(Serialize, Inspect)__ Vector3 translation;
    _(Serialize, Inspect)__ Quaternion rotation;
    _(Serialize, Inspect)__ Vector3 scaling;

    bool invalidateMatrix;
    Matrix matrix;
};
