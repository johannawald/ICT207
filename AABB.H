//  AABH.h
//  Header file for the AABB class
//  Dynamic Array used to store the co-ordinates of the bounding boxes used for collsion 
//  detection.  The array is only used initially before being copied into AABB Linked Lists.
//  The array is then terminated.
//  
//  I created this class originally before using linked lists to store the BB info. But decided
//  to keep it has the stored data can be easily copied across into different linked lists
//  in any prefered order. (i.e. the data is copied into across into linked lists for different
//  quadrants)
//
//  Shay Leary, March 2005
// Johanna Wald: improved code functionallity 
//--------------------------------------------------------------------------------------

#ifndef AABB_H
#define AABB_H

#include <iostream>
#include <math.h>
#include <gl/glut.h>

//--------------------------------------------------------------------------------------

//everyone, functions should not be declared in the .h file -> change that to the .cpp?

class AABB
{
private:
	// stores x,y,z co-ordinates
	struct XYZ 
	{ 
		GLdouble x, y, z; 
	}; 
	// stores max and min values of co-ordinates
	struct BoundingBox 
	{ 
		XYZ max; 
		XYZ min; 
	}; 
	// dynamic array to store info
	BoundingBox *mBBox;
	// number of BB created (i.e. array size)
	int mNoOfBoxes;
	// count of data stored in the array
	int mCount;
public:
	AABB(int count);
	~AABB();
	//----------------------------------------------------------------------------------
	//  Set Method
	//----------------------------------------------------------------------------------
	void SetBBox(const int tempIndex,  //everyone, we don't need SetBBox if we use AddBox to the end of the list, work for later
				const GLdouble MinX, const GLdouble MaxX, 
				const GLdouble MinY, const GLdouble MaxY, 
				const GLdouble MinZ, const GLdouble MaxZ);

	void SetBBox(const int tempIndex, 
				const GLdouble MinX, const GLdouble MaxX, 
				const GLdouble MinZ, const GLdouble MaxZ);

	void AddBBox(const GLdouble MinX, const GLdouble MaxX, 
				const GLdouble MinY, const GLdouble MaxY, 
				const GLdouble MinZ, const GLdouble MaxZ);
	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	GLdouble GetMaxX (const int &tempIndex) {return mBBox[tempIndex].max.x;}
	GLdouble GetMinX (const int &tempIndex) {return mBBox[tempIndex].min.x;}
	GLdouble GetMaxY (const int &tempIndex) {return mBBox[tempIndex].max.y;}
	GLdouble GetMinY (const int &tempIndex) {return mBBox[tempIndex].min.y;}
	GLdouble GetMaxZ (const int &tempIndex) {return mBBox[tempIndex].max.z;}
	GLdouble GetMinZ (const int &tempIndex) {return mBBox[tempIndex].min.z;}
	int GetNoBoundingBoxes() {return mNoOfBoxes;}
};

#endif
