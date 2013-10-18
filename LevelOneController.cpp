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
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	//cam.InitiateBoundingBoxes();
	
	// load texture images and create display lists
	CreateTextures();
	loaded = true;

	// intialise camera values
	camSpeed = 20.0;
	camXpos = 0.0; 
	camYpos = 0.0; 
	camZpos = 0.0; 
	camXrot = 0.0; 
	camYrot = 0.0;
	camRadius = 500.0f;
	camMaxAngle = 35.0;
	camMinAngle = 0.0;
	camYrotrad;
	camXrotrad;
	camMouseClicked = false;
	camKeyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)
	camSpecialKeyStates = new bool[4];
	camLastx = glutGet(GLUT_WINDOW_WIDTH)/2; 
	camLasty = glutGet(GLUT_WINDOW_HEIGHT)/2;

	for(int i=0; i<256; i++)
	{
		camKeyStates[i] = false;
	}

	for(int i=0; i<4; i++)
	{
		camSpecialKeyStates[i] = false;
	}
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void LevelOneController::Init() 
{
	// set perpsective
	//gluLookAt(0.0, 1.75, 0.0, 
	//	      0.0, 1.75, -1,
	//		  0.0f,1.0f,0.0f);

	glutIgnoreKeyRepeat(0);
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
		Enable();

		//RF READ CAMERA CONTROLS
		// check for movement
		KeyOperations();

		//RF: CAMERA
		//control the camera
		glLoadIdentity();
		
		glTranslatef(0.0f, -100.0f, -camRadius);
		glRotatef(camXrot,1.0,0.0,0.0);

		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glColor3f(1.0f, 0.0f, 0.0f);
			glutSolidSphere(100, 12, 12); //Our character to follow
		glPopMatrix();
    
		glRotatef(camYrot,0.0,1.0,0.0);  //rotate the camera on the y-axis (up and down)
		glTranslated(-camXpos,0.0f,-camZpos); //translate the screen to the position of our camera
		glColor3f(1.0f, 1.0f, 1.0f);

		// DISPLAY TEXTURES
		//enable texture mapping
		glEnable (GL_TEXTURE_2D);
		glPushMatrix();
			glRotatef(180, 0.0, 1.0, 0.0); //rotate camera 180 degrees
			glTranslatef(-500.0, -250.0, 3000.0); //translate camera starting position
			// displays the exit screen
			DrawControlRoom();
			DrawOuterWalls();
			DrawArchitecture();
			Draw3DModels();
			DrawObjects();
			// set the movement and rotation speed according to frame count
			IncrementFrameCount();
		glPopMatrix();
		glDisable (GL_TEXTURE_2D); 

		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void LevelOneController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!)
{ 
	//NEED TO CHANGE TO DETECT TRANSITION LOCATION - use collision?
	//if ((camXpos > 400) && (camXpos < 700) && (camZpos < -4300) && (camZpos > -4500)) 
	//	StateMachine::setBushCourtController();
	
	//if ((cam.GetLR() > 400) && (cam.GetLR() < 700) && (cam.GetFB() < -4300) && (cam.GetFB() > -4500)) 
	//	StateMachine::setBushCourtController();
	//else if ((cam.GetFB() > -2000) && (!insertedLevel)) {
	//	cam.Position(2500.0, 1500.0, 550.0, 180.0);
	//	insertedLevel = true;
	//}
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
	gluPerspective(60,ratio,1,250000);	
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
			camSpecialKeyStates[0] = true;
			break;

		case GLUT_KEY_RIGHT :
			camSpecialKeyStates[1] = true;
			break;

		case GLUT_KEY_UP : 
			camSpecialKeyStates[2] = true;
			break;

		case GLUT_KEY_DOWN : 
			camSpecialKeyStates[3] = true;
			break;
	}
}

//---------------------------------------------------------
void LevelOneController::SpecialKeyUp(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
			camSpecialKeyStates[0] = false;
			break;

		case GLUT_KEY_RIGHT :
			camSpecialKeyStates[1] = false;
			break;

		case GLUT_KEY_UP : 
			camSpecialKeyStates[2] = false;
			break;

		case GLUT_KEY_DOWN : 
			camSpecialKeyStates[3] = false;
			break;
	}
}

//--------------------------------------------------------------------------------------

