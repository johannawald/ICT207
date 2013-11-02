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
		pDrawManager.DrawCollisionBoxColored(*mBoundingBoxes[i]);
	}
}

const int CollisionDetection::AddCollisionBox(const Vector3D& pMin, const Vector3D& pMax) 
{
	BoundingBox* boundingbox;
	boundingbox = new BoundingBox(pMin, pMax);
	mBoundingBoxes.push_back(boundingbox);
	return (mBoundingBoxes.size()-1);
}

float CollisionDetection::Collisions(const int pBBIndex, int& pIndex, const bool pCY)
{
	return Collisions(*mBoundingBoxes[pBBIndex], pIndex, true, pBBIndex);
}

const BoundingBox& CollisionDetection::GetCollisionBox(const int pIndex) const
{
	return *mBoundingBoxes[pIndex];
}

float CollisionDetection::Collisions(const BoundingBox& pBoundingBox1, int& pIndex, const bool pCY, const int pSkip)
{
	float collisionResult = 0;
	float collision = 0;
	pIndex = -1;
	for (unsigned int i = 0; i<mBoundingBoxes.size(); i++) 
	{
		if (i==pSkip)
			continue;
		collision = Collision(pBoundingBox1, *mBoundingBoxes[i], pCY);
		if (collision>0)
			pIndex=i;
		collisionResult = collisionResult + collision;
	}
	return collisionResult;
}

float CollisionDetection::Collision(const BoundingBox& pBoundingBox1, const BoundingBox& pBoundingBox2, const bool pCY)
{	
	Vector3D pBB2Center = pBoundingBox2.GetCenter();
	Vector3D pBB1Center = pBoundingBox1.GetCenter();
	
	Vector3D vDistance = pBB1Center.GetDistance(pBB2Center);
	Vector3D vMaxDistance = (pBoundingBox1.GetSize()/2.0f) + (pBoundingBox2.GetSize()/2.0f);
	if (true) 
	{	
		if ((abs(vDistance.x) >= vMaxDistance.x ||
		    abs(vDistance.y) >= vMaxDistance.y || 
			abs(vDistance.z) >= vMaxDistance.z))
			return 0;
		else 
			return (vMaxDistance.x - vDistance.x) * (vMaxDistance.y - vDistance.y) * (vMaxDistance.z - vDistance.z);
	}
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

void CollisionDetection::MoveBoundingBox(const int pIndex, const Vector3D& pTranslation)
{
	mBoundingBoxes[pIndex]->Move(pTranslation);
}

void CollisionDetection::TranslateBoundingBoxes(const Vector3D& pTranslation)
{
	for (unsigned int i = 0; i<mBoundingBoxes.size(); i++) 
		TranslateBoundingBox(i, pTranslation);
}
