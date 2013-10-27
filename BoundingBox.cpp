#pragma once

#include "BoundingBox.h"

Vector3D BoundingBox::GetCenter()
{
	return Vector3D((max+min)/2.0f);
}

Vector3D BoundingBox::GetSize()
{
	return (max-min);
}

