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

int levelTime = 120;
bool stopTimer = false;

void Countdown(int counterStepTime)
{
if (!stopTimer)
	{
		levelTime -=1;
		cout << "Timer: " << levelTime << "\n";
		glutTimerFunc(1000, *Countdown, 0);
	}
	else
		cout << "Timer stopped at " << levelTime << "\n";
}

GameController::GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture): 
		BasisGameController(pAudio, pModel, pTexture), mPush(false), mPull(false)
{
	SetGameObject();
	glutTimerFunc(1000, *Countdown, 0);

	mBoxesCollisionIndex = new int[5]; //dynamic for each level
}

void GameController::SetGameObject()
{

}

void GameController::Init() 
{
	BasisGameController::Init();
	InitGameObjects();
}

void GameController::InitGameObjects() 
{
	int cubeSize = 500; //pIndex
	addCollisionGameObject(Vector3D(1000,1000,1000), Vector3D(0,0,0), Vector3D(100, 100, 100), Vector3D(0.2f, 0.2f, 0.2f), mBox, taBox, mBoxesCollisionIndex[0]);
	addCollisionGameObject(Vector3D(1000,1500,1000), Vector3D(0,0,0), Vector3D(100, 100, 100), Vector3D(0.2f, 0.2f, 0.2f), mBox, taBox, mBoxesCollisionIndex[1]);
	

	//addCollisionGameObject(Vector3D(100,100,10), Vector3D(10,100,100), mBox, taBox, mBoxesCollisionIndex[1]);
	//addCollisionGameObject(Vector3D(200,200,10), Vector3D(10,100,100), mBox, taBox, mBoxesCollisionIndex[2]);
	//addCollisionGameObject(Vector3D(50,50,-100), Vector3D(10,100,100), mBox, taBox, mBoxesCollisionIndex[3]);
	//saddCollisionGameObject(Vector3D(100,150,100), Vector3D(1000,1000,1000), (eModels)-1, (eTextures)-1, mBoxesCollisionIndex[4]);
}

int GameController::CheckCollision()
{	
	//collision with walls:
	int pIndexCollision = BasisGameController::CheckCollision();
	/*if (pIndexCollision==0)		
	{	
		std::cout << "collision" << std::endl;
		if (mPush)
			PushBox(pIndexCollision);
		if (mPull)
			PullBox(pIndexCollision);
	}
	//here collision with objects */
	return pIndexCollision;
}

