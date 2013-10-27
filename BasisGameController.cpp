#include "BasisGameController.h"
#include "AudioManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include <iostream>
#include "GameObject.h"

BasisGameController::BasisGameController(AudioManager* pAudiomanager, ModelManager* pModelmanager, TextureManager* pTexturemanager): 
	BasisController(pAudiomanager, pModelmanager, pTexturemanager)
{	
}

void BasisGameController::DrawGameObjects() 
{ 
	for (std::vector<GameObject*>::iterator it = mGameObject.begin(); it != mGameObject.end(); ++it) 
	{
		glPushMatrix();
			glTranslatef((*it)->GetXPosition(), (*it)->GetYPosition(), (*it)->GetZPosition());
			glScalef((*it)->GetXScale(), (*it)->GetXScale(), (*it)->GetXScale()); 
			if ((*it)->getModelIndex()>=0)
				GetModel()->drawModel((*it)->getModelIndex(), (*it)->getTextureIndex());
		glPopMatrix();
	}
}

void BasisGameController::MouseMotion(int x, int y)
{
	mCamera.MouseMotion(x, y);
}

void BasisGameController::SpecialKey(int key, int x, int y) 
{
	mCamera.SpecialKey(key,x,y);
}

void BasisGameController::SpecialKeyUp(int key, int x, int y) 
{
	mCamera.SpecialKeyUp(key, x, y);
}

void BasisGameController::Keyboard(unsigned char key, int x, int y)
{
	mCamera.Keyboard(key, x, y);
}

//--------------------------------------------------------------------------------------
void BasisGameController::KeyboardUp(unsigned char key, int x, int y)
{
	mCamera.KeyboardUp(key, x, y);
}

void BasisGameController::Mouse(int button, int state, int x, int y)
{
	mCamera.Mouse(button, state, x, y);
}

void BasisGameController::addCollisionGameObject(const Vector3D& pPosition, const Vector3D& pSize, const eModels pModel, const eTextures pTexture, int& pCollisionIndex)
//pSize.x - Width
//pSize.y - Height
//pSize.z - Depth
{
	pCollisionIndex = mCollision.addCollisionBox(Vector3D(pPosition.x, pPosition.y, pPosition.z - pSize.z), 
							   Vector3D(pPosition.x + pSize.x, pPosition.y + pPosition.y, pPosition.z));
	
	addGameObject(Vector3D(pPosition.x, pPosition.y, pPosition.z), Vector3D(0, 0, 0), Vector3D(1, 1, 1), pModel, pTexture, pCollisionIndex);
}

void BasisGameController::Draw()
{
	if (pLoaded) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();
			//Move camera:
			mCamera.PrepareMovement();
			CheckCollision();
			mCamera.MoveCamera();
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
				//Set camera position:
				mCamera.SetCameraPosition(-500, -250, 30, 0);
				mCollision.translateBoundingBoxes(Vector3D(-500, -250, 30));		
				mCollision.Draw(GetDrawManager());
				//translateGameObjects(-500, -250, 30); //do i need that
				DrawObjects();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void BasisGameController::addGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pScale, eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex)
{
	GameObject* gameobject = new GameObject(Vector3D(100,100,100), Vector3D(0, 0, 0), Vector3D(1, 1, 1), mBox, taBox, 0);
	mGameObject.push_back(gameobject);
}

int BasisGameController::CheckCollision()
{
	//Wallcollision
	int IndexCollision = -1;
	int mSizeController = 100;
	if (mCollision.Collision(Vector3D(mCamera.GetXpos(), mCamera.GetYpos(), mCamera.GetZpos()), IndexCollision, mSizeController))
	{
		BeforeCollision(IndexCollision);
		if (mCollision.Collision(Vector3D(mCamera.GetXpos()+mCamera.GetXposDiff(), 
						 mCamera.GetYpos()+mCamera.GetYposDiff(), 
						 mCamera.GetZpos()+mCamera.GetZposDiff()), IndexCollision, mSizeController))
			mCamera.SetDiffValues(0, 0, 0);
	}
	return IndexCollision;
}

void BasisGameController::BeforeCollision(int pIndex)
{
}

void BasisGameController::translateGameObjects(float x, float y, float z)
{ 
	for (std::vector<GameObject*>::iterator it = mGameObject.begin(); it != mGameObject.end(); ++it) 
	{
		(*it)->Transform(x,y,z);
	}
}