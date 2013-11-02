//  @ File Name : DrawManager.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//

#include "DrawManager.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "CollisionDetection.h"
#include "BoundingBox.h"
#include "Vector3D.h"

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
				const int TexCoordX, const int TexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pDepth, const GLdouble pHeight) const
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, pTexture);
	if (pWidth == 0)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(TexCoordX, TexCoordY);		glVertex3f(pPositionX, pPositionY, pPositionZ);
			glTexCoord2f (0.0, TexCoordY);			glVertex3f(pPositionX, pPositionY, pPositionZ+pDepth);
			glTexCoord2f (0.0, 0.0);				glVertex3f(pPositionX, pPositionY+pHeight, pPositionZ+pDepth);
			glTexCoord2f (TexCoordX, 0.0);			glVertex3f(pPositionX, pPositionY+pHeight, pPositionZ);
		glEnd();
	}
	else if (pDepth == 0)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(TexCoordX, TexCoordY);		glVertex3f(pPositionX, pPositionY, pPositionZ);
			glTexCoord2f (0.0, TexCoordY);			glVertex3f(pPositionX+pWidth, pPositionY, pPositionZ);
			glTexCoord2f (0.0, 0.0);				glVertex3f(pPositionX+pWidth, pPositionY+pHeight, pPositionZ);
			glTexCoord2f (TexCoordX, 0.0);			glVertex3f(pPositionX, pPositionY+pHeight, pPositionZ);
		glEnd();
	}
	else if (pHeight == 0)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(TexCoordX, TexCoordY);		glVertex3f(pPositionX, pPositionY, pPositionZ);
			glTexCoord2f (0.0, TexCoordY);			glVertex3f(pPositionX, pPositionY, pPositionZ+pDepth);
			glTexCoord2f (0.0, 0.0);				glVertex3f(pPositionX+pWidth, pPositionY, pPositionZ+pDepth);
			glTexCoord2f (TexCoordX, 0.0);			glVertex3f(pPositionX+pWidth, pPositionY, pPositionZ);
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}

void DrawManager::DrawRect(const GLint pTexture, 
				const int TexCoordX, const int TexCoordY, 
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
						   const int pTexCoordX, const int pTexCoordY, 
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
				const int pTexCoordX, const int pTexCoordY, const Vector3D& pPosition, const Vector3D& pSize) const
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
				const int pTexCoordX, const int pTexCoordY, 
				const Vector3D& pPosition, 
				const GLdouble pWidth, const GLdouble pDepth, const GLdouble pHeight) const
{
	glPushMatrix();
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, pWidth, pDepth, pHeight);
		int width = pWidth;
		int height = pHeight;
		int depth = pDepth;
		
		if (width==0)
			width=10;
		if (height==0)
			height=10;
		if (depth==0)
			depth==10;

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