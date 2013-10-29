#include "BasisGameController.h"
#include "AudioManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include <iostream>
#include "GameObject.h"
#include "BoundingBox.h"

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

void BasisGameController::addCollisionGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, eModels pModel, eTextures pTexture, int& pCollisionIndex)
//pSize.x - Width
//pSize.y - Height
//pSize.z - Depth
{
	Vector3D min = pPosition;
	Vector3D max = pPosition;
	max.x += pSize.x;
	max.y += pSize.y;
	max.z -= pSize.z;

	pCollisionIndex = mCollision.addCollisionBox(min, max);	
	addGameObject(pPosition, pMovement, pSize, pScale, pModel, pTexture, pCollisionIndex);
}

void BasisGameController::Draw()
{
	if (pLoaded) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();
			//Move camera:
			mCamera.PrepareMovement(0, 0, 0, 0);
			CheckCollision();
			mCamera.MoveCamera();
			//mCollision.translateBoundingBoxes(mCamera.Getpos()); //Vector3D(-500, -250, 30));		
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
				//Set camera position:
				mCamera.SetCameraPosition();
				mCollision.Draw(GetDrawManager());
				DrawObjects();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void BasisGameController::addGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex)
{
	GameObject* gameobject = new GameObject(pPosition, pMovement, pSize, pScale, pModelIndex, pTextureIndex, pCollisionIndex);
	mGameObject.push_back(gameobject);
}

void BasisGameController::WallCollision(int pIndex)
{
		std::cout << "collision" << std::endl;
		BoundingBox* bb = new BoundingBox();
		bb = mCamera.GetCameraBB();
		bb->Translate(mCamera.GetposDiff());

		if (mCollision.Collisions(bb, pIndex, false))
			mCamera.SetDiffValues(0, mCamera.GetposDiff().y, 0); //not sure if we need that

		//mCamera.GetposDiff();
		//BoundingBox* bb = mCamera.GetCameraBB();
		//bb->Translate(mCamera.GetposDiff());
		//if (mCollision.Collision(bb, IndexCollision)) 
		//std::cout << " - test - " << std::endl;
		//mCamera.SetDiffValues(0, 0, 0);
}

void BasisGameController::PhysicCollision(int pIndex)
{	
	//falling and stuff
	//mCamera.SetDiffValues(0, mCamera.GetposDiff().y, 0); //not sure if we need that
}

int BasisGameController::CheckCollision()
{	
	int IndexCollision = -1;
	int mSizeController = 100;
	if (mCollision.Collisions(mCamera.GetCameraBB(), IndexCollision)) //IndexCollisions should be a list with all the IDs of objects that collided
	{
		BeforeCollision(IndexCollision); //list!!
		WallCollision(IndexCollision); //Wallcollision
		PhysicCollision(IndexCollision);
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
		(*it)->Transform(Vector3D(x,y,z));
	}
}