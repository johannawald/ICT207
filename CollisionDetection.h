#pragma once

#include "BoundingBox.h"
#include <GL\freeglut.h>
#include <vector>

class CollisionDetection
{
private:
	//BoundingBox *box_mo;
	std::vector<BoundingBox*> static_box;
	GLfloat x_old; //debug
	GLfloat y_old;
	GLfloat z_old;

	//BoundingBox* CreateCollisionBox();
	bool Collision(BoundingBox *b, GLfloat x, GLfloat y, GLfloat z);

	void drawBox(BoundingBox *b);
public:
	CollisionDetection(void);
	~CollisionDetection(void);

	void translateBoundingBox(int i, const GLfloat x, const GLfloat y, const GLfloat z);
	void display();
	bool Collision(GLfloat x, GLfloat y, GLfloat z);
	void addCollisionBox(const GLfloat pMinX, const GLfloat pMinY, const GLfloat pMinZ,
						 const GLfloat pMaxX, const GLfloat pMaxY, const GLfloat pMaxZ);

};


