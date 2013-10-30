#include "CollisionDetection.h"
#include <iostream>
#include <cstdlib>
#include "DrawManager.h"
#include "Vector3D.h"

float CollisionDetection::Collision(const Vector3D& pPoint, int &pIndex, const BoundingBox* bb, const bool pCY) 
{
	float collisionResult = 0;
	float collision = 0;
	for (unsigned int i = 0; i<static_box.size(); i++) 
	{
		collision = Collision2(static_box[i], static_box[i], pCY);
		if (collision>0)
		{
			pIndex=i;
		}
		collisionResult = collisionResult + collision;
	}
	return collisionResult;
}

float CollisionDetection::Collisions(const int pBBIndex, int& pIndex, const bool pCY)
{
	return Collisions(static_box[pBBIndex], pIndex, true, pBBIndex);
}

BoundingBox* CollisionDetection::GetCollisionBox(const int pIndex)
{
	return static_box[pIndex];
}

float CollisionDetection::Collisions(BoundingBox* pBoundingBox1, int& pIndex, const bool pCY, const int pSkip)
{
	float collisionResult = 0;
	float collision = 0;
	pIndex = -1;
	for (unsigned int i = 0; i<static_box.size(); i++) 
	{
		if (i==pSkip)
			continue;
		collision = Collision2(pBoundingBox1, static_box[i], pCY);
		if (collision>0)
			pIndex=i;
		collisionResult = collisionResult + collision;
	}
	return collisionResult;
}

float CollisionDetection::CollisionX(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2)
{
	Vector3D pBB2Center = pBoundingBox2->GetCenter(); //we don't need that!
	Vector3D pBB1Center = pBoundingBox1->GetCenter();
	
	Vector3D vDistance = pBB1Center.GetDistance(pBB2Center);
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	if (abs(vDistance.x) <= vMaxDistance.x)
		return vMaxDistance.x - vDistance.x; //(abs(vDistance.x) <= vMaxDistance.x);
	else 
		return 0;
}

float CollisionDetection::CollisionY(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2)
{
	Vector3D pBB2Center = pBoundingBox2->GetCenter(); //we don't need that!
	Vector3D pBB1Center = pBoundingBox1->GetCenter();
	
	Vector3D vDistance = pBB1Center.GetDistance(pBB2Center);
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	if (abs(vDistance.y) <= vMaxDistance.y)
		return vMaxDistance.y - vDistance.y; //(abs(vDistance.x) <= vMaxDistance.x);
	else 
		return 0;
}

float CollisionDetection::CollisionZ(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2)
{
	Vector3D pBB2Center = pBoundingBox2->GetCenter(); //we don't need that!
	Vector3D pBB1Center = pBoundingBox1->GetCenter();
	
	Vector3D vDistance = pBB1Center.GetDistance(pBB2Center);
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	if (abs(vDistance.z) <= vMaxDistance.z)
		return vMaxDistance.z - vDistance.z; //(abs(vDistance.x) <= vMaxDistance.x);
	else 
		return 0;
}

float CollisionDetection::Collision2(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2, bool pCX, bool pCY, bool pCZ)
{	
	//return false;	
	Vector3D pBB2Center = pBoundingBox2->GetCenter();
	Vector3D pBB1Center = pBoundingBox1->GetCenter();
	
	Vector3D vDistance = pBB1Center.GetDistance(pBB2Center);
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	
	if (pCX && pCY && pCZ) 
	{	
		if (!(abs(vDistance.x) <= vMaxDistance.x &&
		    abs(vDistance.y) <= vMaxDistance.y && 
			abs(vDistance.z) <= vMaxDistance.z))
			return 0;
		else 
			return (vMaxDistance.x - vDistance.x) + (vMaxDistance.y - vDistance.y) + (vMaxDistance.z - vDistance.z);
	}
	
		
	//all axis
	if (pCX && !pCY && pCZ)
		if (!(abs(vDistance.x) <= vMaxDistance.x && abs(vDistance.z) <= vMaxDistance.z))
			return 0;
		else 
			return (vMaxDistance.x - vDistance.x) + (vMaxDistance.z - vDistance.z);
	return 0;
	/*Vector3D pBB2Center = pBoundingBox2->GetCenter();
	Vector3D pBB1Center = pBoundingBox1->GetCenter();
	
	Vector3D vDistance = pBB1Center.GetDistance(pBB2Center);
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	//bool* returnValue = new bool[3];
	returnValue[0] = abs(vDistance.x) <= vMaxDistance.x;
	returnValue[1] = abs(vDistance.x) <= vMaxDistance.x;
	returnValue[2] = abs(vDistance.x) <= vMaxDistance.x;
	return returnValue;*/
}

/*float CollisionDetection::Collision(BoundingBox *b, const Vector3D& pPoint, const GLfloat size, bool pShowPosition)
{
	//old collision function
	if (pShowPosition)
	{
		if (pPoint!=mVold) 
			std::cout << "x: " << pPoint.x << " y: " << pPoint.y << " z: " << pPoint.z << std::endl;
		mVold = pPoint;
	}

	Vector3D Center = pPoint - b->GetMax() - b->OriginalMax;

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
}*/

bool CollisionDetection::PointCollision(BoundingBox *b, const Vector3D& pPoint)
{
	return ((pPoint.x <= b->GetMax().x) && (pPoint.x>= b->GetMin().x) && 
			(pPoint.y<= b->GetMax().y) && (pPoint.y>= b->GetMin().y) && 
			(pPoint.z<= b->GetMax().z) && (pPoint.z >= b->GetMin().z));
}

void CollisionDetection::translateBoundingBox(int i, const Vector3D& pTranslation)
{
	static_box[i]->Translate(pTranslation);

	//SetMax(static_box[i]->OriginalMax + pTranslation);
	//static_box[i]->SetMin(static_box[i]->OriginalMin + pTranslation);
}

void CollisionDetection::translateBoundingBoxOriginal(int i, const Vector3D& pTranslation)
{
	static_box[i]->OriginalMax += pTranslation;
	static_box[i]->OriginalMin += pTranslation;
	static_box[i]->mMin += pTranslation;
	static_box[i]->mMax += pTranslation;
}

void CollisionDetection::translateBoundingBoxes(const Vector3D& pTranslation)
{
	for (unsigned int i = 0; i<static_box.size(); i++) 
		translateBoundingBox(i, pTranslation);
}

BoundingBox& CollisionDetection::getCollisionBox(const Vector3D& pMin, const Vector3D& pMax)
{
	BoundingBox bb; //not working... :/
	/*bb.max = pMax;
	bb.min = pMin;

	bb.OriginalMax = pMax;
	bb.OriginalMin = pMin;*/
	return bb;
}

int CollisionDetection::addCollisionBox(const Vector3D& pMin, const Vector3D& pMax) 
{
	BoundingBox* bb;
	bb = new BoundingBox(pMin, pMax);
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
		//dm->DrawCollisionBox(static_box[i]);
		//glColor3f(0.0f, 0.0f, 0.0f);
		dm->DrawCollisionBoxColored(static_box[i]);
		//glColor3f();
		//depth = static_box[i]->max.z-static_box[i]->min.z;
	
	}
}
