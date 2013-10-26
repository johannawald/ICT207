#pragma once

#include "Vector3D.h"

//bounding boxes
struct BoundingBox
{
    Vector3D max;
    Vector3D min;

    Vector3D OriginalMax;
    Vector3D OriginalMin;
};
