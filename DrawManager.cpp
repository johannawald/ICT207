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

void DrawManager::RenderString(const float x, const float y, void *font, const char* str, const unsigned r, const unsigned g, const unsigned b) const
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

void DrawManager::DrawStairs(const float stairWidth, const float stairHeight, const float stairDepth, const float numSteps) const
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

//everyone, not finished yet
void DrawManager::DrawQuad(const GLint pTexture, 
				const int TexCoordX, const int TexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight) const
{
	glBindTexture(GL_TEXTURE_2D, pTexture);
	glBegin(GL_QUADS);
		glTexCoord2f (TexCoordX, TexCoordX);		
		glVertex3f(0, 0, 0);
		glTexCoord2f (0.0, TexCoordX);		
		glVertex3f(0, 0, pWidth);
		glTexCoord2f (0.0, 0.0);		
		glVertex3f(pWidth, 0,	pWidth);
		glTexCoord2f (TexCoordX, 0.0);		
		glVertex3f(pWidth, 0, 0);
	glEnd();
}
