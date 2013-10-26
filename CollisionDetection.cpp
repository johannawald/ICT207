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

bool CollisionDetection::Collision(GLfloat x, GLfloat y, GLfloat z, int &pIndex, const int pSize)
{
	bool collisionResult = false;
	bool collision = false;
	for (int i = 0; i<static_box.size(); i++) 
	{
		collision = Collision(static_box[i], x, y, z, pSize, false);
		if (collision)
			pIndex=i;
		collisionResult = collisionResult || collision;
	}
	return collisionResult;
}

bool CollisionDetection::Collision(BoundingBox *b, GLfloat px, GLfloat py, GLfloat pz, GLfloat size, bool pShowPosition)
{
	if (pShowPosition)
	{
		if ((px!=x_old) || (py!=y_old) || (pz!=z_old)) 
			std::cout << "x: " << px << " y: " << py << " z: " << pz << std::endl;
		x_old = px;
		y_old = py;
		z_old = pz;
	}

	//not only one point a cube! 

	GLfloat xCenter = (px - (b->max.x-b->OriginalMax.x));
	GLfloat yCenter = (py - (b->max.y-b->OriginalMax.y));
	GLfloat zCenter = (pz - (b->max.z-b->OriginalMax.z));

	GLfloat x[8];
	GLfloat y[8];
	GLfloat z[8];

	x[0] = xCenter + size/2.0;
	y[0] = yCenter + size/2.0;
	z[0] = zCenter + size/2.0;

	x[1] = xCenter + size/2.0;
	y[1] = yCenter + size/2.0;
	z[1] = zCenter - size/2.0;

	x[2] = xCenter + size/2.0;
	y[2] = yCenter - size/2.0;
	z[2] = zCenter + size/2.0;

	x[3] = xCenter + size/2.0;
	y[3] = yCenter - size/2.0;
	z[3] = zCenter - size/2.0;

	x[4] = xCenter - size/2.0;
	y[4] = yCenter + size/2.0;
	z[4] = zCenter + size/2.0;

	x[5] = xCenter - size/2.0;
	y[5] = yCenter + size/2.0;
	z[5] = zCenter - size/2.0;

	x[6] = xCenter - size/2.0;
	y[6] = yCenter - size/2.0;
	z[6] = zCenter + size/2.0;

	x[7] = xCenter - size/2.0;
	y[7] = yCenter - size/2.0;
	z[7] = zCenter - size/2.0;
	bool collision1 = false;
	bool newc = false;

	for (int i = 0; i<8; i++)
	{
		newc = (PointCollision(b, x[i], y[i], z[i]));
		collision1 = collision1 || newc;
		if (collision1)
			return true;
	}
    return false;
}

bool CollisionDetection::PointCollision(BoundingBox *b, GLfloat x, GLfloat y, GLfloat z)
{
	return ((x <= b->max.x) && (x>= b->min.x) && (y<= b->max.y) && (y>= b->min.y) && (z<= b->max.z) && (z >= b->min.z));
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
		//depth = static_box[i]->max.z-static_box[i]->min.z;
		/*dm->DrawCube(-1, 1, 1, static_box[i]->min.x, static_box[i]->min.y, static_box[i]->min.z+depth,
							   static_box[i]->max.x-static_box[i]->min.x,
							   static_box[i]->max.y-static_box[i]->min.y,
							   static_box[i]->max.z-static_box[i]->min.z);*/
	}
}
