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

	//GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 1, 1, Vector3D(0, 0, 0), Vector3D(100, 200, 300)); 
	//GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 1, 1, Vector3D(10, 50, 200), Vector3D(100, 20, 30));
	//GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 1, 1, Vector3D(100, 0, -200), Vector3D(200, 400, 200)); 
	//Jon, can you change this to Collision-quads?
	//GetDrawManager()->DrawCollisionCube(&mCollision, GetTexture()->getTextureID(taHallway10), 10, 10, Vector3D(0, 0, 1000), Vector3D(4000, 3000, 100));
}

void ControlRoom::Draw()
{
	BasisGameController::Draw();
}

void ControlRoom::DrawObjects()
{

		
	//that Push is important!
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glColor3f(1, 1, 1);
		//mCollision.Draw(GetDrawManager());
		//Draw objects
		DrawWalls();
		DrawFloor();
		DrawStairs();
		DrawLadder();
		DrawConsole();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

int ControlRoom::CheckCollision()
{	
	//collision with walls:
	return BasisGameController::CheckCollision();
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

	//floor
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 2, -4000, 0, -6000, 8000, 12000, 0);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 1, 1, -2000, 0, -8000, 4000, 2000, 0);
	//roof
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 2, -4000, 4000, -6000, 8000, 12000, 0);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 1, 1, -2000, 4000, -8000, 4000, 2000, 0);
	
	/*
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glBegin(GL_QUADS);
		glTexCoord2f (2.0, 2.0);		glVertex3f(-4000, 0, 6000);
		glTexCoord2f (0.0, 2.0);		glVertex3f(4000, 0, 6000);
		glTexCoord2f (0.0, 0.0);		glVertex3f(4000, 0, -6000);
		glTexCoord2f (2.0, 0.0);		glVertex3f(-4000, 0, -6000);
	glEnd();
	
	//floor
	
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
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
	glEnd();*/
	
}

void ControlRoom::DrawWalls()
{
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 4, 1, -4000, 0, 6000, 8000, 0, 4000);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 2000, 0, -6000, 2000, 0, 4000);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -4000, 0, -6000, 2000, 0, 4000);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 2, 1, -2000, 0, -8000, 4000, 0, 4000);

	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 6, 1, -4000, 0, -6000, 0, 12000, 4000);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 6, 1, 4000, 0, -6000, 0, 12000, 4000);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, -2000, 0, -8000, 0, 2000, 4000);
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilewall), 1, 1, 2000, 0, -8000, 0, 2000, 4000);


	/*
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
	*/
}

void ControlRoom::DrawStairs()
{
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glPushMatrix();
		glTranslatef(2000, 0, -6000);
		glRotatef(180, 0, 1, 0);
		GetDrawManager()->DrawStairs(4000, 1000, 2000, 5);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, -1);
}

void ControlRoom::DrawConsole()
{
	//console is 500x250?
	glPushMatrix();
		glTranslatef(1000, 0, 4500);
		glRotatef(180, 0, 1, 0);
		glScalef(2, 2, 2);
		GetModel()->drawModel(mConsole, GetTexture()->getTextureID(taConsole));
	glPopMatrix();
}

void ControlRoom::DrawLadder()
{
	glPushMatrix();
		//glTranslatef(-500, 0, -6750);
		glScalef(1.5, 3, 3);	
		addCollisionGameObject(Vector3D(-250, 0, -6560), Vector3D(), Vector3D(100,100,100), Vector3D(1.5,3,3), Vector3D(), mLadder, taRustyWall, mIndexLadder);
		//GetModel()->drawModel(mLadder, GetTexture()->getTextureID(taRustyWall));
	glPopMatrix();
}
