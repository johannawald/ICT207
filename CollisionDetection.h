#pragma once

#include "BoundingBox.h"
#include <GL\freeglut.h>
#include <vector>

class DrawManager;
class CollisionDetection
{
private:
	//BoundingBox *box_mo;
	std::vector<BoundingBox*> static_box;
	GLfloat x_old; //debug
	GLfloat y_old;
	GLfloat z_old;

	//BoundingBox* CreateCollisionBox();
	bool Collision(BoundingBox *b, GLfloat x, GLfloat y, GLfloat z, GLfloat size);
	void translateBoundingBox(int i, const GLfloat x, const GLfloat y, const GLfloat z);
public:
	void Draw(DrawManager* dm);

	void translateBoundingBoxes(const GLfloat x, const GLfloat y, const GLfloat z);
	bool Collision(GLfloat x, GLfloat y, GLfloat z, int &pIndex);
	bool CollisionX(int pIndex, GLfloat x);
	bool CollisionY(int pIndex, GLfloat y);
	bool CollisionZ(int pIndex, GLfloat z);

	void addCollisionBox(const GLfloat pMinX, const GLfloat pMinY, const GLfloat pMinZ,
						 const GLfloat pMaxX, const GLfloat pMaxY, const GLfloat pMaxZ);

};


