#pragma once

#include "BoundingBox.h"
#include <algorithm> 


void BoundingBox::SetBoundingBox(Vector3D pPosition, Vector3D pSize)
{
	mMin = pPosition-(pSize/2.0f);
	mMax = pPosition+pSize/2.0f;
	OriginalMin = mMin;
	OriginalMax = mMax;
}

BoundingBox::BoundingBox(Vector3D pMin, Vector3D pMax)
{
	mMax = pMax;
	mMin = pMin;

	OriginalMin = pMin;
	OriginalMax = pMax;
}

void BoundingBox::Translate(const Vector3D& pTranslate)
{
	mMax = OriginalMax + pTranslate;
	mMin = OriginalMin + pTranslate;
}

BoundingBox::BoundingBox()
{
	mMin.x = 0;
	mMin.y = 0;
	mMin.z = 0;

	mMax.x = 0;
	mMax.y = 0;
	mMax.z = 0;
}

/*void BoundingBox::SetMax(const Vector3D& pValue)
{
	mMax = pValue;
}

void BoundingBox::SetMin(const Vector3D& pValue)
{
	mMin = pValue;
}*/

Vector3D BoundingBox::GetCenter() const
{
	return Vector3D((mMax+mMin)/2.0f);
}

float BoundingBox::GetLength(const float pValue1, const float pValue2) const
{
	if ((pValue1>0) && (pValue2>0))
		return std::max(pValue1, pValue2) - std::min(pValue1, pValue2);
	else if ((pValue1<0) && (pValue2<0))
		return std::max(abs(pValue1), abs(pValue2)) - std::min(abs(pValue1), abs(pValue2));
	else 
		return abs(pValue1) + abs(pValue2);
}

Vector3D BoundingBox::GetSize() const
{
	return (Vector3D(GetLength(mMin.x, mMax.x), GetLength(mMin.y, mMax.y), GetLength(mMin.z, mMax.z)));
}

const Vector3D& BoundingBox::GetMin() const
{
	return mMin;
}

const Vector3D& BoundingBox::GetMax() const
{
	return mMax;
}

void BoundingBox::TranslateBB(const Vector3D& pTranslate)
{
	mMax += pTranslate;
	mMin += pTranslate;
	OriginalMax += pTranslate;
	OriginalMin += pTranslate;
}