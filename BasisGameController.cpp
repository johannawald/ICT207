#include "BasisGameController.h"
#include "AudioManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include <iostream>

BasisGameController::BasisGameController(AudioManager* pAudiomanager, ModelManager* pModelmanager, TextureManager* pTexturemanager): 
	BasisController(pAudiomanager, pModelmanager, pTexturemanager)
{	
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
				mCamera.SetCameraPosition(-500, -250, 3000, 0);
				mCollision.translateBoundingBoxes(-500, -250, 3000);		
				DrawObjects();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void BasisGameController::CheckCollision()
{
	//Wallcollision
	int IndexCollision = -1;
	int mSizeController = 100;
	if (mCollision.Collision(mCamera.GetXpos(), mCamera.GetYpos(), mCamera.GetZpos(), IndexCollision, mSizeController))
	{
		std::cout << "collision" << std::endl;

		if (mCollision.Collision(mCamera.GetXpos()+mCamera.GetXposDiff(), 
						 mCamera.GetYpos()+mCamera.GetYposDiff(), 
						 mCamera.GetZpos()+mCamera.GetZposDiff(), IndexCollision, mSizeController))
			mCamera.SetDiffValues(0, 0, 0);
	}
}