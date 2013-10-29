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
	mCollision.addCollisionBox(Vector3D(2000, 2000, 2000), Vector3D(200, 200, 600));
	/*mCollision.addCollisionBox(Vector3D(1000, 1000, 1000), Vector3D(2000, 2000, 60));
	mCollision.addCollisionBox(Vector3D(2000, 1200, 1200), Vector3D(250, 20, 60));
	mCollision.addCollisionBox(Vector3D(100, 2000, 1300), Vector3D(250, 100, 600));
	mCollision.addCollisionBox(Vector3D(10000, 20000, 3000), Vector3D(-250, -100, -600));
	mCollision.addCollisionBox(Vector3D(1000, 20000, 3000), Vector3D(-250, -100, 600));*/
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
	
	//addGameObject(Vector3D(pPosition.x, pPosition.y, pPosition.z), Vector3D(0, 0, 0), Vector3D(1, 1, 1), pModel, pTexture, pCollisionIndex);
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
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
				//Set camera position:
				mCamera.SetCameraPosition();
				//mCollision.translateBoundingBoxes(); //Vector3D(-500, -250, 30));		
				mCollision.Draw(GetDrawManager());
				translateGameObjects(0, 0, 0); //do i need that
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

void BasisGameController::WallCollision(int pIndex)
{

		std::cout << "collision" << std::endl;
		BoundingBox* bb = new BoundingBox();
		bb = mCamera.GetCameraBB();
		bb->Translate(mCamera.GetposDiff());

		if (mCollision.Collisions(bb, pIndex))
			mCamera.SetDiffValues(0, mCamera.GetposDiff().y, 0); //not sure if we need that

		//mCamera.GetposDiff();
		//BoundingBox* bb = mCamera.GetCameraBB();
		//bb->Translate(mCamera.GetposDiff());
		//if (mCollision.Collision(bb, IndexCollision)) 
		//std::cout << " - test - " << std::endl;
		//mCamera.SetDiffValues(0, 0, 0);
}

int BasisGameController::CheckCollision()
{	
	int IndexCollision = -1;
	int mSizeController = 100;
	if (mCollision.Collisions(mCamera.GetCameraBB(), IndexCollision)) //IndexCollisions should be a list with all the IDs of objects that collided
	{
		BeforeCollision(IndexCollision); //list!!
		WallCollision(IndexCollision); //Wallcollision
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