void LevelOneController::Keyboard(unsigned char key, int x, int y)
{
	camKeyStates[key] = true; // Set the state of the current key to pressed
	//int i = 0;
	//switch (key)
	//{
	//	case '1':
	//		//can only be used within these bounds - next to console - adjust size
	//		if (((cam.GetLR() > 0) && (cam.GetLR() < 1000)) && ((cam.GetFB() < -1000) || (cam.GetFB() > -2000)))
	//		{
	//			//change that later to a seperate controller
	//			cam.Position(2500.0, 1500.0, 550.0, 180.0);
	//		}
	//		break;
	//	case '0':
	//		StateMachine::setBushCourtController(); //debug! Should be deleted in the release version
	//		break;
	//	case 'e':
	//		//next to ladder out
	//		if (((cam.GetLR() > 250) && (cam.GetLR() < 750)) && ((cam.GetFB() < -2000) || (cam.GetFB() > -3000)))
	//		{
	//			StateMachine::setBushCourtController();
	//		}
	//	case 'Z':
	//	case 'z':
	//		cam.DirectionLR(-1);
	//		break;
	//	// step right
	//	case 'X':
	//	case 'x':
	//		cam.DirectionLR(1);
	//	break;
	//	// look up
	//	case 'Q':
	//	case 'q':
	//		cam.DirectionLookUD(1);
	//		break;
	//	// look down
	//	case 'A':
	//	case 'a':
	//		cam.DirectionLookUD(-1);
	//	break;
	//	// exit tour (escape key)
	//	case 27:
	//		{
	//			cam.Position(500, 500, -4000, 180.0);
	//		}
	//	break;
	//	// display welcome page (space key)
	//	case ' ':
	//		{
	//			cam.SetRotateSpeed (0.0f);
	//			cam.SetMoveSpeed (0.0f);
	//		}
	//	break;	
	//}
}

//--------------------------------------------------------------------------------------
void LevelOneController::KeyboardUp(unsigned char key, int x, int y)
{
	camKeyStates[key] = false; // Set the state of the current key to not pressed
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void LevelOneController::Mouse(int button, int state, int x, int y)
{
	camLastx = x; //set lastx to the current x position
	camLasty = y; //set lasty to the current y position
	
	if((button == GLUT_LEFT_BUTTON) || (button == GLUT_RIGHT_BUTTON)) 
	{
		camMouseClicked = (state == GLUT_DOWN);
		if(state == GLUT_DOWN)
		{
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else
		{
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2); //rest the mouse point to center of window
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
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
	camDiffx = 0;// = x-lastx; //check the difference between the current x and the last x position
	camDiffy = 0;// = y-lasty; //check the difference between the current y and the last y position

	if(camMouseClicked)
	{
		camDiffx = x-camLastx; //check the difference between the current x and the last x position
		camDiffy = y-camLasty; //check the difference between the current y and the last y position
	}

	camLastx=x; //set lastx to the current x position
	camLasty=y; //set lasty to the current y position

	camXrot += (float) camDiffy; //set the xrot to xrot with the addition of the difference in the y position
	camYrot += (float) camDiffx; //set the yrot to yrot with the addition of the difference in the x position

	if(camXrot > camMaxAngle) //restrict maximum vertical camera angle to 45 degrees
		camXrot = camMaxAngle;
	else if(camXrot < camMinAngle) //restrict minimum vertical camera angle to 5 degrees
		camXrot = camMinAngle;
}

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
/*	void LevelOneController::CreateBoundingBoxes()
{
	//outer level walls - needs more work, can escape in the corners!
	cam.SetAABB(0, -100, 0, 0, 0, 0, 5000);
	cam.SetAABB(1, 5000, 5100, 0, 0, 0, 5000);
	cam.SetAABB(2, 0, 5000, 0, 0, -100, 0);
	cam.SetAABB(3, 0, 5000, 0, 0, 5000, 5100);
}*/

//--------------------------------------------------------------------------------------
// Load and Create Textures
//--------------------------------------------------------------------------------------
void LevelOneController::CreateTextures() //ray, we don't need that if we implemented the texturemanager, because all the texture should be loaded in the texturemanager
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// set texture count
	tp.SetTextureCount(LAST); //NEEDS TO BE THE SAME ACROSS ALL CONTROLLERS!!! (else textures assigned randomly)
	unsigned char* image;
	// load and create textures

	image = tp.LoadTexture("textures/thanks.raw", 512, 512);
	tp.CreateTexture(EXIT, image, 512, 512);

	image = tp.LoadTexture("textures/box.raw", 512, 512);
	tp.CreateTexture(BOX, image, 512, 512);

	image = tp.LoadTexture("textures/tilefloor.bmp", 512, 512);
	tp.CreateTexture(TILEFLOOR, image, 512, 512);

	image = tp.LoadTexture("textures/concwall.bmp", 512, 512);
	tp.CreateTexture(CONCWALL, image, 512, 512);

	image = tp.LoadTexture("textures/rustywall.raw", 512, 256); //bad  texture, not sure where used :S *JM
	tp.CreateTexture(RUSTYWALL, image, 512, 256);

	image = tp.LoadTexture("textures/tilewall.bmp", 512, 512);
	tp.CreateTexture(TILEWALL, image, 512, 512);

	image = tp.LoadTexture("textures/4x1platform.png", 512, 512);
	tp.CreateTexture(PLATFORM4X1, image, 512, 512);

	image = tp.LoadTexture("textures/button.bmp", 512, 512);
	tp.CreateTexture(BUTTON, image, 512, 512);

	image = tp.LoadTexture("textures/bomb.bmp", 512, 512);
	tp.CreateTexture(BOMB, image, 512, 512);

	image = tp.LoadTexture("textures/console.bmp", 512, 512);
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
		GetModel()->drawModel(mButton, tp.GetTexture(BUTTON)); //ray, jon, don't do it like this!
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
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PLATFORM4X1));
		glTranslatef(2500, 0, 4250);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2250, 450, 1500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glTranslatef(500, 0, -1250);
		glRotatef(180, 0, 1, 0);
		GetModel()->drawModel(mConsole, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(CONSOLE)); //*JW
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
		glBindTexture(GL_TEXTURE_2D,GetTexture()->getTextureID(taWelcome)); // tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (5.0, 5.0);		glVertex3f(0, 0, 0);
			glTexCoord2f (0.0, 5.0);		glVertex3f(0, 0, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 0,	5000);
			glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 0, 0);
		glEnd();

		//ceiling
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(TILEFLOOR));
		glBegin(GL_QUADS);
			glTexCoord2f (5.0, 5.0);		glVertex3f(0, 2000,	0);
			glTexCoord2f (0.0, 5.0);		glVertex3f(0, 2000, 5000);
			glTexCoord2f (0.0, 0.0);		glVertex3f(5000, 2000, 5000);
			glTexCoord2f (5.0, 0.0);		glVertex3f(5000, 2000, 0);
		glEnd();

		//walls
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); // tp.GetTexture(TILEWALL));
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
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(CONCWALL));
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
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(TILEFLOOR));
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
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(CONCWALL));
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
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); // tp.GetTexture(CONCWALL));
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
		glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(CONCWALL));
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
	DrawManager drawMan; //jon, we should not create the drawmanager in the draw function! use the drawmanager provided in the base class!
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); // tp.GetTexture(TILEFLOOR));

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

	glBindTexture(GL_TEXTURE_2D,GetTexture()->getTextureID(taWelcome)); // tp.GetTexture(TILEFLOOR));
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

	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(CONCWALL));
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
	
	DrawManager drawMan; //jon, don't create that object over and over again!
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(TILEFLOOR));
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


