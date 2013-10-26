#include "LevelOneController.h"
#include "texturedPolygons.h"
#include "GameController.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "BushCourtController.h"
#include "DrawManager.h"
#include "Stairs.h"

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
LevelOneController::LevelOneController(AudioManager* am, ModelManager* mm, TextureManager* tm): BasisController(am,mm,tm), loaded(false)
{
	loaded = true;
	Init();
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void LevelOneController::Init() 
{
	//GetAudio()->playSound(asBgMusic);
	Reshape();
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void LevelOneController::Draw()  //try to avoid updating variables in the draw function! -> do that in the update-funciton
{
	if (loaded) 
	{
		glClearColor(0, 0, 0, 0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
		
		// prepare for camera manipulation
		glPushMatrix();
		glLoadIdentity();

		// move the camera
		mCamera.MoveCamera();

		// DISPLAY TEXTURES
		//enable texture mapping
		glEnable (GL_TEXTURE_2D);
		glPushMatrix();
			//set camera to start position
			mCamera.SetCameraPosition(-500.0, -250.0, 3000.0, 180.0); 
			// displays the exit screen
			DrawControlRoom();
			DrawOuterWalls();
			DrawArchitecture();
			Draw3DModels();
			DrawObjects();
		glPopMatrix();
		glDisable (GL_TEXTURE_2D); 
		glPopMatrix();

		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void LevelOneController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!)
{ 

}

void LevelOneController::Reshape() 
{
	Reshape(width, height);
}

void LevelOneController::Reshape(int w, int h) 
{
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

//--------------------------------------------------------------------------------------
// Keyboard Functions
//--------------------------------------------------------------------------------------
void LevelOneController::SpecialKey(int key, int x, int y) 
{
	mCamera.SpecialKey(key, x, y);
}

//---------------------------------------------------------
void LevelOneController::SpecialKeyUp(int key, int x, int y) 
{
	mCamera.SpecialKeyUp(key, x, y);
}

//--------------------------------------------------------------------------------------

void LevelOneController::Keyboard(unsigned char key, int x, int y)
{
	mCamera.Keyboard(key, x, y);
}

//--------------------------------------------------------------------------------------
void LevelOneController::KeyboardUp(unsigned char key, int x, int y)
{
	mCamera.KeyboardUp(key, x, y);
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void LevelOneController::Mouse(int button, int state, int x, int y)
{
	mCamera.Mouse(button, state, x, y);
}

//--------------------------------------------------------------------------------------
//  Mouse Movements (NOT USED)
//  Can be used to rotate around screen using mouse, but keyboard used instead
//--------------------------------------------------------------------------------------
void LevelOneController::PassiveMotion(int x, int y) 
{
}

void LevelOneController::MouseMotion(int x, int y)
{
	mCamera.MouseMotion(x, y);
}

//--------------------------------------------------------------------------------------
//  Draw the Objects
//--------------------------------------------------------------------------------------
void LevelOneController::DrawObjects() 
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

	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taBomb));
		glPushMatrix();
		glTranslatef(750, 500, 4250);
		GetModel()->drawModel(mButton, GetTexture()->getTextureID(taButton));
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
//  Draw the 3D Models
//--------------------------------------------------------------------------------------
void LevelOneController::Draw3DModels()
{
	glPushMatrix();
		glTranslatef(4250, 0, 2500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(ta4x1platform));
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(ta4x1platform));
		glTranslatef(2500, 0, 4250);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(ta4x1platform));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2250, 450, 1500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(ta4x1platform));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500, 0, -1250);
		glRotatef(180, 0, 1, 0);
		GetModel()->drawModel(mConsole, GetTexture()->getTextureID(taConsole));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500, 0, -4450);
		glScalef(0.5, 1, 1);	
		GetModel()->drawModel(mLadder, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(RUSTYWALL));
	glPopMatrix();
}

//------------------------------------------------- -------------------------------------
//  Draw the Outer Walls
//--------------------------------------------------------------------------------------
void LevelOneController::DrawOuterWalls()
{
		//floor
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
		glBegin(GL_QUADS);
			glTexCoord2f (5.0, 5.0);		glVertex3f(0, 0, 0);
			glTexCoord2f (0.0, 5.0);		glVertex3f(0, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 0,	5000);
			glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 0, 0);
		glEnd();

		//ceiling
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
void LevelOneController::DrawArchitecture()
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


//--------------------------------------------------------------------------------------
//  Draw the Level Architecture
//--------------------------------------------------------------------------------------
void LevelOneController::DrawControlRoom()
{

	glBindTexture(GL_TEXTURE_2D,GetTexture()->getTextureID(taTilefloor)); 
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

	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taConcWall)); 
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
	
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor)); 
	glPushMatrix();
		glTranslatef(700, 0, -4000);
		glRotatef(180, 0, 1, 0);
		GetDrawManager()->DrawStairs(400, 250, 500, 5);
	glPopMatrix();
}