//Johanna Wald, added some Push/Pop Attribues

#include "GameWinController.h"
#include "StateMachine.h"
#include "GameController.h"
#include "ControlRoom.h"

GameWinController::GameWinController(AudioManager* am, ModelManager* mm, TextureManager* tm, float pHeight, float pWidth): 
	BasisController(am,mm,tm, pHeight, pWidth)
{
}

void GameWinController::Init() 
{	
	BasisController::Init();
}

void GameWinController::Draw()
{
	BasisController::Draw();
}

void GameWinController::DrawObjects()
{		
	glPushMatrix();
		//trigger something - needs to be a cool win state - fireworks?
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable (GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taGameWin));
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			glTexCoord2f (0.0, 1.0);			glVertex3f(-4,-4,-10);
			glTexCoord2f (1.0, 1.0);			glVertex3f(4,-4,-10);
			glTexCoord2f (1.0, 0.0);			glVertex3f(4,4,-10);
			glTexCoord2f (0.0, 0.0);			glVertex3f(-4,4,-10);
		glEnd();

		//glDisable(GL_BLEND);
		glDisable (GL_TEXTURE_2D); 
	glPopMatrix();
}

void GameWinController::Update()
{ 
}

void GameWinController::Reshape(int w, int h) {
	BasisController::Reshape(w, h);
}

void GameWinController::MouseMotion(int x, int y)
{
}

void GameWinController::SpecialKey(int key, int x, int y) 
{
}

void GameWinController::SpecialKeyUp(int key, int x, int y) 
{
}

void GameWinController::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: //press esc to restart game
		StateMachine::setController(new ControlRoom(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth()));
		break;
	}
}

//--------------------------------------------------------------------------------------
void GameWinController::KeyboardUp(unsigned char key, int x, int y)
{
}

void GameWinController::Mouse(int button, int state, int x, int y)
{
}

void GameWinController::PassiveMotion(int x, int y)
{
}
