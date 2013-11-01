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
		(*it)->Draw(*GetModel(), *GetDrawManager(), mCollision);
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

void BasisGameController::addCollisionGameObject(Vector3D& pPosition, Vector3D& pMovement, 
												Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation,
												int pModel, GLuint pTexture, int pTexCoordX, int pTexCoordY, int& pCollisionIndex, void (*pCollisionMethod)(void))
//pSize.x - Width
//pSize.y - Height
//pSize.z - Depth
{
	Vector3D min = pPosition;
	Vector3D max = pPosition;

	if (pModel>0)
	{
		max.x += pSize.x;
		max.y += pSize.y;
		max.z -= pSize.z;
	}
	else max += pSize;

	pCollisionIndex = mCollision.AddCollisionBox(min, max);	

	addGameObject(pPosition, pMovement, pSize, pScale, pRotation, pModel, pTexture, pTexCoordX, pTexCoordY, pCollisionIndex, pCollisionMethod);
}

void BasisGameController::Draw()
{
	if (pLoaded) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();
			gluLookAt(0, 400, 700.0, 
				0.0, 0.0, 0.0,
				0.0f, 1.0f, 0.0f);
			//Move camera:
			mCamera.PrepareMovement(0, 0, 0, 0);
			CheckCollision();
			mCamera.MoveCamera();
			//mCollision.translateBoundingBoxes(mCamera.Getpos()); //Vector3D(-500, -250, 30));		
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
				//Set camera position:
				mCamera.SetCameraPosition();
				mCollision.Draw(*GetDrawManager());
				DrawGameObjects();
				DrawObjects();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void BasisGameController::addGameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, int pModelIndex, GLuint pTextureIndex, int pTexCoordX, int pTexCoordY, int pCollisionIndex, void (*pCollisionMethod)(void))
{
	GameObject* gameobject = new GameObject(pPosition, pMovement, pSize, pScale, pRotation, pModelIndex, pTextureIndex, pTexCoordX, pTexCoordY, pCollisionIndex); //, pCollisionMethod, nullptr
	mGameObject.push_back(gameobject);
}

void BasisGameController::WallCollision(int pIndex, float pCollisionValue)
{
	BoundingBox bb;
	bb = *mCamera.GetCameraBB();
	bb.Translate(mCamera.GetposDiff());
	float ChangedCollisionValue = mCollision.Collisions(&bb, pIndex);
	//float ChangedCollisionValue = mCollision.Collisions(mCamera.GetCameraBB(), pIndex, false); 
								  //mCollision.Collisions(mCamera.GetCameraBB(), pIndex); 
	if (pCollisionValue>0)
	{
		if (ChangedCollisionValue>pCollisionValue)
			mCamera.SetDiffValues(0, 0, 0); //not sure if we need that
	}
}

void BasisGameController::PhysicCollision(int pIndex, float pCollisionValue)
{	
	//falling and stuff
	//mCamera.SetDiffValues(0, mCamera.GetposDiff().y, 0); //not sure if we need that
}

int BasisGameController::CheckCollision()
{	
	int IndexCollision = -1;
	int mSizeController = 100;
	float CollisionValue = mCollision.Collisions(mCamera.GetCameraBB(), IndexCollision); 
	if (CollisionValue>0) //IndexCollisions should be a list with all the IDs of objects that collided
	{
		BeforeCollision(IndexCollision, CollisionValue); //list!!
		WallCollision(IndexCollision, CollisionValue); //Wallcollision
		PhysicCollision(IndexCollision, CollisionValue);
	}
	return IndexCollision;
}

void BasisGameController::BeforeCollision(int pIndex, float pCollisionValue)
{
}

void BasisGameController::MoveGameObject(const int pIndex, const Vector3D& pTranslate)
{
	if (pIndex<mGameObject.size())
		mGameObject[pIndex]->Move(pTranslate);
}


GameObject* BasisGameController::GetGameObject(const int pIndex) const
{
	return mGameObject[pIndex];
}

void BasisGameController::translateGameObject(GameObject* gobj, const Vector3D& pTranslation)
{
	 gobj->Transform(pTranslation);
}

void BasisGameController::translateGameObjects(const Vector3D& pTranslation)
{ 
	for (std::vector<GameObject*>::iterator it = mGameObject.begin(); it != mGameObject.end(); ++it) 
	{
		translateGameObject((*it), pTranslation);
	}
}