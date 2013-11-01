#include "CollisionDetection.h"
#include <iostream>
#include <cstdlib>
#include "DrawManager.h"
#include "Vector3D.h"

void CollisionDetection::Draw(const DrawManager& pDrawManager) const
{
	float depth = 0;
	for (unsigned int i = 0; i<mBoundingBoxes.size(); i++) 
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		pDrawManager.DrawCollisionBoxColored(mBoundingBoxes[i]);
	}
}

const int CollisionDetection::AddCollisionBox(const Vector3D& pMin, const Vector3D& pMax) 
{
	BoundingBox* boundingbox;
	boundingbox = new BoundingBox(pMin, pMax);
	mBoundingBoxes.push_back(boundingbox);
	return (mBoundingBoxes.size()-1);
}

float CollisionDetection::Collision(const Vector3D& pPoint, int &pIndex, const BoundingBox* bb, const bool pCY) 
{
	float collisionResult = 0;
	float collision = 0;
	for (unsigned int i = 0; i<mBoundingBoxes.size(); i++) 
	{
		collision = Collision2(mBoundingBoxes[i], mBoundingBoxes[i], pCY);
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
	return Collisions(mBoundingBoxes[pBBIndex], pIndex, true, pBBIndex);
}

const BoundingBox& CollisionDetection::GetCollisionBox(const int pIndex) const
{
	return *mBoundingBoxes[pIndex];
}

float CollisionDetection::Collisions(BoundingBox* pBoundingBox1, int& pIndex, const bool pCY, const int pSkip)
{
	float collisionResult = 0;
	float collision = 0;
	pIndex = -1;
	for (unsigned int i = 0; i<mBoundingBoxes.size(); i++) 
	{
		if (i==pSkip)
			continue;
		collision = Collision2(pBoundingBox1, mBoundingBoxes[i], pCY);
		if (collision>0)
			pIndex=i;
		collisionResult = collisionResult + collision;
	}
	return collisionResult;
}

float CollisionDetection::CollisionX(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2)
{
	Vector3D vDistance = pBoundingBox1->GetCenter().GetDistance(pBoundingBox2->GetCenter());
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	if (abs(vDistance.x) <= vMaxDistance.x)
		return vMaxDistance.x - vDistance.x;
	else 
		return 0;
}

float CollisionDetection::CollisionY(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2)
{
	Vector3D vDistance = pBoundingBox1->GetCenter().GetDistance(pBoundingBox2->GetCenter());
	Vector3D vMaxDistance = (pBoundingBox1->GetSize()/2.0f) + (pBoundingBox2->GetSize()/2.0f);

	if (abs(vDistance.y) <= vMaxDistance.y)
		return vMaxDistance.y - vDistance.y;
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
		if (!((abs(vDistance.x) <= vMaxDistance.x &&
		    abs(vDistance.y) <= vMaxDistance.y && 
			abs(vDistance.z) <= vMaxDistance.z)))
			return 0;
		else 
			return (vMaxDistance.x - vDistance.x) + (vMaxDistance.y - vDistance.y) + (vMaxDistance.z - vDistance.z);
	}
	if (pCX && !pCY && pCZ)
		if (!(abs(vDistance.x) <= vMaxDistance.x && abs(vDistance.z) <= vMaxDistance.z))
			return 0;
		else 
			return (vMaxDistance.x - vDistance.x) + (vMaxDistance.z - vDistance.z);
	return 0;
}

const bool CollisionDetection::PointCollision(const BoundingBox *pBoundingBox, const Vector3D& pPoint) const
{
	return ((pPoint.x <= pBoundingBox->GetMax().x) && (pPoint.x >= pBoundingBox->GetMin().x) && 
			(pPoint.y <= pBoundingBox->GetMax().y) && (pPoint.y >= pBoundingBox->GetMin().y) && 
			(pPoint.z <= pBoundingBox->GetMax().z) && (pPoint.z >= pBoundingBox->GetMin().z));
}

void CollisionDetection::TranslateBoundingBox(const int pIndex, const Vector3D& pTranslation)
{
	mBoundingBoxes[pIndex]->Translate(pTranslation);
}

void CollisionDetection::translateBoundingBoxOriginal(int i, const Vector3D& pTranslation)
{
	mBoundingBoxes[i]->TranslatePosition(pTranslation);
	/*OriginalMax += pTranslation;
	static_box[i]->OriginalMin += pTranslation;
	static_box[i]->mMin += pTranslation;
	static_box[i]->mMax += pTranslation;*/
}

void CollisionDetection::TranslateBoundingBoxes(const Vector3D& pTranslation)
{
	for (unsigned int i = 0; i<mBoundingBoxes.size(); i++) 
		TranslateBoundingBox(i, pTranslation);
}


