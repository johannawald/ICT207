//  cameraMap.cpp
//
//  Implementation file for CameraMap Class
//  Defines all the methods declared, but not defined, in cameraMap.h
//
//  Shay Leary, April 2005
// 26/11/2013 Johanna Wald, added some Push/Pop Attribues
//--------------------------------------------------------------------------------------

#include "cameraMap.h"
#include "DrawManager.h"
#include <GL/freeglut.h>

//--------------------------------------------------------------------------------------
//  Display a map with a cursor on it, which moves with the camera
//--------------------------------------------------------------------------------------

void CameraMap::DisplayMap(const int & screenWidth, const int & screenHeight,
				           const GLdouble &xPos, const GLdouble & zPos, const GLuint & tempImage)
{
	GLdouble tempX = xPos/163.0 - 2096/163;
	GLdouble tempZ = zPos/164.0 - 4688/164;
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glScalef(1, -1, 1);
	
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -screenHeight, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// display the cursor of the camera position
	glBegin(GL_QUADS);		
		glVertex3f(219.0 - tempX - 2.0, 256.0 - tempZ - 2.0, 0.0);
		glVertex3f(219.0 - tempX + 2.0, 256.0 - tempZ - 2.0,  0.0);
		glVertex3f(219.0 - tempX + 2.0, 256.0 - tempZ + 2.0,  0.0);
		glVertex3f(219.0 - tempX - 2.0, 256.0 - tempZ + 2.0, 0.0);
	glEnd();
	
	// display map
	glBindTexture(GL_TEXTURE_2D, tempImage);
	glCallList(448);

	// Reset Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Displays a welcome or exit screen
//--------------------------------------------------------------------------------------
void CameraMap::DisplayWelcomeScreen (const int & screenWidth, const int & screenHeight, 
									  const int & tempExit, const GLuint & tempImage)
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glScalef(1, -1, 1);
		
	// move to centre of screen
	//glTranslatef(screenWidth/2 -256.0, -screenHeight/2 -256.0, 0);
	glTranslatef(screenWidth/2 -512.0, -screenHeight/2 -384, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	glBindTexture(GL_TEXTURE_2D, tempImage);

	// display image
	glCallList(449);

	// Reset Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CameraMap::DisplayGameEntryScreen(const int & tempExit, const GLuint & tempImage, const char* str)
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 790, 490, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Draw-Text:
	glPushMatrix();
		DrawManager dm;
		dm.RenderString(510,50,GLUT_BITMAP_HELVETICA_18, (const char*) str);
	glPopMatrix();
	
	// display black screen / no texture (for the "crash") or the texture
	if (tempImage>0) 
		glBindTexture(GL_TEXTURE_2D, tempImage);
	else
		glBindTexture(GL_TEXTURE_2D, -1);
	// display image
	glCallList(450);
	
	// Reset Perspective Projection
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void CameraMap::DisplayNoExit (const int & screenWidth, const int & screenHeight, 
							   const GLuint & tempImage)
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glScalef(1, -1, 1);
	
	// move to centre of screen
	glTranslatef(screenWidth/2 -128.0, -screenHeight/2 -32.0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	// display sign
	glBindTexture(GL_TEXTURE_2D, tempImage);
	// display image
	glCallList(454);
	// Reset Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}