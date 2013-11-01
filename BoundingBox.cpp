#pragma once

#include "BoundingBox.h"
#include <algorithm> 


void BoundingBox::SetBoundingBox(const Vector3D& pPosition, const Vector3D& pSize)
{
	mMin = pPosition-(pSize/2.0f);
	mMax = pPosition+pSize/2.0f;
	mOriginalMin = mMin;
	mOriginalMax = mMax;
}

BoundingBox::BoundingBox(const Vector3D& pMin, const Vector3D& pMax)
{
	mMax = pMax;
	mMin = pMin;
	mOriginalMin = pMin;
	mOriginalMax = pMax;
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

const Vector3D& BoundingBox::GetCenter() const
{
	return Vector3D((mMax+mMin)/2.0f);
}

const float BoundingBox::GetLength(const float pValue1, const float pValue2) const
{
	if ((pValue1>0) && (pValue2>0))
		return std::max(pValue1, pValue2) - std::min(pValue1, pValue2);
	else if ((pValue1<0) && (pValue2<0))
		return std::max(abs(pValue1), abs(pValue2)) - std::min(abs(pValue1), abs(pValue2));
	else 
		return abs(pValue1) + abs(pValue2);
}

const Vector3D& BoundingBox::GetSize() const
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

void BoundingBox::Translate(const Vector3D& pTranslate)
{
	mMax = mOriginalMax + pTranslate;
	mMin = mOriginalMin + pTranslate;
}

void BoundingBox::TranslatePosition(const Vector3D& pTranslate)
{
	mMax += pTranslate;
	mMin += pTranslate;
	mOriginalMax += pTranslate;
	mOriginalMin += pTranslate;
}
