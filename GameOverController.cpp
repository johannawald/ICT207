#include "GameOverController.h"
#include "StateMachine.h"
#include "GameController.h"
#include "ControlRoom.h"

GameOverController::GameOverController(AudioManager* am, ModelManager* mm, TextureManager* tm, float pHeight, float pWidth): 
	BasisController(am,mm,tm, pHeight, pWidth)
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

void GameOverController::DrawObjects()		//updated 29.10 *JM
{		
	glPushMatrix();
		//jon, Draw objects here
		//trigger explosion, wait a second, then show this tex?
		//or explosion in background?
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable (GL_TEXTURE_2D);
		
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taGameOver));
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			glTexCoord2f (0.0, 1.0);			glVertex3f(-4,-4,-10);
			glTexCoord2f (1.0, 1.0);			glVertex3f(4,-4,-10);
			glTexCoord2f (1.0, 0.0);			glVertex3f(4,4,-10);
			glTexCoord2f (0.0, 0.0);			glVertex3f(-4,4,-10);
		glEnd();


		glDisable(GL_BLEND);
		glDisable (GL_TEXTURE_2D); 
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

void GameOverController::Keyboard(unsigned char key, int x, int y)		//updated 29.10 *JM
{
	switch (key)
	{
	case 27: //press esc to restart game
		StateMachine::setController(new ControlRoom(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth()));
		break;
	}
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
