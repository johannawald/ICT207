#include "CollisionDetection.h"
#include <iostream>

bool CollisionDetection::Collision(GLfloat x, GLfloat y, GLfloat z)
{
	bool collision = false;
	for (int i = 0; i<static_box.size(); i++) 
	{
		collision = collision || Collision(static_box[i], x, y, z, 100);
	}
	return collision;
}

bool CollisionDetection::Collision(BoundingBox *b, GLfloat x,GLfloat y,GLfloat z, GLfloat size)
{
	if ((x!=x_old) || (y!=y_old) || (z!=z_old)) 
	{
		std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
	}
	x_old = x;
	y_old = y;
	z_old = z;

	GLfloat x1 = x; //+size/2.0f;
	GLfloat y1 = y; //+size/2.0f;
	GLfloat z1 = z; //+size/2.0f;

	GLfloat x2 = x-size/2.0f;
	GLfloat y2 = y-size/2.0f;
	GLfloat z2 = z-size/2.0f;
	
	bool collision1 = ((x1 <= b->max.x) && (x1>= b->min.x) && (y1<= b->max.y) && (y1>= b->min.y) && (z1<= b->max.z) && (z1 >= b->min.z));
	bool collision2 =  ((x2 <= b->max.x) && (x2>= b->min.x) && (y2<= b->max.y) && (y2>= b->min.y) && (z2<= b->max.z) && (z2 >= b->min.z));

    return (collision1 || collision2);
}

void CollisionDetection::translateBoundingBox(int i, const GLfloat x, const GLfloat y, const GLfloat z)
{
	static_box[i]->max.x += x;
	static_box[i]->max.y += y;
	static_box[i]->max.z += z;
	
	static_box[i]->min.x += x;
	static_box[i]->min.y += y;
	static_box[i]->min.z += z;
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
	static_box.push_back(bb);
}