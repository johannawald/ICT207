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
LevelOneController::LevelOneController(): movementSpeed(15.0), rotationSpeed(0.005), loaded(false)
{
	// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
	// Set speed (steps)
	frameCount = 0;
	lastClock = 0;

	// display exit screen
	DisplayExit = false;
	// Stores raw image file
	image = nullptr;

	Init();
	
	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();
	
	// load texture images and create display lists
	CreateTextures();
	loaded = true;	

}

LevelOneController::~LevelOneController() {
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void LevelOneController::Init() {
	// set background (sky colour)
	transition.Update(tsNone);
	cam.DirectionUD(0);
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
	//cam.Position(2500.0, 350.0, 500.0, 180.0);
	cam.Position(2500.0, 1500.0, 550.0, 180.0); //temp view for checking level layout
	Reshape();
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void LevelOneController::Draw() 
{
	if (loaded) 
	{
		// check for movement
		cam.CheckCamera();
		//ansition.CheckNumberpad();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// DISPLAY TEXTURES
		//enable texture mapping
		glEnable (GL_TEXTURE_2D);
		glPushMatrix();
			// displays the exit screen
			if (DisplayExit) cam.DisplayWelcomeScreen (width, height, 0, tp.GetTexture(EXIT));
			DrawOuterWalls();
			DrawArchitecture();
			Draw3DModels();
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

void LevelOneController::Update() { 
	//there should be a difference between update (all the data) and draw (the objects)
	//this method  has to be defined since it's an abstract-function; our game-state will make a differnece between update and draw
}

void LevelOneController::Reshape() {
	Reshape(width, height);
}

void LevelOneController::Reshape(int w, int h) {
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
	switch (key)
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
void LevelOneController::SpecialKeyUp(int key, int x, int y) 
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

void LevelOneController::Keyboard(unsigned char key, int x, int y)
{
	int i = 0;
	switch (key)
	{
		// step left
		case 'c':
			//loaded = false;
			//transition.Update(tsNone);
			//StateMachine::setController(new BushCourtController);
		break;
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
		// display campus map
		case 'm':
		case 'M':
		{
			if (DisplayMap)
			{
				DisplayMap = false;
			}
			else
			{
				DisplayMap = true;
			}
		}
		break;
		// exit tour (escape key)
		case 27:
			{
				cam.SetRotateSpeed (0.0f);
				cam.SetMoveSpeed (0.0f);
				DisplayExit = true;
			}
		break;
		// display welcome page (space key)
		case ' ':
			{
				if (DisplayWelcome)
				{
					cam.SetRotateSpeed (rotationSpeed);
					cam.SetMoveSpeed (movementSpeed);
					DisplayWelcome = false;
				}
				else
				{
					cam.SetRotateSpeed (0.0f);
					cam.SetMoveSpeed (0.0f);
					DisplayWelcome = true;
				}
			}
		break;	
	}
}

//--------------------------------------------------------------------------------------
void LevelOneController::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
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
void LevelOneController::Mouse(int button, int state, int x, int y)
{
	// exit tour if clicked on exit splash screen
 	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		transition.CheckMouseInput();
		if ((DisplayExit) && (x <= width/2.0 + 256.0) && (x >= width/2.0 - 256.0)
			&& (y <= height/2.0 + 256.0) && (y >= height/2.0 - 256.0))
		{
			DeleteImageFromMemory(image);
			exit(1);
		}
  	 }
}

//--------------------------------------------------------------------------------------
//  Mouse Movements (NOT USED)
//  Can be used to rotate around screen using mouse, but keyboard used instead
//--------------------------------------------------------------------------------------
void LevelOneController::PassiveMotion(int x, int y) //mouseMove
{
	//trigger for the button-click-function in the transition
	transition.CheckMousePosition(x,y, width, height);

	/*if (x < 0)
		cam.DirectionRotateLR(0);
	else if (x > width)
		cam.DirectionRotateLR(0);
	else if (x > width/2.0)
	{
		cam.DirectionRotateLR(1);
		Draw();
		glutWarpPointer(width/2.0,height/2.0);
	}
	else if (x < width/2.0)
	{
		cam.DirectionRotateLR(-1);
		Draw();
		glutWarpPointer(width/2.0,height/2.0);
	}
	else
		cam.DirectionRotateLR(0);
	if (y < 0 || y > height)
		cam.DirectionLookUD(0);

	else if (y > height/2.0) {
		cam.DirectionLookUD(-1);
		Draw();
		glutWarpPointer(width/2.0,height/2.0);
	}
	else if (y < height/2.0) {
		cam.DirectionLookUD(1);
		Draw();
		glutWarpPointer(width/2.0,height/2.0);
	}
	else
		cam.DirectionLookUD(0);
	*/
}

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
void LevelOneController::CreateBoundingBoxes()
{
	//outer level walls - needs more work, can escape in the corners!
	cam.SetAABBMinX(0, -100);
	cam.SetAABBMaxX(0, 0);
	cam.SetAABBMinZ(0, 0);
	cam.SetAABBMaxZ(0, 5000);

	cam.SetAABBMinX(1, 5100);
	cam.SetAABBMaxX(1, 5000);
	cam.SetAABBMinZ(1, 0);
	cam.SetAABBMaxZ(1, 5000);

	cam.SetAABBMinZ(2, -100);
	cam.SetAABBMaxZ(2, 0);
	cam.SetAABBMinX(2, 0);
	cam.SetAABBMaxX(2, 5000);

	cam.SetAABBMinZ(3, 5100);
	cam.SetAABBMaxZ(3, 5000);
	cam.SetAABBMinX(3, 0);
	cam.SetAABBMaxX(3, 5000.0);

}

//--------------------------------------------------------------------------------------
//  Delete raw image and clear memory
//--------------------------------------------------------------------------------------
void LevelOneController::DeleteImageFromMemory(unsigned char* tempImage)
{
	tempImage = NULL;
		if (tempImage == NULL)
	{
		delete [] tempImage;
	}
}

//--------------------------------------------------------------------------------------
// Load and Create Textures
//--------------------------------------------------------------------------------------
void LevelOneController::CreateTextures()
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// set texture count
	tp.SetTextureCount(250); //NEEDS TO BE THE SAME ACROSS ALL CONTROLLERS!!! (else textures assigned randomly)
	unsigned char* image;
	// load and create textures

	image = tp.LoadTexture("data/thanks.raw", 512, 512);
	tp.CreateTexture(EXIT, image, 512, 512);

	image = tp.LoadTexture("data/box.raw", 512, 512);
	tp.CreateTexture(BOX, image, 512, 512);

	image = tp.LoadTexture("data/tilefloor.raw", 512, 512);
	tp.CreateTexture(TILEFLOOR, image, 512, 512);

	image = tp.LoadTexture("data/concwall.raw", 512, 512);
	tp.CreateTexture(CONCWALL, image, 512, 512);

	image = tp.LoadTexture("data/tilewall.raw", 512, 512);
	tp.CreateTexture(TILEWALL, image, 512, 512);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//--------------------------------------------------------------------------------------
//  Draw the 3D Models
//--------------------------------------------------------------------------------------
void LevelOneController::Draw3DModels()
{
	glPushMatrix();
		ModelLoader box;
		box.load("data/box.obj");
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOX));
		glScalef(0.5, 0.75, 0.5);
		glTranslatef(1000, 0, 1000);
		box.draw();
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Draw the Outer Walls
//--------------------------------------------------------------------------------------
void LevelOneController::DrawOuterWalls()
{
		//floor
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (2.0, 2.0);		glVertex3f(0, 0, 0);
			glTexCoord2f (0.0, 2.0);		glVertex3f(0, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 0,	5000);
			glTexCoord2f (2.0, 0.0);		glVertex3f(5000, 0, 0);
		glEnd();

		//ceiling
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (2.0, 2.0);		glVertex3f(0, 2000,	0);
			glTexCoord2f (0.0, 2.0);		glVertex3f(0, 2000, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 2000, 5000);
			glTexCoord2f (2.0, 0.0);		glVertex3f(5000, 2000, 0);
		glEnd();

		//walls
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEWALL));
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
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
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
	glPushMatrix();
		glTranslatef(-1, 0, -1);
		//solid platform tops
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (1.5, 1.5);		glVertex3f(0, 500, 0);
			glTexCoord2f (0.0, 1.5);		glVertex3f(0, 500, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 1500);
			glTexCoord2f (1.5, 0.0);		glVertex3f(1500, 500, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (0.5, 2.0);		glVertex3f(2000, 500, 0);
			glTexCoord2f (0.0, 2.0);		glVertex3f(2000, 500, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(4000, 500, 500);
			glTexCoord2f (0.5, 0.0);		glVertex3f(4000, 500, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f (1.5, 1.0);		glVertex3f(4000, 500, 0);
			glTexCoord2f (0.0, 1.0);		glVertex3f(4000, 500, 1500);
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
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (4.0, 0.25);		glVertex3f(2000, 0, 500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(4000, 0, 500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(4000, 500, 500);
			glTexCoord2f (4.0, 0.0);		glVertex3f(2000, 500, 500);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (2.0, 0.25);		glVertex3f(4000, 0, 1500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(5000, 0, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 500, 1500);
			glTexCoord2f (2.0, 0.0);		glVertex3f(4000, 500, 1500);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (2.0, 0.25);		glVertex3f(4000, 0, 500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(4000, 0, 1500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(4000, 500, 1500);
			glTexCoord2f (2.0, 0.0);		glVertex3f(4000, 500, 500);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(3500, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(5000, 0, 3500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 500, 3500);
			glTexCoord2f (3.0, 0.0);		glVertex3f(3500, 500, 3500);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(3500, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(3500, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(3500, 500, 5000);
			glTexCoord2f (3.0, 0.0);		glVertex3f(3500, 500, 3500);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(0, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(1500, 0, 3500);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 3500);
			glTexCoord2f (3.0, 0.0);		glVertex3f(0, 500, 3500);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
		glBegin(GL_QUADS);
			glTexCoord2f (3.0, 0.25);		glVertex3f(1500, 0, 3500);
			glTexCoord2f (0.0, 0.25);		glVertex3f(1500, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(1500, 500, 5000);
			glTexCoord2f (3.0, 0.0);		glVertex3f(1500, 500, 3500);
		glEnd();

		//stairs!
		DrawManager drawMan;
		glTranslatef(0, 0, 2000);
		drawMan.drawStairs(1500, 500, -500, 5);

	glPopMatrix();
}


//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void LevelOneController::IncrementFrameCount()
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
