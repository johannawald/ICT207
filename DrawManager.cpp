//  @ File Name : DrawManager.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet


#include "DrawManager.h"
#include "AssertManager.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

DrawManager::DrawManager() {	
}

DrawManager::~DrawManager() {
}

void DrawManager::RenderString(float x, float y, void *font, const char* str)
{ 
	glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_LIGHTING);
		glColor3f(1,0,0);
		glRasterPos2f(x, y);
		glutBitmapString(font, (const unsigned char*) str);
		glEnable(GL_LIGHTING);
	glPopAttrib();
}