void GameController::BeforeCollision(int pIndex)
{
	//should not collide
	float factor = 3.0f;
	
	//if (mCamera.GetposDiff().x>0)
		mCollision.translateBoundingBoxOriginal(pIndex, mCamera.GetposDiff()*factor);
	//mCamera.SetPull(3);
	//mCollision.translateBoundingBoxOriginal(pIndex, Vector3D(mCamera.GetXposDiff()*factor, mCamera.GetYposDiff()*factor,  mCamera.GetZposDiff()*factor));
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
	BasisGameController::Draw();
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
	int index = -1;
	//if (mCollision.Collision(&mCamera.GetCameraBB(), &mCam)) //mCamera.Getpos(), index, 100))
	{ 
		//std::cout << "collision changed: " << std::endl;
	}
	if (levelTime<=0)
	{
		stopTimer = true;
		//StateMachine::setController(new GameOverController(GetAudio(), GetModel(), GetTexture()));
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
	BasisGameController::SpecialKey(key, x, y);
}

//---------------------------------------------------------
void GameController::SpecialKeyUp(int key, int x, int y) 
{
	BasisGameController::SpecialKeyUp(key, x, y);
}

void GameController::Keyboard(unsigned char key, int x, int y)
{
	BasisGameController::Keyboard(key, x, y);
	if (key=='p')
		mPush = true;
	else if (key=='o')
		mPull = true;
}

//--------------------------------------------------------------------------------------
void GameController::KeyboardUp(unsigned char key, int x, int y)
{
	BasisGameController::KeyboardUp(key, x, y);
	mPush = false;
	mPull = false;
}

void GameController::Mouse(int button, int state, int x, int y)
{
	BasisGameController::Mouse(button, state, x, y);
}

void GameController::PassiveMotion(int x, int y) //maybe we can delete that?
{
}

void GameController::MouseMotion(int x, int y)
{
	BasisGameController::MouseMotion(x, y);
}

//--------------------------------------------------------------------------------------
//  Draw the Objects
//--------------------------------------------------------------------------------------
void GameController::DrawObjects() 
{
	//that Push is important!
	glPushMatrix();
		DrawGameObjects();
		DrawTimer();
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
	glPushMatrix();
		glTranslatef(2000, 0, 3500);
		glScalef(0.75, 1.0, 0.75);
		GetModel()->drawModel(mBox, GetTexture()->getTextureID(taBox));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 750);
		glScalef(0.75, 1.0, 0.75);
		GetModel()->drawModel(mBox, GetTexture()->getTextureID(taBox));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(750, 500, 750);
		GetModel()->drawModel(mButton, GetTexture()->getTextureID(taButton));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 1250);
		GetModel()->drawModel(mButton, GetTexture()->getTextureID(taButton));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 4250);
		GetModel()->drawModel(mButton, GetTexture()->getTextureID(taButton));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(750, 500, 4250);
		GetModel()->drawModel(mButton, GetTexture()->getTextureID(taButton));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 0, 2500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(ta4x1platform));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2500, 0, 4250);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(ta4x1platform));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2250, 450, 1500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(ta4x1platform));
	glPopMatrix();	
}

//------------------------------------------------- -------------------------------------
//  Draw the Outer Walls
//--------------------------------------------------------------------------------------
void GameController::DrawOuterWalls()
{
	//floor
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glBegin(GL_QUADS);
		glTexCoord2f (5.0, 5.0);		glVertex3f(0, 0, 0);
		glTexCoord2f (0.0, 5.0);		glVertex3f(0, 0, 5000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 0,	5000);
		glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 0, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glBegin(GL_QUADS);
		glTexCoord2f (5.0, 5.0);		glVertex3f(0, 2000,	0);
		glTexCoord2f (0.0, 5.0);		glVertex3f(0, 2000, 5000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 2000, 5000);
		glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 2000, 0);
	glEnd();

	//walls
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilewall));
	glBegin(GL_QUADS);
		glTexCoord2f (10.0, 1.0);		glVertex3f(0, 0, 0);
		glTexCoord2f (0.0, 1.0);		glVertex3f(0, 0, 5000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(0, 1000, 5000);
		glTexCoord2f (10.0, 0.0);		glVertex3f(0, 1000,	0);
	glEnd();
		
	glBegin(GL_QUADS);
		glTexCoord2f (10.0, 1.0);		glVertex3f(0, 0, 5000);
		glTexCoord2f (0.0, 1.0);		glVertex3f(5000, 0, 5000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 1000, 5000);
		glTexCoord2f (10.0, 0.0);		glVertex3f(0, 1000, 5000);
	glEnd();
		
	glBegin(GL_QUADS);
		glTexCoord2f(10.0, 1.0);		glVertex3f(5000, 0, 5000);
		glTexCoord2f (0.0, 1.0);		glVertex3f(5000, 0, 0);
		glTexCoord2f(0.0, 0.0);			glVertex3f(5000, 1000, 0);
		glTexCoord2f(10.0, 0.0);		glVertex3f(5000, 1000, 5000);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(10.0, 1.0);		glVertex3f(5000, 0, 0);
		glTexCoord2f(0.0, 1.0);			glVertex3f(0, 0, 0);
		glTexCoord2f(0.0, 0.0);			glVertex3f(0, 1000, 0);
		glTexCoord2f(10.0, 0.0);		glVertex3f(5000, 1000, 0);
	glEnd();

	//2nd story walls
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall));
	glBegin(GL_QUADS);
		glTexCoord2f (10.0, 1.0);		glVertex3f(0, 1000, 0);
		glTexCoord2f (0.0, 1.0);		glVertex3f(0, 1000, 5000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(0, 2000, 5000);
		glTexCoord2f (10.0, 0.0);		glVertex3f(0, 2000,	0);
	glEnd();
		
	glBegin(GL_QUADS);
		glTexCoord2f (10.0, 1.0);		glVertex3f(0, 1000, 5000);
		glTexCoord2f (0.0, 1.0);		glVertex3f(5000, 1000, 5000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 2000, 5000);
		glTexCoord2f (10.0, 0.0);		glVertex3f(0, 2000, 5000);
	glEnd();
	
	glBegin(GL_QUADS);
		glTexCoord2f(10.0, 1.0);		glVertex3f(5000, 1000, 5000);
		glTexCoord2f (0.0, 1.0);		glVertex3f(5000, 1000, 0);
		glTexCoord2f(0.0, 0.0);			glVertex3f(5000, 2000, 0);
		glTexCoord2f(10.0, 0.0);		glVertex3f(5000, 2000, 5000);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(10.0, 1.0);		glVertex3f(5000, 1000, 0);
		glTexCoord2f(0.0, 1.0);			glVertex3f(0, 1000, 0);
		glTexCoord2f(0.0, 0.0);			glVertex3f(0, 2000, 0);
		glTexCoord2f(10.0, 0.0);		glVertex3f(5000, 2000, 0);
	glEnd();
}

