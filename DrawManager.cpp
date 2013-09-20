//  @ File Name : DrawManager.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet


#include "DrawManager.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

DrawManager::DrawManager() {	
}

DrawManager::~DrawManager() {
}

void DrawManager::RenderString(float x, float y, void *font, const char* str, unsigned r, unsigned g, unsigned b)
{
	glPushAttrib(GL_CURRENT_BIT);
		glBindTexture(GL_TEXTURE_2D, -1);
		glDisable(GL_LIGHTING);
		glColor3f(r,g,b);
		glRasterPos2f(x, y);
		glutBitmapString(font, (const unsigned char*) str);
		glEnable(GL_LIGHTING); 
	glPopAttrib();
}

void DrawManager::drawStairs(float stairWidth, float stairHeight, float stairDepth, float numSteps)
{
	//work out step dimensions
	float stepHeight, stepDepth;
	stepHeight = stairHeight / numSteps;
	stepDepth = stairDepth / numSteps;

	//draw vertical step faces
	for (int i = 0; i < numSteps; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.125, 0.5);		glVertex3f(0.0, stepHeight * i, stepDepth * i);
			glTexCoord2f (0.0, 0.5);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * i);
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * i);
			glTexCoord2f (0.125, 0.0);		glVertex3f(stairWidth, stepHeight * i, stepDepth * i);
		glEnd();
	}

	//draw horizontal step faces
	for (int i = 0; i < numSteps; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.125, 0.5);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * i);
			glTexCoord2f (0.0, 0.5);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.125, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * i);
		glEnd();
	}

	//draw sides of staircase
	for (int i = 0; i < numSteps; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.125, 0.125);	glVertex3f(0.0, 0.0, stepDepth * i);
			glTexCoord2f (0.0, 0.125);		glVertex3f(0.0, 0.0, stepDepth * (i + 1));
			glTexCoord2f (0.0, 0.0);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.125, 0.0);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * i);

			glTexCoord2f (0.125, 0.125);	glVertex3f(stairWidth, 0.0, stepDepth * i);
			glTexCoord2f (0.0, 0.125);		glVertex3f(stairWidth, 0.0, stepDepth * (i + 1));
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.125, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * i);
		glEnd();
	}

	//draw rear of staircase
		glBegin(GL_QUADS);
			glTexCoord2f (0.5, 0.5);		glVertex3f(0.0, 0.0, stairDepth);
			glTexCoord2f (0.0, 0.5);		glVertex3f(stairWidth, 0.0, stairDepth);
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stairHeight, stairDepth);
			glTexCoord2f (0.5, 0.0);		glVertex3f(0.0, stairHeight, stairDepth);
		glEnd();
}