//--------------------------------------------------------------------------------------
//  RF: Enables depth testing, lighting and shading model
//--------------------------------------------------------------------------------------
void LevelOneController::Enable(void) 
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}


//--------------------------------------------------------------------------------------
//  RF: Controls key presses
//--------------------------------------------------------------------------------------
void LevelOneController::KeyOperations(void)
{
	if(camKeyStates['q'])
	{
		camYrotrad = (camYrot / 180 * 3.141592654f);
		camXpos -= float(cos(camYrotrad)) * camSpeed;
		camZpos -= float(sin(camYrotrad)) * camSpeed;
		
	}

	if(camKeyStates['e'])
	{
		camYrotrad = (camYrot / 180 * 3.141592654f);
		camXpos += float(cos(camYrotrad)) * camSpeed;
		camZpos += float(sin(camYrotrad)) * camSpeed;
	}

	if(camKeyStates['r'])
	{
		if(camXrot < camMaxAngle) //restrict maximum vertical camera angle to 45 degrees
			camXrot += 1;
	}

	if(camKeyStates['f'])
	{
		if(camXrot > camMinAngle) //restrict minimum vertical camera angle to 5 degrees
			camXrot -= 1;
	}

	if(camKeyStates['w'])
	{
		camYrotrad = (camYrot / 180 * 3.141592654f);
		camXrotrad = (camXrot / 180 * 3.141592654f); 
		camXpos += float(sin(camYrotrad)) * camSpeed;
		camZpos -= float(cos(camYrotrad)) * camSpeed;
		camYpos -= float(sin(camXrotrad)) * camSpeed;
	}

	if(camKeyStates['s'])
	{
		camYrotrad = (camYrot / 180 * 3.141592654f);
		camXrotrad = (camXrot / 180 * 3.141592654f); 
		camXpos -= float(sin(camYrotrad)) * camSpeed;
		camZpos += float(cos(camYrotrad)) * camSpeed;
		camYpos += float(sin(camXrotrad)) * camSpeed;
	}

	if(camKeyStates['a'])
	{
		camYrot += -1.0f;
	}

	if(camKeyStates['d'])
	{
		camYrot += 1.0f;
	}

	if(camSpecialKeyStates[0])
	{
		camYrot += -1.0f;
	}

	if(camSpecialKeyStates[1])
	{
		camYrot += 1.0f;
	}

	if(camSpecialKeyStates[2])
	{
		camYrotrad = (camYrot / 180 * 3.141592654f);
		camXrotrad = (camXrot / 180 * 3.141592654f); 
		camXpos += float(sin(camYrotrad)) * camSpeed;
		camZpos -= float(cos(camYrotrad)) * camSpeed;
		camYpos -= float(sin(camXrotrad)) * camSpeed;
	}

	if(camSpecialKeyStates[3])
	{
		camYrotrad = (camYrot / 180 * 3.141592654f);
		camXrotrad = (camXrot / 180 * 3.141592654f); 
		camXpos -= float(sin(camYrotrad)) * camSpeed;
		camZpos += float(cos(camYrotrad)) * camSpeed;
		camYpos += float(sin(camXrotrad)) * camSpeed;
	}
}
