 #include "ControlRoom.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "GameController.h"

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
ControlRoom::ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm): 
	BasisGameController(am,mm,tm)
{
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void ControlRoom::Init() 
{	
	BasisGameController::Init();

	GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 1, 1, 0, 0, 0, 100, 200, 300); 
	GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 1, 1, 10, 50, 200, 100, 20, 30);
	GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 1, 1, 100, 0, -200, 200, 400, 200); 
	//Jon, can you change this to Collision-quads?
	GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 10, 10, 0, 0, 1000, 4000, 3000, 100); 
}

void ControlRoom::Draw()
{
	BasisGameController::Draw();
}

void ControlRoom::DrawObjects()
{		
	//that Push is important!
	glPushMatrix();
		mCollision.Draw(GetDrawManager());
		//Draw objects
		DrawWalls();
		DrawFloor();
		DrawStairs();
		DrawLadder();
		DrawConsole();
	glPopMatrix();
}

void ControlRoom::CheckCollision()
{	
	//collision with walls:
	BasisGameController::CheckCollision();
	//here collision with objects 
}

void ControlRoom::CollisionWithObject(GameObject* pGameObject)
{
}

void ControlRoom::Update()
{ 
	if (IsAtComputerPosition())
		StateMachine::setController(new GameController(GetAudio(), GetModel(), GetTexture()));
}

bool ControlRoom::IsAtComputerPosition() 
{
	return (false);  //(mCamera.GetZpos() > -2000); Jon, insert here position of computer
}

void ControlRoom::Reshape(int w, int h) {
	BasisGameController::Reshape(w, h);
}

void ControlRoom::MouseMotion(int x, int y)
{
	BasisGameController::MouseMotion(x, y);
}

void ControlRoom::SpecialKey(int key, int x, int y) 
{
	BasisGameController::SpecialKey(key,x,y);
}

void ControlRoom::SpecialKeyUp(int key, int x, int y) 
{
	BasisGameController::SpecialKeyUp(key,x,y);
}

void ControlRoom::Keyboard(unsigned char key, int x, int y)
{
	BasisGameController::Keyboard(key,x,y);
	if (key=='t')
		StateMachine::setController(new GameController(GetAudio(), GetModel(), GetTexture()));
}

//--------------------------------------------------------------------------------------
void ControlRoom::KeyboardUp(unsigned char key, int x, int y)
{
	BasisGameController::KeyboardUp(key,x,y);
}

void ControlRoom::Mouse(int button, int state, int x, int y)
{
	BasisGameController::Mouse(button, state, x, y);
}

void ControlRoom::PassiveMotion(int x, int y)
{
}

void ControlRoom::DrawFloor()
{
	//jon, please make it bigger -> controlroom we need an window for the left
	//maybe create a variable "factor" to change the size of everything easily

	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	//floor
	glBegin(GL_QUADS);
		glTexCoord2f (1.0, 1.0);		glVertex3f(0, 0, -4000);
		glTexCoord2f (0.0, 1.0);		glVertex3f(0, 0, -1000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(1000, 0, -1000);
		glTexCoord2f (1.0, 0.0);		glVertex3f(1000, 0, -4000);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f (0.25, 0.25);		glVertex3f(300, 0, -4500);
		glTexCoord2f (0.0, 0.25);		glVertex3f(300, 0, -4000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(700, 0, -4000);
		glTexCoord2f (0.25, 0.0);		glVertex3f(700, 0, -4500);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f (1.0, 1.0);		glVertex3f(0, 1000, -4000);
		glTexCoord2f (0.0, 1.0);		glVertex3f(0, 1000, -1000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(1000, 1000, -1000);
		glTexCoord2f (1.0, 0.0);		glVertex3f(1000, 1000, -4000);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f (0.25, 0.25);		glVertex3f(300, 1000, -4000);
		glTexCoord2f (0.0, 0.25);		glVertex3f(300, 1000, -4500);
		glTexCoord2f (0.0, 0.0);		glVertex3f(700, 1000, -4500);
		glTexCoord2f (0.25, 0.0);		glVertex3f(700, 1000, -4000);
	glEnd();
}

void ControlRoom::DrawWalls()
{
	
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall));
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);			glVertex3f(0, 0, -1000);
		glTexCoord2f(0.0, 1.0);			glVertex3f(1000, 0, -1000);
		glTexCoord2f(0.0, 0.0);			glVertex3f(1000, 1000, -1000);
		glTexCoord2f(1.0, 0.0);			glVertex3f(0, 1000, -1000);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);			glVertex3f(1000, 0, -1000);
		glTexCoord2f(0.0, 1.0);			glVertex3f(1000, 0, -4000);
		glTexCoord2f(0.0, 0.0);			glVertex3f(1000, 1000, -4000);
		glTexCoord2f(1.0, 0.0);			glVertex3f(1000, 1000, -1000);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.5, 1.0);			glVertex3f(0, 0, -4000);
		glTexCoord2f(0.0, 1.0);			glVertex3f(300, 0, -4000);
		glTexCoord2f(0.0, 0.0);			glVertex3f(300, 1000, -4000);
		glTexCoord2f(0.5, 0.0);			glVertex3f(0, 1000, -4000);
	glEnd();	
	glBegin(GL_QUADS);
		glTexCoord2f(0.5, 1.0);			glVertex3f(700, 0, -4000);
		glTexCoord2f(0.0, 1.0);			glVertex3f(1000, 0, -4000);
		glTexCoord2f(0.0, 0.0);			glVertex3f(1000, 1000, -4000);
		glTexCoord2f(0.5, 0.0);			glVertex3f(700, 1000, -4000);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.5, 1.0);			glVertex3f(300, 0, -4500);
		glTexCoord2f(0.0, 1.0);			glVertex3f(700, 0, -4500);
		glTexCoord2f(0.0, 0.0);			glVertex3f(700, 1000, -4500);
		glTexCoord2f(0.5, 0.0);			glVertex3f(300, 1000, -4500);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);			glVertex3f(300, 0, -4500);
		glTexCoord2f(0.0, 1.0);			glVertex3f(300, 0, -4000);
		glTexCoord2f(0.0, 0.0);			glVertex3f(300, 1000, -4000);
		glTexCoord2f(1.0, 0.0);			glVertex3f(300, 1000, -4500);
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);			glVertex3f(700, 0, -4000);
		glTexCoord2f(0.0, 1.0);			glVertex3f(700, 0, -4500);
		glTexCoord2f(0.0, 0.0);			glVertex3f(700, 1000, -4500);
		glTexCoord2f(1.0, 0.0);			glVertex3f(700, 1000, -4000);
	glEnd();
}

void ControlRoom::DrawStairs()
{
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glPushMatrix();
		glTranslatef(700, 0, -4000);
		glRotatef(180, 0, 1, 0);
		GetDrawManager()->DrawStairs(400, 250, 500, 5);
	glPopMatrix();
}

void ControlRoom::DrawConsole()
{
	glPushMatrix();
		glTranslatef(500, 0, -1250);
		glRotatef(180, 0, 1, 0);
		GetModel()->drawModel(mConsole, GetTexture()->getTextureID(taConsole));
	glPopMatrix();
}

void ControlRoom::DrawLadder()
{
	glPushMatrix();
		glTranslatef(500, 0, -4450); //Jon, can you please locate that + Texture
		glScalef(0.5, 1, 1);	
		GetModel()->drawModel(mLadder, GetTexture()->getTextureID(taRustyWall));
	glPopMatrix();
}
