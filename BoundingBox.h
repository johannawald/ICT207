#pragma once

#include "Vector3D.h"

//bounding boxes
class BoundingBox
{
private:
	
public:
	BoundingBox(Vector3D pMin, Vector3D pMax);
	BoundingBox(Vector3D pPosition, float pSize);
	BoundingBox();

	float GetLength(const float pValue1, const float pValue2) const;

	const Vector3D& GetMin() const;
	const Vector3D& GetMax() const;

	//void SetMax(const Vector3D& pValue);
	//void SetMin(const Vector3D& pValue);
	void SetBoundingBox(Vector3D pPosition, Vector3D pSize);

	Vector3D mMax;
    Vector3D mMin;
    Vector3D OriginalMax;
    Vector3D OriginalMin;

	Vector3D GetCenter() const;
	Vector3D GetSize() const;

	void Translate(const Vector3D& pTranslate);
	void TranslateBB(const Vector3D& pTranslate);
};
