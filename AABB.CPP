//  AABB.cpp
//
//  Implementation file for AABB Class
//  Defines all the methods declared, but not defined, in AABB.h
//
// Shay Leary, March 2005
// johanna, avoid memory leaks
//--------------------------------------------------------------------------------------

#include <iostream>
#include "AABB.h"

AABB::AABB(const int count): mNoOfBoxes(count), mCount(0) {
	mBBox = new BoundingBox[count];
}

AABB::~AABB () {
	delete[] mBBox;
}

void AABB::SetBBox(const int tempIndex, 
				const GLdouble MinX, const GLdouble MaxX, 
				const GLdouble MinY, const GLdouble MaxY, 
				const GLdouble MinZ, const GLdouble MaxZ) 
{
	SetBBox(tempIndex, MinX, MaxX, MinZ, MaxZ);	
	mBBox[tempIndex].min.y = MinY;
	mBBox[tempIndex].max.y = MaxY;
}

void AABB::SetBBox(const int tempIndex, 
				const GLdouble MinX, const GLdouble MaxX, 
				const GLdouble MinZ, const GLdouble MaxZ)
{
	mBBox[tempIndex].min.x = MinX;
	mBBox[tempIndex].max.x = MaxX;
	mBBox[tempIndex].min.z = MinZ;
	mBBox[tempIndex].max.z = MaxZ;	
}

void AABB::AddBBox(const GLdouble MinX, const GLdouble MaxX, 
				const GLdouble MinY, const GLdouble MaxY, 
				const GLdouble MinZ, const GLdouble MaxZ)
{
	if (mCount<mNoOfBoxes) 
	{
		mBBox[mCount].min.x = MinX;
		mBBox[mCount].max.x = MaxX;
		mBBox[mCount].min.y = MinY;
		mBBox[mCount].max.y = MaxY;
		mBBox[mCount].min.z = MinZ;
		mBBox[mCount].max.z = MaxZ;
		mCount++;
	}
}
