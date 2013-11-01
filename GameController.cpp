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

int levelTime = 100;
//bool stopTimer = false;
bool DebugCollision = false;

void Countdown(int counterStepTime)
{
	//if (mSoundOn)
	if (levelTime>-5)
	{
		levelTime -=1;
		glutTimerFunc(1000, *Countdown, 0); //static?
	}
}

GameController::GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture): 
	BasisGameController(pAudio, pModel, pTexture), mGround(-65), mPush(false), mPull(false), mSoundOn(true), mLost(false), mBombSoundPlaying(false), mLostAnimation(false)
{
	SetGameObject();
	glutTimerFunc(1000, *Countdown, 0);
	mBoxesCollisionIndex = new int[5]; //dynamic for each level
	for (int i = 0; i<5; i++)
		mBoxesCollisionIndex[i] = -1;
	//mExplosion.mSpeed = 10;
}

void GameController::SetGameObject()
{

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
	if (pIndexCollision>=0)		
	{	
		DebugCollision = true;
		if (mPush)
			PushBox(pIndexCollision);
		if (mPull)
			PullBox(pIndexCollision);
	}
	else DebugCollision = false;
	return pIndexCollision;
}

bool GameController::ObjectIsBox(const int pIndex) const
{
	for (int i = 0; i<5; i++)
		if (mBoxesCollisionIndex[i]==pIndex)
			return true;
	return false;
}

void GameController::WinGame() const
{
	StateMachine::setController(new GameWinController(GetAudio(), GetModel(), GetTexture()));
}

void GameController::BeforeCollision(int pIndex, float pCollisionValue) //just for boxes
{

	if (ObjectIsBox(pIndex))
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
			bb = *mCamera.GetCameraBB();
			bb.Translate(mCamera.GetposDiff()*factor);
			//collision of moved camera:
			float CollisionValueMoved = mCollision.Collisions(&bb, pCollisionIndex, true);

			if (CollisionValueMoved<=pCollisionValue)
				Move = false;
			else 
				Move = true;
		}
		else 
		{
			BoundingBox bb;
			bb = mCollision.GetCollisionBox(pIndex);
			bb.Translate(mCamera.GetposDiff()*factor);
			float CollisionValueMoved = mCollision.Collisions(&bb, pCollisionIndex, true, pIndex);
			if (CollisionValueMoved<=CollisionValue) //pull
				Move = true;
		}
		//Move = true;
		if (Move)
		{
			Vector3D movement  = mCamera.GetposDiff()*factor;
			movement.y = 0;
			mCollision.translateBoundingBoxOriginal(pIndex, movement);
				//gameobject has to have the same index (collision) work with a map - ask ray
			MoveGameObject(pIndex,movement);
		}
	}
}

void GameController::PushBox(int pIndex)
{
	
	//std::cout << "Ausgabe " << std::endl;
}

void GameController::PullBox(int pIndex)
{
	
	//std::cout << "Ausgabe " << std::endl;
}


void GameController::Draw()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//mExplosion.draw();
	BasisGameController::Draw();
	glDisable(GL_CULL_FACE);
}

void GameController::CollisionWithObject(GameObject* pGameObject)
{ 

}

void GameController::DrawTexttest()
{ 
	//Draw Infos in corner (Timer) here
}

void GameController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!) //updated 29.10 *JM
{ 
	//mExplosion.idle();
	if (levelTime==3)
		mLostAnimation = true;
	else if (levelTime==-5)
		mLost = true;

	if (mLostAnimation && !mBombSoundPlaying)
	{
		GetAudio()->playSound(sBomb);
		mBombSoundPlaying = true;
	}
	int index = -1;

	if (mLost) //*JW animation
	{
		StateMachine::setController(new GameOverController(GetAudio(), GetModel(), GetTexture()));
	}
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
	SetNewExplosion(0,0,0);
	if (!mLostAnimation) 
	{
		BasisGameController::Keyboard(key, x, y);
		if (key=='p')
			mPush = true;
		else if (key=='o')
			mPull = true;
	}
}

//--------------------------------------------------------------------------------------
void GameController::KeyboardUp(unsigned char key, int x, int y)
{
	if (!mLostAnimation) 
	{
		BasisGameController::KeyboardUp(key, x, y);
		mPush = false;
		mPull = false;
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

//--------------------------------------------------------------------------------------
//  Draw the Objects
//--------------------------------------------------------------------------------------
void GameController::DrawObjects() 
{
	//that Push is important!
	glPushMatrix();
		
		//DrawTimer();
		//Draw objects
		//Draw3DModels();
		//DrawOuterWalls();
		//DrawArchitecture();
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Draw the 3D Models
//--------------------------------------------------------------------------------------
void GameController::Draw3DModels()
{
	
}

//------------------------------------------------- -------------------------------------
//  Draw the Outer Walls
//--------------------------------------------------------------------------------------
void GameController::DrawOuterWalls()
{
	
}

//--------------------------------------------------------------------------------------
//  Draw the Level Architecture
//--------------------------------------------------------------------------------------
void GameController::DrawArchitecture()
{

}


void GameController::DrawTimer()
{
	glBindTexture(GL_TEXTURE_2D, -1);
	void *font;
	char s[255];

	SetOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();

	sprintf(s, "Time: %d", levelTime); //get timer
	glColor3f(1.0, 0.0, 0.0);
	font = GLUT_BITMAP_TIMES_ROMAN_24;
	RenderBitmapString(1.0,6.5,0.0,font, s); //display timer

	sprintf(s, "Camera x: %f y: %f z: %f", mCamera.Getpos().x, mCamera.Getpos().y, mCamera.Getpos().z); //get camera position
	glColor3f(1.0, 0.5, 0.5);
	font = GLUT_BITMAP_8_BY_13;
	RenderBitmapString(1.0,10.5,0.0,font, s); //display camera position

	sprintf(s, "Time: %d", levelTime); //get timer
	glColor3f(1.0, 0.0, 0.0);
	font = GLUT_BITMAP_TIMES_ROMAN_24;
	RenderBitmapString(1.0,6.5,0.0,font, s); //display timer

	//Collision
	if (DebugCollision)
	{
		sprintf(s, "Collision", mCamera.Getpos().x, mCamera.Getpos().y, mCamera.Getpos().z); //get camera position
		glColor3f(1.0, 0.5, 0.5);
		font = GLUT_BITMAP_8_BY_13;
		RenderBitmapString(1.0, 15.5, 0.0, font, s); //display camera position
	}

	glPopMatrix();

	RestorePerspectiveProjection();
}


void GameController::RenderBitmapString(float x, float y, float z, void *font, char *string) 
{
	char *c;

	glRasterPos3f(x, y, z);

	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}
}


void GameController::RenderStrokeFontString(float x, float y, float z, void *font, char *string) 
{
	char *c;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.002f, 0.002f, 0.002f);

	for(c=string; *c != '\0'; c++) 
	{
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}


void GameController::SetOrthographicProjection()
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


void GameController::RestorePerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void GameController::SetNewExplosion(const float x, const float y, const float z)
{
	//mExplosion.newExplosion(x,y,z);
}