//  @ File Name : DrawManager.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet


#include "DrawManager.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "CollisionDetection.h"
#include "BoundingBox.h"
#include "Vector3D.h"

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
	stairs.DrawStairs(stairWidth, stairHeight, stairDepth, numSteps);
}

void DrawManager::DrawRect(const GLint pTexture, 
				const int TexCoordX, const int TexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pDepth, const GLdouble pHeight ) const
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
		//DrawRect(pTexture, TexCoordX, TexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pHeight);
	glPopMatrix();
}

//johanna, change stair function

void DrawManager::DrawCube(const GLint pTexture, 
						   const int pTexCoordX, const int pTexCoordY, 
						   const Vector3D& pPosition, 
						   const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth) const
{	
	//z is reversed!
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glBindTexture(GL_TEXTURE_2D, -1);
		//glDisable(GL_LIGHTING);
	//	DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, 10, 10);
		//draw the front
		//glColor3f(0.3f, 0.0f, 0.0f);
	//	DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, pWidth, pHeight); 
		//draw the back
		//glColor3f(0.0f, 0.5f, 0.0f);
	//	DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z-pDepth, pWidth, pHeight);
		//draw the side
		//glColor3f(0.0f, 0.0f, 0.5f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, pDepth, pHeight, 0, 90, 0);
		glTranslatef(pWidth,0,-pDepth);
		//glColor3f(0.0f, 0.0f, 0.5f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, pDepth, pHeight, 0, 270, 0);
		glTranslatef(-pWidth,0,pDepth);
		//draw the top / bottom
		//glColor3f(0.5f, 0.5f, 0.0f);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, pWidth, pDepth, -90, 0, 0);
		glTranslatef(0,pHeight,0);
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPosition.x, pPosition.y, pPosition.z, pWidth, pDepth, -90, 0, 0);
		glTranslatef(0,-pHeight,0);
		//glEnable(GL_LIGHTING); 
	glPopAttrib();
	glPopMatrix();
}

void DrawManager::DrawCollisionCube(CollisionDetection* collision, const GLint pTexture, 
				const int pTexCoordX, const int pTexCoordY, 
				const Vector3D& pPosition,
				const Vector3D& pSize)
{
//pSize.x = Height
//pSize.y = Width
//pSize.z = Depth
	glPushMatrix();
		DrawCube(pTexture, pTexCoordX, pTexCoordY, pPosition, pSize.x, pSize.y, pSize.z);
		Vector3D position = pPosition;
		position.z -= pSize.z;
		Vector3D size(pPosition.x+pSize.x, pPosition.y+pSize.y, pPosition.z);
		collision->addCollisionBox(position, size);
	glPopAttrib();
}

void DrawManager::DrawCollisionRect(CollisionDetection* collision, const GLint pTexture, 
				const int pTexCoordX, const int pTexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pDepth, const GLdouble pHeight)
{
	glPushMatrix();
		DrawRect(pTexture, pTexCoordX, pTexCoordY, pPositionX, pPositionY, pPositionZ, pWidth, pDepth, pHeight);
		//collision->addCollisionBox(Vector3D(pPositionX, pPositionY, pPositionZ), Vector3D(pPositionX+pWidth, pPositionY+pHeight, pPositionZ+pDepth));
	glPopAttrib();
}

void DrawManager::DrawCollisionBoxColored(BoundingBox *b)
{
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMin().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMin().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMin().z);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMin().z);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMax().z);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMax().z);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMin().z);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMin().z);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMin().z);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMin().z);
    glEnd();

	glPopAttrib();
	glColor3f(0,1,0);
}

void DrawManager::DrawCollisionBox(BoundingBox *b)
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMin().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMin().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMin().z);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMin().z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMax().z);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMax().z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMin().z);
    glVertex3f(b->GetMax().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMax().y,b->GetMin().z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMax().z);
    glVertex3f(b->GetMin().x,b->GetMin().y,b->GetMin().z);
    glVertex3f(b->GetMax().x,b->GetMin().y,b->GetMin().z);
    glEnd();
	glColor3f(1,1,1);
	glPopAttrib();
	glColor3f(1,1,1);
}