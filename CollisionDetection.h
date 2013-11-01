#pragma once

#include "BoundingBox.h"
#include <GL\freeglut.h>
#include <vector>
#include "Vector3D.h"

class DrawManager;
class CollisionDetection
{
private:
	//BoundingBox *box_mo;
	std::vector<BoundingBox*> static_box;
	
	Vector3D mVold; 

	//BoundingBox* CreateCollisionBox();
	bool PointCollision(BoundingBox *b, const Vector3D& pPoint);
	float Collision(BoundingBox *b, const Vector3D& pPoint, const GLfloat size, bool pShowPosition);
public:
	void Draw(DrawManager* dm);

	void translateBoundingBox(int i, const Vector3D& pTranslation);
	void translateBoundingBoxOriginal(int i, const Vector3D& pTranslation);
	void translateBoundingBoxes(const Vector3D& pTranslation);
	void scaleBoundingBoxes(const Vector3D& pScale);

	BoundingBox* GetCollisionBox(const int pIndex);

	float CollisionX(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	float CollisionY(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	float CollisionZ(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);

	//bool Collision2(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	//bool* CollisionSeperate(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	float Collision2(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2, bool pCX = true, bool pCY = true, bool pCZ = true);
	//bool Collision(BoundingBox* pBoundingBox1, const int pIndex); //collision between camerea and index
	float Collisions(const int pBBIndex, int& pIndex, const bool pCY);
	float Collisions(BoundingBox* pBoundingBox1, int& pIndex, const bool pCY = true, const int pSkip = -1);
	//bool Collision(const Vector3D& pPoint, int &pIndex, const GLfloat pSize);
	float Collision(const Vector3D& pPoint, int &pIndex, const BoundingBox* bb, const bool pCY = true);

	int addCollisionBox(const Vector3D& pMin, const Vector3D& pMax);
};


