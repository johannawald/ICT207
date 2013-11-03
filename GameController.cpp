#include "LevelOneController.h"
#include "texturedPolygons.h"
#include "GameController.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "BushCourtController.h"
#include "DrawManager.h"
#include "Stairs.h"
#include <sstream>
#include "GameOverController.h"
#include <iostream>
#include "GameWinController.h"

int G_LEVELTIME = 100;
bool G_DEBUGCOLLISION = false;

const bool GameController::ObjectIsBox(const int pIndex) const
{
	for (int i = 0; i<5; i++)
		if (mBoxesCollisionIndex[i]==pIndex)
			return true;
	return false;
}

const bool GameController::ObjectIsBomb(const int pIndex) const
{
	return (pIndex==mBombIndex);
}

void Countdown(int counterStepTime)
{
	//if (mSoundOn)
	if (G_LEVELTIME>-5)
	{
		G_LEVELTIME -=1;
		glutTimerFunc(1000, *Countdown, 0); //static?
	}
}

GameController::GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture): 
	BasisGameController(pAudio, pModel, pTexture), c_mLostTime(-5), mSoundOn(true), mBombSoundPlaying(false), mLostAnimation(false)
{

	glutTimerFunc(1000, *Countdown, 0);
	mBoxesCollisionIndex = new int[3]; //dynamic for each level
	for (int i = 0; i<5; i++)
		mBoxesCollisionIndex[i] = -1;
}


void GameController::Init() 
{
	BasisGameController::Init();
	InitGameObjects();
	if (mSoundOn)
		GetAudio()->playSound(sBgMusic);




}

void GameController::InitGameObjects() 
{
}

int GameController::CheckCollision()
{	
	//collision with walls:
	int pIndexCollision = BasisGameController::CheckCollision();
	G_DEBUGCOLLISION = pIndexCollision>=0;
	return pIndexCollision;
}


void GameController::BeforeCollision(int pIndex, float pCollisionValue) //just for boxes
{
	if (ObjectIsBomb(pIndex))
	{
		StateMachine::setController(new GameWinController(GetAudio(), GetModel(), GetTexture()));
	}
	else if (ObjectIsBox(pIndex))
	{
		//should not collide
		bool Move = false;
		float factor = 1.0f;
		//if not collision
		int pCollisionIndex = -1;
	
		float CollisionValue = mCollision.Collisions(pIndex, pCollisionIndex, true);

		if (CollisionValue==0)
		{	
			BoundingBox bb;
			bb = mCamera.GetCameraBB();
			bb.Move(mCamera.GetposDiff()*factor);
			float CollisionValueMoved = mCollision.Collisions(bb, pCollisionIndex, true);

			if (CollisionValueMoved<pCollisionValue)
				Move = false;
			else 
				Move = true;
		}
		else 
		{
			BoundingBox bb;
			bb = mCollision.GetCollisionBox(pIndex);
			bb.Move(mCamera.GetposDiff()*factor);
			float CollisionValueMoved = mCollision.Collisions(bb, pCollisionIndex, true, pIndex);
			if (CollisionValueMoved<=CollisionValue) //pull
				Move = true;
		}
		if (Move)
		{
			Vector3D movement  = mCamera.GetposDiff()*factor;
			movement.y = 0;
			mCollision.MoveBoundingBox(pIndex, movement);
				//gameobject has to have the same index (collision) work with a map - ask ray
			MoveGameObject(pIndex,movement);
		}
	}
}


void GameController::Draw()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	mExplosion.draw();
	BasisGameController::Draw();
	glDisable(GL_CULL_FACE);
}

void GameController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!) //updated 29.10 *JM
{ 
	mExplosion.idle();
	if (G_LEVELTIME==3)
		mLostAnimation = true;
	else if (G_LEVELTIME==c_mLostTime)
		StateMachine::setController(new GameOverController(GetAudio(), GetModel(), GetTexture()));

	if (mLostAnimation && !mBombSoundPlaying)
	{
		GetAudio()->StopSound(sBgMusic);
		GetAudio()->playSound(sBomb);
		mBombSoundPlaying = true;
	}
	int index = -1;

}

void GameController::Reshape(int w, int h) 
{
	BasisGameController::Reshape(w,h);
}

//--------------------------------------------------------------------------------------
// Keyboard Functions
//--------------------------------------------------------------------------------------
void GameController::SpecialKey(int key, int x, int y) 
{
	if (!mLostAnimation)
		BasisGameController::SpecialKey(key, x, y);
}

//---------------------------------------------------------
void GameController::SpecialKeyUp(int key, int x, int y) 
{
	if (!mLostAnimation)
		BasisGameController::SpecialKeyUp(key, x, y);
}

void GameController::Keyboard(unsigned char key, int x, int y)
{
	SetNewExplosion(10,10,10);
	if (!mLostAnimation) 
	{
		BasisGameController::Keyboard(key, x, y);
	}
}

//--------------------------------------------------------------------------------------
void GameController::KeyboardUp(unsigned char key, int x, int y)
{
	if (!mLostAnimation) 
	{
		BasisGameController::KeyboardUp(key, x, y);
	}
}

void GameController::Mouse(int button, int state, int x, int y)
{
	if (!mLostAnimation) 
	{
		BasisGameController::Mouse(button, state, x, y);
	}
}

void GameController::PassiveMotion(int x, int y) //maybe we can delete that?
{
}

void GameController::MouseMotion(int x, int y)
{
	if (!mLostAnimation) 
	{
		BasisGameController::MouseMotion(x, y);
	}
}

void GameController::DrawObjects()
{

}

void GameController::DrawTimer()
{
	glPushAttrib(GL_CURRENT_BIT);
		glBindTexture(GL_TEXTURE_2D, -1);
		void *font;
		char s[255];

		GetDrawManager()->SetOrthographicProjection();

		glPushMatrix();
		glLoadIdentity();

		sprintf(s, "Time: %d", G_LEVELTIME); //get timer
		glColor3f(1.0, 0.0, 0.0);
		font = GLUT_BITMAP_TIMES_ROMAN_24;
		GetDrawManager()->RenderBitmapString(1.0,6.5,0.0,font, s); //display timer

		sprintf(s, "Camera x: %f y: %f z: %f", mCamera.Getpos().x, mCamera.Getpos().y, mCamera.Getpos().z); //get camera position
		glColor3f(1.0, 0.5, 0.5);
		font = GLUT_BITMAP_8_BY_13;
		GetDrawManager()->RenderBitmapString(1.0,10.5,0.0,font, s); //display camera position

		//Collision
		if (G_DEBUGCOLLISION)
		{
			sprintf(s, "Collision: %f new: %f", COLLISIONVALUE, NEW_COLLISIONVALUE); //get camera position
			glColor3f(1.0, 0.5, 0.5);
			font = GLUT_BITMAP_8_BY_13;
			GetDrawManager()->RenderBitmapString(1.0, 15.5, 0.0, font, s); //display camera position
		}

		glPopMatrix();

		GetDrawManager()->RestorePerspectiveProjection();
	glPopAttrib();
}

void GameController::SetNewExplosion(const float x, const float y, const float z)
{
	mExplosion.newExplosion(x,y,z);
}