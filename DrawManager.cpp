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

void DrawManager::DrawRect(const GLint pTexture, 
				const int TexCoordX, const int TexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight) const
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, pTexture);
		glBegin(GL_QUADS);
			glTexCoord2f(TexCoordX, TexCoordX);		
			glVertex3f(pPositionX, pPositionY, pPositionZ);
			glTexCoord2f (0.0, TexCoordX);		
			glVertex3f(pPositionX+pWidth, pPositionY, pPositionZ);
			glTexCoord2f (0.0, 0.0);		
			glVertex3f(pPositionX+pWidth, pPositionY+pHeight, pPositionZ);
			glTexCoord2f (TexCoordX, 0.0);		
			glVertex3f(pPositionX, pPositionY+pHeight, pPositionZ);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}

void DrawManager::DrawRect(const GLint pTexture, 
				const int TexCoordX, const int TexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight, 
				const float angleX, const float angleY, const float angleZ) const
{
	glPushMatrix();
		glTranslatef(pPositionX, pPositionY, pPositionZ);
		glRotatef(angleX,1,0,0);
		glRotatef(angleY,0,1,0);
		glRotatef(angleZ,0,0,1);
		glTranslatef(-pPositionX, -pPositionY, -pPositionZ);
		DrawRect(pTexture, TexCoordX, TexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pHeight);
	glPopMatrix();
}

//johanna, change stair function

void DrawManager::DrawCube(const GLint pTexture, 
						   const int pTexCoordX, const int pTexCoordY, 
						   const int pPositionX, const int pPositionY, const int pPositionZ, 
						   const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth) const
{	
	//z is reversed!
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glBindTexture(GL_TEXTURE_2D, -1);
		glDisable(GL_LIGHTING);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, 10, 10);
		//draw the front
		//glColor3f(0.3f, 0.0f, 0.0f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pHeight); 
		//draw the back
		//glColor3f(0.0f, 0.5f, 0.0f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ-pDepth, pWidth, pHeight);
		//draw the side
		//glColor3f(0.0f, 0.0f, 0.5f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pDepth, pHeight, 0, 90, 0);
		glTranslatef(pWidth,0,-pDepth);
		//glColor3f(0.0f, 0.0f, 0.5f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pDepth, pHeight, 0, 270, 0);
		glTranslatef(-pWidth,0,pDepth);
		//draw the top / bottom
		//glColor3f(0.5f, 0.5f, 0.0f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pDepth, -90, 0, 0);
		glTranslatef(0,pHeight,0);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pDepth, -90, 0, 0);
		glTranslatef(0,-pHeight,0);
		glEnable(GL_LIGHTING); 
	glPopAttrib();
	glPopMatrix();
}

void DrawManager::DrawCollisionCube(CollisionDetection* collision, const GLint pTexture, 
				const int pTexCoordX, const int pTexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth)
{
	glPushMatrix();
		DrawCube(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pHeight, pDepth);
		collision->addCollisionBox(pPositionX, pPositionY, pPositionZ-pDepth, pPositionX+pWidth, pPositionY+pHeight, pPositionZ);
	glPopAttrib();
}

void DrawManager::DrawCollisionRect(CollisionDetection* collision, const GLint pTexture, 
				const int pTexCoordX, const int pTexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight)
{
	glPushMatrix();
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pHeight);
		collision->addCollisionBox(pPositionX, pPositionY, pPositionZ, pPositionX+pWidth, pPositionY+pHeight, pPositionZ+100); 
	glPopAttrib();
}
