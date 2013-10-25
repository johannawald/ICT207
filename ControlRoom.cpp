 #include "ControlRoom.h"
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
ControlRoom::ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm): BasisController(am,mm,tm), movementSpeed(15.0), rotationSpeed(0.005), loaded(false)
{
	insertedLevel = false;
	frameCount = 0;
	lastClock = 0;

	image = nullptr; //ray, we don't need that if we implemented the texturemanager! 
	//(images are loaded over and over again, if you enter the level / shay's world)

	Init();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();
	
	// load texture images and create display lists
	//CreateTextures();
	loaded = true;	
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void ControlRoom::Init() {
	cam.DirectionUD(0); //ray, we don't need that if you change the camera movement!
	cam.DirectionRotateLR(0);

	glClearColor(0, 0, 0, 0); //background/sky colour
	
	// set perpsective
	gluLookAt(0.0, 1.75, 0.0, 
		      0.0, 1.75, -1,
			  0.0f,1.0f,0.0f);

	// set the world co-ordinates (used to set quadrants for bounding boxes)
	cam.SetWorldCoordinates(5000.0, 5000.0);
	// turn collision detection on
	cam.SetCollisionDetectionOn(true);

	// set number of bounding boxes required
	cam.SetNoBoundingBoxes(19);
	// set starting position of user
	cam.Position(500, 500, -4000, 180.0);
	Reshape();
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void ControlRoom::Draw()  //try to avoid updating variables in the draw function! -> do that in the update-funciton
{
	if (loaded) 
	{
		// check for movement
		cam.CheckCamera();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// DISPLAY TEXTURES
		//enable texture mapping
		glEnable (GL_TEXTURE_2D);
		glPushMatrix();
			// displays the exit screen
		DrawWalls();
		DrawFloor();
		DrawStairs();
		DrawConsole();
		DrawLadder();
			// set the movement and rotation speed according to frame count
			IncrementFrameCount();
			cam.SetMoveSpeed(stepIncrement);
			cam.SetRotateSpeed(angleIncrement);
		glPopMatrix();
		glDisable (GL_TEXTURE_2D); 
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void ControlRoom::MouseMotion(int x, int y)
{

}

void ControlRoom::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!)
{ 
	if ((cam.GetLR() > 400) && (cam.GetLR() < 700) && (cam.GetFB() < -4300) && (cam.GetFB() > -4500)) 
		StateMachine::setBushCourtController();
	else if ((cam.GetFB() > -2000) && (!insertedLevel)) {
		cam.Position(2500.0, 1500.0, 550.0, 180.0);
		insertedLevel = true;
	}
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



//--------------------------------------------------------------------------------------
// Keyboard Functions
//--------------------------------------------------------------------------------------
void ControlRoom::SpecialKey(int key, int x, int y) 
{
	switch (key) //ray, we don't need that if you change the camera movement!
	{
		case GLUT_KEY_LEFT :
			cam.DirectionRotateLR(-2);
			break;

		case GLUT_KEY_RIGHT : 
			cam.DirectionRotateLR(2);
			break;

		case GLUT_KEY_UP : 
			cam.DirectionFB(1);
			break;

		case GLUT_KEY_DOWN : 
			cam.DirectionFB(-1);
			break;
	}
}

//---------------------------------------------------------
void ControlRoom::SpecialKeyUp(int key, int x, int y) 
{
	switch (key)
	{
		// rotate left or right
		case GLUT_KEY_LEFT : 
		case GLUT_KEY_RIGHT : 
			cam.DirectionRotateLR(0);			
		break;
		// move backwards or forwards
		case GLUT_KEY_UP : 
		case GLUT_KEY_DOWN : 
			cam.DirectionFB(0);
		break;
	}
}

//--------------------------------------------------------------------------------------

void ControlRoom::Keyboard(unsigned char key, int x, int y)
{
	int i = 0;
	switch (key)
	{
		case '1':
			//can only be used within these bounds - next to console - adjust size
			if (((cam.GetLR() > 0) && (cam.GetLR() < 1000)) && ((cam.GetFB() < -1000) || (cam.GetFB() > -2000)))
			{
				//change that later to a seperate controller
				cam.Position(2500.0, 1500.0, 550.0, 180.0);
			}
			break;
		case '0':
			StateMachine::setBushCourtController(); //debug! Should be deleted in the release version
			break;
		case 'e':
			//next to ladder out
			if (((cam.GetLR() > 250) && (cam.GetLR() < 750)) && ((cam.GetFB() < -2000) || (cam.GetFB() > -3000)))
			{
				StateMachine::setBushCourtController();
			}
		case 'Z':
		case 'z':
			cam.DirectionLR(-1);
			break;
		// step right
		case 'X':
		case 'x':
			cam.DirectionLR(1);
		break;
		// look up
		case 'Q':
		case 'q':
			cam.DirectionLookUD(1);
			break;
		// look down
		case 'A':
		case 'a':
			cam.DirectionLookUD(-1);
		break;
		// exit tour (escape key)
		case 27:
			{
				cam.Position(500, 500, -4000, 180.0);
			}
		break;
		// display welcome page (space key)
		case ' ':
			{
				cam.SetRotateSpeed (0.0f);
				cam.SetMoveSpeed (0.0f);
			}
		break;	
	}
}

//--------------------------------------------------------------------------------------
void ControlRoom::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) //ray, we don't need that if you change the camera movement!
	{
		// step left or right
		case 'x' :
		case 'X' :
		case 'z' :
		case 'Z' :
			cam.DirectionLR(0);
		break;
		// look left up or down
		case 'a' :
		case 'A' :
		case 'q' :
		case 'Q' :
			cam.DirectionLookUD(0);
		break;
	}
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void ControlRoom::Mouse(int button, int state, int x, int y)
{

}

void ControlRoom::PassiveMotion(int x, int y) //mouseMove
{
}

void ControlRoom::DrawFloor()
{
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
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
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
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
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
	glPushMatrix();
		glTranslatef(700, 0, -4000);
		glRotatef(180, 0, 1, 0);
		drawMan.DrawStairs(400, 250, 500, 5);
	glPopMatrix();
}

void ControlRoom::DrawConsole()
{
	glPushMatrix();
		glTranslatef(500, 0, -1250);
		glRotatef(180, 0, 1, 0);
		//GetModel()->drawModel(mConsole, tp.GetTexture(CONSOLE)); //*JW
	glPopMatrix();
}

void ControlRoom::DrawLadder(){
	glPushMatrix();
		glTranslatef(500, 0, -4450);
		glScalef(0.5, 1, 1);	
		//GetModel()->drawModel(mLadder, tp.GetTexture(RUSTYWALL));
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void ControlRoom::IncrementFrameCount() //ray, check if you need that, please if you change the camera movement
{
	double t = ((GLdouble)(clock()-lastClock))/(GLdouble)CLOCKS_PER_SEC;  
	frameCount ++;

	// reset after t
	if (t > 0.1)
	{
		stepIncrement = t/frameCount * 1400;
		angleIncrement = t/frameCount;
		frameCount = 0;
		lastClock = clock();
	}
}

