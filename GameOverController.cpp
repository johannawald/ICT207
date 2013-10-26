#include "GameOverController.h"
#include "StateMachine.h"
#include "GameController.h"

GameOverController::GameOverController(AudioManager* am, ModelManager* mm, TextureManager* tm): 
	BasisController(am,mm,tm)
{
}

void GameOverController::Init() 
{	
	BasisController::Init();
}

void GameOverController::Draw()
{
	BasisController::Draw();
}

void GameOverController::DrawObjects()
{		
	glPushMatrix();
		//jon, Draw objects here
		glBegin(GL_QUADS);
			glColor3d(1,0,0);
			glVertex3f(-1,-1,-10);
			glColor3d(1,1,0);
			glVertex3f(1,-1,-10);
			glColor3d(1,1,1);
			glVertex3f(1,1,-10);
			glColor3d(0,1,1);
			glVertex3f(-1,1,-10);
		glEnd();
	glPopMatrix();
}

void GameOverController::Update()
{ 
}

void GameOverController::Reshape(int w, int h) {
	BasisController::Reshape(w, h);
}

void GameOverController::MouseMotion(int x, int y)
{
}

void GameOverController::SpecialKey(int key, int x, int y) 
{
}

void GameOverController::SpecialKeyUp(int key, int x, int y) 
{
}

void GameOverController::Keyboard(unsigned char key, int x, int y)
{
	if (key=='t') //press t to restart game
		StateMachine::setController(new GameController(GetAudio(), GetModel(), GetTexture()));
}

//--------------------------------------------------------------------------------------
void GameOverController::KeyboardUp(unsigned char key, int x, int y)
{
}

void GameOverController::Mouse(int button, int state, int x, int y)
{
}

void GameOverController::PassiveMotion(int x, int y)
{
}
