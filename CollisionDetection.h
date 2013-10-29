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
	bool Collision(BoundingBox *b, const Vector3D& pPoint, const GLfloat size, bool pShowPosition);
public:
	void Draw(DrawManager* dm);

	void translateBoundingBox(int i, const Vector3D& pTranslation);
	void translateBoundingBoxOriginal(int i, const Vector3D& pTranslation);
	void translateBoundingBoxes(const Vector3D& pTranslation);
	void scaleBoundingBoxes(const Vector3D& pScale);

	bool Collision2(BoundingBox* pBoundingBox1, BoundingBox* pBoundingBox2);
	bool Collision(BoundingBox* pBoundingBox1, const int pIndex); //collision between camerea and index
	bool Collisions(BoundingBox* pBoundingBox1, int& pIndex);
	//bool Collision(const Vector3D& pPoint, int &pIndex, const GLfloat pSize);
	bool Collision(const Vector3D& pPoint, int &pIndex, const BoundingBox* bb);
	//bool CollisionX(int pIndex, GLfloat x);
	//bool CollisionY(int pIndex, GLfloat y);
	//bool CollisionZ(int pIndex, GLfloat z);

	BoundingBox& getCollisionBox(const Vector3D& pMin, const Vector3D& pMax);
	int addCollisionBox(const Vector3D& pMin, const Vector3D& pMax);
};


