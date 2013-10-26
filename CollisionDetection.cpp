#include "CollisionDetection.h"
#include <iostream>
#include <cstdlib>
#include "DrawManager.h"

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

bool CollisionDetection::Collision(GLfloat x, GLfloat y, GLfloat z, int &pIndex)
{
	bool collisionResult = false;
	bool collision = false;
	for (int i = 0; i<static_box.size(); i++) 
	{
		collision = Collision(static_box[i], x, y, z, 10, false);
		if (collision)
			pIndex=i;
		collisionResult = collisionResult || collision;
	}
	return collisionResult;
}

bool CollisionDetection::Collision(BoundingBox *b, GLfloat x, GLfloat y, GLfloat z, GLfloat size, bool pShowPosition)
{
	if (pShowPosition)
	{
		if ((x!=x_old) || (y!=y_old) || (z!=z_old)) 
			std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
		x_old = x;
		y_old = y;
		z_old = z;
	}

	GLfloat x1 = x - (b->max.x-b->OriginalMax.x);
	GLfloat y1 = y - (b->max.y-b->OriginalMax.y);
	GLfloat z1 = z - (b->max.z-b->OriginalMax.z);

	bool collision1 = ((x1 <= b->max.x) && (x1>= b->min.x) 

						&& (y1<= b->max.y) && (y1>= b->min.y) 
						&& (z1<= b->max.z) && (z1 >= b->min.z));

    return (collision1 || false);
    return false;
}

void CollisionDetection::translateBoundingBox(int i, const GLfloat x, const GLfloat y, const GLfloat z)
{
	static_box[i]->max.x = static_box[i]->OriginalMax.x + x;
	static_box[i]->max.y = static_box[i]->OriginalMax.y + y;
	static_box[i]->max.z = static_box[i]->OriginalMax.z + z;
	
	static_box[i]->min.x = static_box[i]->OriginalMin.x + x;
	static_box[i]->min.y = static_box[i]->OriginalMin.y + y;
	static_box[i]->min.z = static_box[i]->OriginalMin.z + z;
}

void CollisionDetection::translateBoundingBoxes(const GLfloat x, const GLfloat y, const GLfloat z)
{
	for (int i = 0; i<static_box.size(); i++) 
		translateBoundingBox(i, x, y, z);
}

void CollisionDetection::addCollisionBox(const GLfloat pMinX, const GLfloat pMinY, const GLfloat pMinZ,
										 const GLfloat pMaxX, const GLfloat pMaxY, const GLfloat pMaxZ) 
{
	BoundingBox* bb;
	bb = new BoundingBox;
	bb->max.x = pMaxX;
	bb->max.y = pMaxY;
	bb->max.z = pMaxZ;
	
	bb->min.x = pMinX;
	bb->min.y = pMinY;
	bb->min.z = pMinZ;

	bb->OriginalMax.x = pMaxX;
	bb->OriginalMax.y = pMaxY;
	bb->OriginalMax.z = pMaxZ;
	
	bb->OriginalMin.x = pMinX;
	bb->OriginalMin.y = pMinY;
	bb->OriginalMin.z = pMinZ;

	static_box.push_back(bb);
}

void CollisionDetection::Draw(DrawManager* dm)
{
	float depth = 0;

	for (int i = 0; i<static_box.size(); i++) 
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		dm->DrawCollisionBox(static_box[i]);
		//glColor3f();
		depth = static_box[i]->max.z-static_box[i]->min.z;
		dm->DrawCube(-1, 1, 1, static_box[i]->min.x, static_box[i]->min.y, static_box[i]->min.z+depth,
							   static_box[i]->max.x-static_box[i]->min.x,
							   static_box[i]->max.y-static_box[i]->min.y,
							   static_box[i]->max.z-static_box[i]->min.z);
	}
}
