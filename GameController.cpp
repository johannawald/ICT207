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

int levelTime = 60;

void Countdown(int counterStepTime)
{
	levelTime -=1;
	cout << "Timer: " << levelTime << "\n";
	glutTimerFunc(1000, *Countdown, 0);
}

GameController::GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture): 
		BasisGameController(pAudio, pModel, pTexture)
{
	SetGameObject();
	glutTimerFunc(1000, *Countdown, 0);
}

void GameController::SetGameObject()
{

}

void GameController::Init() 
{
	BasisGameController::Init();
	int cubeSize = 200;
	mCollision.addCollisionBox(100, 100, 100-cubeSize, 100+cubeSize, 100+cubeSize, 100);
	InitGameObjects();
}

void GameController::InitGameObjects() 
{
	addGameObject(Vector3D(100,100,100), Vector3D(0, 0, 0), Vector3D(10, 10, 10), mBox, taBox, 0);
}

void GameController::CheckCollision()
{	
	//collision with walls:
	BasisGameController::CheckCollision();
	//here collision with objects 
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

void GameController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!)
{ 
	int index = -1;
	if (mCollision.Collision(mCamera.GetXpos(), mCamera.GetYpos(), mCamera.GetZpos(), index, 100))
	{ 
		std::cout << "collision changed: " << std::endl;
	}
	if (levelTime<=0)
		StateMachine::setController(new GameOverController(GetAudio(), GetModel(), GetTexture()));
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
}

//--------------------------------------------------------------------------------------
void GameController::KeyboardUp(unsigned char key, int x, int y)
{
	BasisGameController::KeyboardUp(key, x, y);
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
