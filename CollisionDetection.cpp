#include "CollisionDetection.h"
#include <iostream>
#include <cstdlib>
#include "DrawManager.h"
#include "Vector3D.h"

bool CollisionDetection::CollisionX(int pIndex, GLfloat x)
{
	return ((x <= static_box[pIndex]->max.x) && (x>= static_box[pIndex]->min.x));
}

bool CollisionDetection::CollisionY(int pIndex, GLfloat y)
{
	return  ((y <= static_box[pIndex]->max.y) && (y>= static_box[pIndex]->min.y));
}

bool CollisionDetection::CollisionZ(int pIndex, GLfloat z)
{
	return ((z <= static_box[pIndex]->max.z) && (z>= static_box[pIndex]->min.z));
}

bool CollisionDetection::Collision(const Vector3D& pPoint, int &pIndex, const GLfloat pSize)
{
	bool collisionResult = false;
	bool collision = false;
	for (unsigned int i = 0; i<static_box.size(); i++) 
	{
		collision = Collision(static_box[i], pPoint, pSize, true);
		if (collision)
			pIndex=i;
		collisionResult = collisionResult || collision;
	}
	return collisionResult;
}

bool CollisionDetection::Collision(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2)
{
	Vector3D vDistance = pBoundingBox1->GetCenter() - pBoundingBox2->GetCenter();
	Vector3D vMaxDistance = pBoundingBox1->GetSize() + pBoundingBox2->GetSize();
	return (abs(vDistance.x) <= vMaxDistance.x && abs(vDistance.y) <= vMaxDistance.y && abs(vDistance.z) <= vMaxDistance.z);
}

bool CollisionDetection::Collision(BoundingBox *b, const Vector3D& pPoint, const GLfloat size, bool pShowPosition)
{
	if (pShowPosition)
	{
		if (pPoint!=mVold) 
			std::cout << "x: " << pPoint.x << " y: " << pPoint.y << " z: " << pPoint.z << std::endl;
		mVold = pPoint;
	}

	//not only one point a cube! 

	Vector3D Center = pPoint - b->max - b->OriginalMax;
	/*GLfloat xCenter = (pPoint.x - (b->max.x-b->OriginalMax.x));
	GLfloat yCenter = (pPoint.y - (b->max.y-b->OriginalMax.y));
	GLfloat zCenter = (pPoint.z - (b->max.z-b->OriginalMax.z));*/

	GLfloat x[8];
	GLfloat y[8];
	GLfloat z[8];

	x[0] = Center.x + size/2.0f;
	y[0] = Center.y + size/2.0f;
	z[0] = Center.z + size/2.0f;

	x[1] = Center.x + size/2.0f;
	y[1] = Center.y + size/2.0f;
	z[1] = Center.z - size/2.0f;

	x[2] = Center.x + size/2.0f;
	y[2] = Center.y - size/2.0f;
	z[2] = Center.z + size/2.0f;

	x[3] = Center.x + size/2.0f;
	y[3] = Center.y - size/2.0f;
	z[3] = Center.z - size/2.0f;

	x[4] = Center.x - size/2.0f;
	y[4] = Center.y + size/2.0f;
	z[4] = Center.z + size/2.0f;

	x[5] = Center.x - size/2.0f;
	y[5] = Center.y + size/2.0f;
	z[5] = Center.z - size/2.0f;

	x[6] = Center.x - size/2.0f;
	y[6] = Center.y - size/2.0f;
	z[6] = Center.z + size/2.0f;

	x[7] = Center.x - size/2.0f;
	y[7] = Center.y - size/2.0f;
	z[7] = Center.z - size/2.0f;
	bool collision1 = false;
	bool newc = false;

	for (int i = 0; i<8; i++)
	{
		newc = (PointCollision(b, Vector3D(x[i], y[i], z[i])));
		collision1 = collision1 || newc;
		if (collision1)
			return true;
	}
    return false;
}

bool CollisionDetection::PointCollision(BoundingBox *b, const Vector3D& pPoint)
{
	return ((pPoint.x <= b->max.x) && (pPoint.x>= b->min.x) && 
			(pPoint.y<= b->max.y) && (pPoint.y>= b->min.y) && 
			(pPoint.z<= b->max.z) && (pPoint.z >= b->min.z));
}

void CollisionDetection::translateBoundingBox(int i, const Vector3D& pTranslation)
{
	static_box[i]->max = static_box[i]->OriginalMax + pTranslation;
	static_box[i]->min = static_box[i]->OriginalMin + pTranslation;
}

void CollisionDetection::translateBoundingBoxOriginal(int i, const Vector3D& pTranslation)
{
	static_box[i]->OriginalMax += pTranslation;
	static_box[i]->OriginalMin += pTranslation;
}

void CollisionDetection::translateBoundingBoxes(const Vector3D& pTranslation)
{
	for (unsigned int i = 0; i<static_box.size(); i++) 
		translateBoundingBox(i, pTranslation);
}

int CollisionDetection::addCollisionBox(const Vector3D& pMin, 
										const Vector3D& pMax) 
{
	BoundingBox* bb;
	bb = new BoundingBox;
	bb->max = pMax;
	bb->min = pMin;

	bb->OriginalMax = pMax;
	bb->OriginalMin = pMin;

	static_box.push_back(bb);
	return (static_box.size()-1);
}

void CollisionDetection::Draw(DrawManager* dm)
{
	float depth = 0;

	for (unsigned int i = 0; i<static_box.size(); i++) 
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		dm->DrawCollisionBox(static_box[i]);
		//glColor3f();
		//depth = static_box[i]->max.z-static_box[i]->min.z;
		/*dm->DrawCube(-1, 1, 1, static_box[i]->min.x, static_box[i]->min.y, static_box[i]->min.z+depth,
							   static_box[i]->max.x-static_box[i]->min.x,
							   static_box[i]->max.y-static_box[i]->min.y,
							   static_box[i]->max.z-static_box[i]->min.z);*/
	}
}
