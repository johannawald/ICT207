//  @ File Name : DrawManager.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// 02/11/2013 Johanna Wald, added some Push/Pop Attribues

#include "DrawManager.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "CollisionDetection.h"
#include "BoundingBox.h"
#include "Vector3D.h"
#include <iostream>

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

void DrawManager::DrawStairs(const float pStairWidth, const float pStairHeight, const float pStairDepth, const float pNumSteps) const
{
	mStairs.DrawStairs(pStairWidth, pStairHeight, pStairDepth, pNumSteps);
}

void DrawManager::DrawRect(const GLint pTexture, 
				const float TexCoordX, const float TexCoordY, 
				const Vector3D& pPosition,
				const Vector3D& pSize) const
{
	//pSize.x = width
	//pSize.y = height
	//pSize.z = depth
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pTexture);
	if (pSize.x <= 10 && pSize.x >= 0)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(TexCoordX, TexCoordY);		glVertex3f(pPosition.x,		pPosition.y,			pPosition.z);
			glTexCoord2f (0.0, TexCoordY);			glVertex3f(pPosition.x,		pPosition.y,			pPosition.z+pSize.z);
			glTexCoord2f (0.0, 0.0);				glVertex3f(pPosition.x,		pPosition.y + pSize.y,	pPosition.z+pSize.z);
			glTexCoord2f (TexCoordX, 0.0);			glVertex3f(pPosition.x,		pPosition.y + pSize.y,	pPosition.z);
		glEnd();
	}
	else if (pSize.y <= 10 && pSize.y >= 0)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.0, 0.0);				glVertex3f(pPosition.x,				pPosition.y,		pPosition.z);
			glTexCoord2f (0.0, TexCoordY);			glVertex3f(pPosition.x,				pPosition.y,		pPosition.z + pSize.z);
			glTexCoord2f (TexCoordX, TexCoordY);	glVertex3f(pPosition.x + pSize.x,	pPosition.y,		pPosition.z + pSize.z);
			glTexCoord2f (TexCoordX, 0.0);			glVertex3f(pPosition.x + pSize.x,	pPosition.y,		pPosition.z);
			
		glEnd();
	}
	else if (pSize.z <= 10)
	{

			glBegin(GL_QUADS);
				glTexCoord2f (TexCoordX, TexCoordY);	glVertex3f(pPosition.x,				pPosition.y,				pPosition.z);
				glTexCoord2f (0.0, TexCoordY);			glVertex3f(pPosition.x + pSize.x,	pPosition.y,				pPosition.z);
				glTexCoord2f (0.0, 0.0);				glVertex3f(pPosition.x + pSize.x,	pPosition.y + pSize.y,		pPosition.z);
				glTexCoord2f (TexCoordX, 0.0);			glVertex3f(pPosition.x,				pPosition.y + pSize.y,		pPosition.z);
			glEnd();			
		}
	glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}

void DrawManager::DrawRect(const GLint pTexture, 
				const float TexCoordX, const float TexCoordY, 
				const Vector3D& pPosition, 
				const GLdouble pWidth, const GLdouble pHeight, 
				const Vector3D& pAngle) const
{
	glPushMatrix();
		glTranslatef(pPosition.x, pPosition.y, pPosition.z);
		glRotatef(pAngle.x,1,0,0);
		glRotatef(pAngle.y,0,1,0);
		glRotatef(pAngle.z,0,0,1);
		glTranslatef(-pPosition.x, -pPosition.y, -pPosition.z);
	glPopMatrix();
}

void DrawManager::DrawCube(const GLint pTexture, 
						   const float pTexCoordX, const float pTexCoordY, 
						   const Vector3D& pPosition, 
						   const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth) const
{	
	glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
			glBindTexture(GL_TEXTURE_2D, -1);
			DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition, pDepth, pHeight, Vector3D(0, 90, 0));
			glTranslatef(pWidth,0,-pDepth);
			DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition, pDepth, pHeight, Vector3D(0, 270, 0));
			glTranslatef(-pWidth,0,pDepth);
			DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition, pWidth, pDepth, Vector3D(-90, 0, 0));
			glTranslatef(0,pHeight,0);
			DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition, pWidth, pDepth, Vector3D(-90, 0, 0));
			glTranslatef(0,-pHeight,0);
		glPopAttrib();
	glPopMatrix();
}

void DrawManager::DrawCollisionCube(CollisionDetection* collision, const GLint pTexture, 
				const float pTexCoordX, const float pTexCoordY, const Vector3D& pPosition, const Vector3D& pSize) const
{
	glPushMatrix();
		DrawCube(pTexture, pTexCoordX, pTexCoordY, pPosition, pSize.x, pSize.y, pSize.z);
		Vector3D position = pPosition;
		position.z -= pSize.z;
		Vector3D size(pPosition.x+pSize.x, pPosition.y+pSize.y, pPosition.z);
		collision->AddCollisionBox(position, size);
	glPopAttrib();
}

void DrawManager::DrawCollisionRect(CollisionDetection* collision, const GLint pTexture, 
				const float pTexCoordX, const float pTexCoordY, 
				const Vector3D& pPosition, 
				const Vector3D& pSize) const
{
	glPushMatrix();
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition, pSize);
		float width = pSize.x;
		float height = pSize.y;
		float depth = pSize.z;
		
		if (width==0)
			width=10;
		if (height==0)
			height=10;
		if (depth==0)
			depth=10;

		collision->AddCollisionBox(Vector3D(pPosition.x, pPosition.y, pPosition.z), Vector3D(pPosition.x+width, pPosition.y+height, pPosition.z+depth));
	glPopAttrib();
}

void DrawManager::DrawCollisionBoxColored(const BoundingBox& pBoundingBox) const
{
	glBegin(GL_QUADS);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
    glEnd();

    glBegin(GL_QUADS);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMin().z);
    glEnd();

    glBegin(GL_QUADS);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMin().z);
    glEnd();
}

void DrawManager::DrawCollisionBox(const BoundingBox& pBoundingBox) const
{
    glBegin(GL_LINE_LOOP);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMin().z);
    glEnd();

    glBegin(GL_LINE_LOOP);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
    glEnd();

    glBegin(GL_LINE_LOOP);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMax().y,pBoundingBox.GetMin().z);
    glEnd();

    glBegin(GL_LINE_LOOP);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMax().z);
		glVertex3f(pBoundingBox.GetMin().x,pBoundingBox.GetMin().y,pBoundingBox.GetMin().z);
		glVertex3f(pBoundingBox.GetMax().x,pBoundingBox.GetMin().y,pBoundingBox.GetMin().z);
    glEnd();
}


void DrawManager::RenderBitmapString(const float x, const float y, const float z, void *pFont, const char *pString) const 
{
	const char *c;

	glRasterPos3f(x, y, z);

	for (c=pString; *c != '\0'; c++) 
	{
		glutBitmapCharacter(pFont, *c);
	}
}


void DrawManager::RenderStrokeFontString(const float x, const float y, const float z, void *pFont, const char *pString) const 
{
	const char *c;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.002f, 0.002f, 0.002f);

	for(c=pString; *c != '\0'; c++) 
	{
		glutStrokeCharacter(pFont, *c);
	}
	glPopMatrix();
}


void DrawManager::SetOrthographicProjection() const 
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void DrawManager::RestorePerspectiveProjection() const 
{
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}