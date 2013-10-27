#pragma once

#include "Vector3D.h"

//bounding boxes
class BoundingBox
{
public:
    Vector3D max;
    Vector3D min;

    Vector3D OriginalMax;
    Vector3D OriginalMin;

	Vector3D GetCenter();
	Vector3D GetSize();
};
