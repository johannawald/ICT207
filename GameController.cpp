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

int LevelTime = 6;
bool TimerSet = false;
bool G_DEBUGCOLLISION = false;

void GameController::SetLevelTime(const int pValue)
{
	LevelTime=pValue;
}

const bool GameController::ObjectIsBox(const int pIndex) const
{
	for (int i = 0; i<9; i++)
	{
		if (pIndex==mBoxesCollisionIndex[i])
		{
			return true;
			break;
		}
	}
	return false;
}

const bool GameController::ObjectIsBomb(const int pIndex) const
{
	return (pIndex==mBombIndex);
}

void Countdown(int counterStepTime)
{
	//if (mSoundOn)
	if (LevelTime>-5)
	{
		LevelTime -=1;
		glutTimerFunc(1000, *Countdown, 0);
	}
}

GameController::GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture, float pHeight, float pWidth): 
	BasisGameController(pAudio, pModel, pTexture, pHeight, pWidth), c_mLostTime(-5), mSoundOn(true), mBombSoundPlaying(false), mLostAnimation(false), mMaxLevels(3)
{
	LevelTime = 40;
	if (!TimerSet)
		glutTimerFunc(1000, *Countdown, 0);
	TimerSet = true;
	/*mBoxesCollisionIndex = new int[3]; //dynamic for each level
	for (int i = 0; i<5; i++)
		mBoxesCollisionIndex[i] = -1;*/
}

GameController::~GameController()
{
	/*for (int i = 0; i < 3; i++)
		delete mBoxesCollisionIndex;*/
}

void GameController::Init() 
{
	BasisGameController::Init();
	int G_LEVELTIME = 70;
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

void GameController::OnBeforeWin()
{
	if (mLevelNr==mMaxLevels)
		mNextState = new GameWinController(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth());
}

void GameController::BeforeCollision(int pIndex, float pCollisionValue)
{
	if (ObjectIsBomb(pIndex))
	{
		//Update XML file
		OnBeforeWin();
		
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
	BasisGameController::Draw();
	glDisable(GL_CULL_FACE);
}

void GameController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!) //updated 29.10 *JM
{ 
	mExplosion.Update();

	if (LevelTime==0)
	{
		mLostAnimation = true;
	}
	else if (LevelTime==c_mLostTime)
		mNextState = new GameOverController(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth());
	
	if (mLostAnimation && !mBombSoundPlaying)
	{
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
		if (LevelTime>0)
		{
			//sprintf(s, "Time: %d \nLevel %d of %d", LevelTime, mLevelNr+1, mMaxLevels+1); //get timer
			sprintf(s, "Time: %d", LevelTime); //get timer
			glColor3f(1.0, 0.0, 0.0);
			font = GLUT_BITMAP_TIMES_ROMAN_24;
			GetDrawManager()->RenderBitmapString(1.0,6.5,0.0,font, s); //display timer
			sprintf(s, "Level %d of %d",  mLevelNr+1, mMaxLevels+1);
			GetDrawManager()->RenderBitmapString(1.0,10.5,0.0,font, s);
		}

		glPopMatrix();

		GetDrawManager()->RestorePerspectiveProjection();
	glPopAttrib();
}

void GameController::SetNewExplosion(const float x, const float y, const float z)
{
	mExplosion.newExplosion(x,y,z);
}