//--------------------------------------------------------------------------------------
//  Draw the Level Architecture
//--------------------------------------------------------------------------------------
void GameController::DrawArchitecture()
{
	//solid platform tops
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor)); 
		glBegin(GL_QUADS);
			glTexCoord2f (1.5, 1.5);		glVertex3f(0, 500, 0);
			glTexCoord2f (0.0, 1.5);		glVertex3f(0, 500, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 1500);
			glTexCoord2f (1.5, 0.0);		glVertex3f(1500, 500, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (0.5, 1.5);		glVertex3f(2000, 500, 0);
			glTexCoord2f (0.0, 1.5);		glVertex3f(2000, 500, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(3500, 500, 500);
			glTexCoord2f (0.5, 0.0);		glVertex3f(3500, 500, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.5, 1.5);		glVertex3f(3500, 500, 0);
			glTexCoord2f (0.0, 1.5);		glVertex3f(3500, 500, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 500, 1500);
			glTexCoord2f (1.5, 0.0);		glVertex3f(5000, 500, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.5, 1.5);		glVertex3f(3500, 500, 3500);
			glTexCoord2f (0.0, 1.5);		glVertex3f(3500, 500, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 500, 5000);
			glTexCoord2f (1.5, 0.0);		glVertex3f(5000, 500, 3500);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.5, 1.5);		glVertex3f(0, 500, 3500);
			glTexCoord2f (0.0, 1.5);		glVertex3f(0, 500, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 5000);
			glTexCoord2f (1.5, 0.0);		glVertex3f(1500, 500, 3500);
		glEnd();

		//platform sides
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall));
		glBegin(GL_QUADS);
			glTexCoord2f (4.0, 0.25);		glVertex3f(1500, 0, 500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(3500, 0, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(3500, 500, 500);
			glTexCoord2f (4.0, 0.0);		glVertex3f(1500, 500, 500);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(3500, 0, 1500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(5000, 0, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 500, 1500);
			glTexCoord2f (3.0, 0.0);		glVertex3f(3500, 500, 1500);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(3500, 0, 500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(3500, 0, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(3500, 500, 1500);
			glTexCoord2f (3.0, 0.0);		glVertex3f(3500, 500, 500);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(1500, 0, 500);
			glTexCoord2f (0.0, 4.0);		glVertex3f(1500, 500, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 1000);
			glTexCoord2f (1.0, 0.0);		glVertex3f(1500, 0, 1000);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(3500, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(5000, 0, 3500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 500, 3500);
			glTexCoord2f (3.0, 0.0);		glVertex3f(3500, 500, 3500);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(3500, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(3500, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(3500, 500, 5000);
			glTexCoord2f (3.0, 0.0);		glVertex3f(3500, 500, 3500);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(0, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(1500, 0, 3500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 3500);
			glTexCoord2f (3.0, 0.0);		glVertex3f(0, 500, 3500);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(1500, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(1500, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 5000);
			glTexCoord2f (3.0, 0.0);		glVertex3f(1500, 500, 3500);
		glEnd();

		//high inside walls - lowersection
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall));
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(1500, 500, 0);
			glTexCoord2f (0.0, 4.0);		glVertex3f(1500, 500, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 2000, 500);
			glTexCoord2f (1.0, 0.0);		glVertex3f(1500, 2000, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(2000, 500, 500);
			glTexCoord2f (0.0, 4.0);		glVertex3f(1500, 500, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 2000, 500);
			glTexCoord2f (1.0, 0.0);		glVertex3f(2000, 2000, 500);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(2000, 500, 0);
			glTexCoord2f (0.0, 4.0);		glVertex3f(2000, 500, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(2000, 2000, 500);
			glTexCoord2f (1.0, 0.0);		glVertex3f(2000, 2000, 0);
		glEnd();

		//high inside walls - uppersection
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall));
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(1500, 0, 1000);
			glTexCoord2f (0.0, 4.0);		glVertex3f(1500, 0, 2000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 2000, 2000);
			glTexCoord2f (1.0, 0.0);		glVertex3f(1500, 2000, 1000);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(2000, 0, 2000);
			glTexCoord2f (0.0, 4.0);		glVertex3f(1500, 0, 2000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 2000, 2000);
			glTexCoord2f (1.0, 0.0);		glVertex3f(2000, 2000, 2000);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(2000, 0, 1000);
			glTexCoord2f (0.0, 4.0);		glVertex3f(2000, 0, 2000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(2000, 2000, 2000);
			glTexCoord2f (1.0, 0.0);		glVertex3f(2000, 2000, 1000);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.0, 4.0);		glVertex3f(1500, 0, 1000);
			glTexCoord2f (0.0, 4.0);		glVertex3f(2000, 0, 1000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(2000, 2000, 1000);
			glTexCoord2f (1.0, 0.0);		glVertex3f(1500, 2000, 1000);
		glEnd();

	 //stairs
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor)); 

	glPushMatrix();
		glTranslatef(0, 0, 2000);
		GetDrawManager()->DrawStairs(500, 500, -500, 5);
		glTranslatef(500, 0, 0);
		GetDrawManager()->DrawStairs(500, 500, -500, 5);
		glTranslatef(500, 0, 0);
		GetDrawManager()->DrawStairs(500, 500, -500, 5);
	glPopMatrix();

	
	glPushMatrix(); //more stairs!
		glTranslatef(1500, 0, 2000);
		glRotatef(270, 0, 1, 0);
		GetDrawManager()->DrawStairs(500, 500, -500, 5);
	glPopMatrix();
}


void GameController::DrawTimer()
{
	glBindTexture(GL_TEXTURE_2D, -1);
	void *font;
	char s[255];

	SetOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();

	sprintf(s, "Time Remaining: %d", levelTime); //get timer
	glColor3f(1.0, 0.0, 0.0);
	font = GLUT_BITMAP_TIMES_ROMAN_24;
	RenderBitmapString(1.0,6.5,0.0,font, s); //display timer

	sprintf(s, "Camera x: %f y: %f z: %f", mCamera.Getpos().x, mCamera.Getpos().y, mCamera.Getpos().z); //get camera position
	glColor3f(1.0, 0.5, 0.5);
	font = GLUT_BITMAP_8_BY_13;
	RenderBitmapString(1.0,10.5,0.0,font, s); //display camera position

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