#include "BasisController.h"
#include "DrawManager.h"
#include "AudioManager.h"

BasisController::BasisController(AudioManager* pAudioManager, ModelManager* pModelManager, TextureManager* pTextureManager): 
	mAudioManager(pAudioManager), mModelManager(pModelManager), mTextureManager(pTextureManager), pLoaded(false), mScreenWidth(1024), mScreenHeight(1024)
{	
	mDrawManager = new DrawManager();
	Init();
	pLoaded = true;	
}

void BasisController::Reshape(int pWidth, int pHeight) 
{
	mScreenWidth = pWidth;
	mScreenHeight = pHeight;
	// Prevent a divide by zero, when window is too short		
	// (you cant make a window of zero width).
	if (pHeight== 0) 
		pHeight = 1;
	mRatio = 1.0f * pWidth / pHeight;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, pWidth, pHeight);
	gluPerspective(45,mRatio,1,250000);	
	glMatrixMode(GL_MODELVIEW);
}

void BasisController::Draw()
{
	if (pLoaded) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();


			glLoadIdentity();
			//Move camera:
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();	
				DrawObjects();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void BasisController::Reshape()
{
	Reshape(mScreenWidth, mScreenHeight);
}

void BasisController::Init()
{
	glClearColor(0, 0, 0, 0);
	
	glEnable(GL_DEPTH_TEST); 
	glShadeModel(GL_SMOOTH);
	Reshape();
}

AudioManager* BasisController::GetAudio() const
{	
	return mAudioManager;
}

ModelManager* BasisController::GetModel() const
{	
	return mModelManager;
}

TextureManager* BasisController::GetTexture() const
{	
	return mTextureManager;
}

DrawManager* BasisController::GetDrawManager()
{	
	return mDrawManager;
}


const int BasisController::GetWindowWidth() const
{
	return mScreenWidth;
}

const int BasisController::GetWindowHeight() const
{
	return mScreenHeight;
}