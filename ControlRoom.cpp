 #include "ControlRoom.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "GameController.h"

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
ControlRoom::ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm): 
	BasisController(am,mm,tm), loaded(false), MoveX(true), MoveY(true), MoveZ(true)
{
	Init();
	loaded = true;	
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void ControlRoom::Init() 
{	
	glClearColor(0, 0, 0, 0); //background/sky colour	
	gluLookAt(0.0, 1.75, 0.0, 
		      0.0, 1.75, -1,
			  0.0f,1.0f,0.0f);
	Reshape();
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void ControlRoom::Draw()
{
	if (loaded) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();
			//Move camera:
			mCamera.PrepareMovement();
			//mCamera.SetDiffValues(mCamera.GetXposDiff(), mCamera.GetYposDiff(), mCamera.GetZposDiff());
			mCamera.MoveCamera();
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			//Set camera position:
			mCamera.SetCameraPosition(-500, -250, 3000, 180);
			//Draw objects
			DrawWalls();
			DrawFloor();
			DrawStairs();
			DrawLadder();
			DrawConsole(); //the last one is always not working
			
			GetDrawManager()->DrawCollisionCube(&cd, -1, 1, 1, 100, 100, 10, 100, 200, 300); 
			GetDrawManager()->DrawCollisionCube(&cd, -1, 1, 1, 10, 50, 200, 100, 20, 30);
			GetDrawManager()->DrawCollisionCube(&cd, -1, 1, 1, 100, 10, -200, 200, 4000, 200); 

		glPopMatrix();
		glDisable (GL_TEXTURE_2D); 
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void ControlRoom::Update()
{ 
	int IndexCollision = -1;
	// the camera wants to move(1,2,1)
	if (cd.Collision(mCamera.GetXpos(), mCamera.GetXpos(), mCamera.GetXpos(), IndexCollision))
	{
		//cd.UpdateMovementVector(IndexCollision, );
		//Update Movement Vector
	}
	MoveX = true; //!cd.CollisionX(mCamera.GetXpos());
	MoveY = true; //!cd.CollisionY(mCamera.GetYpos());
	MoveZ = true; //!cd.CollisionZ(mCamera.GetZpos());
	//Collision Detection

	if (IsAtComputerPosition())
		StateMachine::setController(new GameController(GetAudio(), GetModel(), GetTexture()));
}

bool ControlRoom::IsAtComputerPosition()
{ 
	return (false);  //(mCamera.GetZpos() > -2000); Jon, insert here position of computer
}

void ControlRoom::Reshape() {
	Reshape(width, height);
}

void ControlRoom::Reshape(int w, int h) {
	width = w;		
	height = h;
	// Prevent a divide by zero, when window is too short		
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	ratio = 1.0f * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,250000);	
	glMatrixMode(GL_MODELVIEW);
}

void ControlRoom::MouseMotion(int x, int y)
{
	mCamera.MouseMotion(x, y);
}

void ControlRoom::SpecialKey(int key, int x, int y) 
{
	mCamera.SpecialKey(key,x,y);
}

void ControlRoom::SpecialKeyUp(int key, int x, int y) 
{
	mCamera.SpecialKeyUp(key, x, y);
}

void ControlRoom::Keyboard(unsigned char key, int x, int y)
{
	mCamera.Keyboard(key, x, y);
}

//--------------------------------------------------------------------------------------
void ControlRoom::KeyboardUp(unsigned char key, int x, int y)
{
	mCamera.KeyboardUp(key, x, y);
}

void ControlRoom::Mouse(int button, int state, int x, int y)
{
	mCamera.Mouse(button, state, x, y);
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
	//Jon, can you change this to Collision-quads?
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall));
	//walls
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);			glVertex3f(0, 0, -4000);
		glTexCoord2f(0.0, 1.0);			glVertex3f(0, 0, -1000);
		glTexCoord2f(0.0, 0.0);			glVertex3f(0, 1000, -1000);
		glTexCoord2f(1.0, 0.0);			glVertex3f(0, 1000, -4000);
	glEnd();
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
