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
LevelOneController::LevelOneController(AudioManager* am, ModelManager* mm, TextureManager* tm): BasisController(am,mm,tm), movementSpeed(15.0), rotationSpeed(0.005), loaded(false)
{
	insertedLevel = false;
	frameCount = 0;
	lastClock = 0;

	image = nullptr; //ray, we don't need that if we implemented the texturemanager! 
	//(images are loaded over and over again, if you enter the level / shay's world)

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
void LevelOneController::Draw()  //try to avoid updating variables in the draw function! -> do that in the update-funciton
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
			DrawControlRoom();
			DrawOuterWalls();
			DrawArchitecture();
			Draw3DModels();
			DrawObjects();
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

void LevelOneController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!)
{ 
	if ((cam.GetLR() > 400) && (cam.GetLR() < 700) && (cam.GetFB() < -4300) && (cam.GetFB() > -4500)) 
		StateMachine::setBushCourtController();
	else if ((cam.GetFB() > -2000) && (!insertedLevel)) {
		cam.Position(2500.0, 1500.0, 550.0, 180.0);
		insertedLevel = true;
	}
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
void LevelOneController::KeyboardUp(unsigned char key, int x, int y)
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
void LevelOneController::Mouse(int button, int state, int x, int y)
{

}

//--------------------------------------------------------------------------------------
//  Mouse Movements (NOT USED)
//  Can be used to rotate around screen using mouse, but keyboard used instead
//--------------------------------------------------------------------------------------
void LevelOneController::PassiveMotion(int x, int y) //mouseMove
{
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

	cam.SetAABBMinX(1, 5000);
	cam.SetAABBMaxX(1, 5100);
	cam.SetAABBMinZ(1, 0);
	cam.SetAABBMaxZ(1, 5000);

	cam.SetAABBMinX(2, 0);
	cam.SetAABBMaxX(2, 5000);
	cam.SetAABBMinZ(2, -100);
	cam.SetAABBMaxZ(2, 0);

	cam.SetAABBMinX(3, 0);
	cam.SetAABBMaxX(3, 5000);
	cam.SetAABBMinZ(3, 5000);
	cam.SetAABBMaxZ(3, 5100);
}

//--------------------------------------------------------------------------------------
// Load and Create Textures
//--------------------------------------------------------------------------------------
void LevelOneController::CreateTextures() //ray, we don't need that if we implemented the texturemanager! 
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// set texture count
	tp.SetTextureCount(LAST); //NEEDS TO BE THE SAME ACROSS ALL CONTROLLERS!!! (else textures assigned randomly)
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

	image = tp.LoadTexture("data/rustywall.raw", 512, 256);
	tp.CreateTexture(RUSTYWALL, image, 512, 256);

	image = tp.LoadTexture("data/tilewall.raw", 512, 512);
	tp.CreateTexture(TILEWALL, image, 512, 512);

	image = tp.LoadTexture("data/4x1platform.raw", 512, 512);
	tp.CreateTexture(PLATFORM4X1, image, 512, 512);

	image = tp.LoadTexture("data/button.raw", 512, 512);
	tp.CreateTexture(BUTTON, image, 512, 512);

	image = tp.LoadTexture("data/bomb.raw", 512, 512);
	tp.CreateTexture(BOMB, image, 512, 512);

	image = tp.LoadTexture("data/console.raw", 512, 512);
	tp.CreateTexture(CONSOLE, image, 512, 512);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//--------------------------------------------------------------------------------------
//  Draw the Objects
//--------------------------------------------------------------------------------------
void LevelOneController::DrawObjects() 
{

	glPushMatrix();
		glTranslatef(2000, 0, 3500);
		glScalef(0.75, 1.0, 0.75);
		GetModel()->drawModel(mBox, tp.GetTexture(BOX));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 750);
		glScalef(0.75, 1.0, 0.75);
		GetModel()->drawModel(mBox, tp.GetTexture(BOX));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(750, 500, 750);
		GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 1250);
		GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 4250);
		GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOMB));
		glPushMatrix();
		glTranslatef(750, 500, 4250);
		GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
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
		GetModel()->drawModel(m4x1platform, tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PLATFORM4X1));
		glTranslatef(2500, 0, 4250);
		GetModel()->drawModel(m4x1platform, tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2250, 450, 1500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500, 0, -1250);
		glRotatef(180, 0, 1, 0);
		GetModel()->drawModel(mConsole, tp.GetTexture(CONSOLE)); //*JW
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500, 0, -4450);
		glScalef(0.5, 1, 1);	
		GetModel()->drawModel(mLadder, tp.GetTexture(RUSTYWALL)); //*JW
	glPopMatrix();
}

//------------------------------------------------- -------------------------------------
//  Draw the Outer Walls
//--------------------------------------------------------------------------------------
void LevelOneController::DrawOuterWalls()
{
		//floor
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (5.0, 5.0);		glVertex3f(0, 0, 0);
			glTexCoord2f (0.0, 5.0);		glVertex3f(0, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 0,	5000);
			glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 0, 0);
		glEnd();

		//ceiling
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (5.0, 5.0);		glVertex3f(0, 2000,	0);
			glTexCoord2f (0.0, 5.0);		glVertex3f(0, 2000, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 2000, 5000);
			glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 2000, 0);
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

		//solid platform tops
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
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
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
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
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
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
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
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
	DrawManager drawMan; //jak, we should not create the drawmanager in the draw function! use the drawmanager provided in the base class!
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));

	glPushMatrix();
		glTranslatef(0, 0, 2000);
		drawMan.DrawStairs(500, 500, -500, 5);
		glTranslatef(500, 0, 0);
		drawMan.DrawStairs(500, 500, -500, 5);
		glTranslatef(500, 0, 0);
		drawMan.DrawStairs(500, 500, -500, 5);
	glPopMatrix();

	
	glPushMatrix(); //more stairs!
		glTranslatef(1500, 0, 2000);
		glRotatef(270, 0, 1, 0);
		drawMan.DrawStairs(500, 500, -500, 5);
	glPopMatrix();

	/*
	Stairs stairs;
	glPushMatrix();
		stairs.SetStairDimensions(500, 500, 500, 5);
		stairs.DrawStairs(1550, 0, 2000, 0, 270, 0, 1, CONCWALL, CONCWALL);
	glPopMatrix();*/
}


//--------------------------------------------------------------------------------------
//  Draw the Level Architecture
//--------------------------------------------------------------------------------------
void LevelOneController::DrawControlRoom()
{

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
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

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CONCWALL));
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
	
	DrawManager drawMan; //jak, don't create that object over and over again!
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TILEFLOOR));
	glPushMatrix();
		glTranslatef(700, 0, -4000);
		glRotatef(180, 0, 1, 0);
		drawMan.DrawStairs(400, 250, 500, 5);
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void LevelOneController::IncrementFrameCount() //ray, check if you need that, please if you change the camera movement
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
