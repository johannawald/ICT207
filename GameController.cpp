#include "LevelOneController.h"
#include "texturedPolygons.h"
#include "GameController.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "BushCourtController.h"
#include "DrawManager.h"
#include "Stairs.h"
#include <sstream>

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
GameController::GameController(AudioManager* am, ModelManager* mm, TextureManager* tm): BasisController(am,mm,tm), movementSpeed(15.0), rotationSpeed(0.005), loaded(false)
{
	SetGameObject(); //*JW
	frameCount = 0;
	lastClock = 0;

	Init();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)

	loaded = true;

	// intialise camera values
	camSpeed = 3.0;
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
	camLastx = glutGet(GLUT_WINDOW_WIDTH)/2; 
	camLasty = glutGet(GLUT_WINDOW_HEIGHT)/2;

	for(int i=0; i<256; i++)
	{
		camKeyStates[i] = false;
	}
}

void GameController::SetGameObject() //*JW
{
	//GameObject Box(Vector3D(2000, 0, 3500), Vector3D(0, 0, 0), Vector3D(0.75, 1.0, 0.75), mBox, 0); //johanna, collision detection!
	//mGameObject.push_back(&Box);
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void GameController::Init() 
{
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	Reshape();
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void GameController::Draw()  //try to avoid updating variables in the draw function! -> do that in the update-funciton
{
	if (loaded) 
	{
		glClearColor(0, 0, 0, 0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
		Enable();
		
		// check for movement
		//RF READ CAMERA CONTROLS
		KeyOperations();
		//glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
		//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
		
		//RF: CAMERA
		//control the camera
		glLoadIdentity();
		
		glTranslatef(0.0f, -100.0f, -camRadius);
		glRotatef(camXrot,1.0,0.0,0.0);

		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			//glColor3f(1.0f, 0.0f, 0.0f);
			//glutSolidSphere(100, 12, 12); //Our character to follow
			glutSolidCube(100);
		glPopMatrix();
    
		glRotatef(camYrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
		glTranslated(-camXpos,-camYpos,-camZpos); //translate the screen to the position of our camera
		//glColor3f(1.0f, 1.0f, 1.0f);
		// DISPLAY TEXTURES
		//enable texture mapping
		glEnable (GL_TEXTURE_2D);
		glPushMatrix();
			//glTranslatef(-500.0, -250.0, 3000.0); //translate camera starting position ??
			// displays the exit screen
			//DrawControlRoom();
			//DrawOuterWalls();
			//DrawArchitecture();
		
			//glRotatef(-90,1,0,0);
			DrawGameObjects(); //*JW
			Draw3DModels();
			//DrawObjects();
			// set the movement and rotation speed according to frame count
		glPopMatrix();
		GetDrawManager()->DrawCollisionCube(&cd, GetTexture()->getTextureID(taHallway10), 1, 1, 0, 0, 0, 100, 200, 300); 
		GetDrawManager()->DrawCollisionCube(&cd, GetTexture()->getTextureID(taHallway10), 1, 1, 10, 50, 200, 100, 20, 30);
		GetDrawManager()->DrawCollisionCube(&cd, GetTexture()->getTextureID(taHallway10), 1, 1, 100, 0, -200, 200, 4000, 200); 
		
		glDisable (GL_TEXTURE_2D); 
		DrawTexttest();
		// clear buffers
		glFlush();
		glutSwapBuffers();
	}
}

void GameController::DrawGameObjects() //*JW
{ 
	for(std::vector<GameObject*>::iterator it = mGameObject.begin(); it != mGameObject.end(); ++it) {
		glPushMatrix();
			glTranslatef((*it)->GetXPosition(), (*it)->GetYPosition(), (*it)->GetZPosition());
			glScalef((*it)->GetXScale(), (*it)->GetXScale(), (*it)->GetXScale()); 
			if ((*it)->getModelIndex()>=0)
			//	GetModel()->drawModel(mBox, tp.GetTexture(BOX));
		glPopMatrix();
	}

	//GameObject Box(Vector3D(2000, 0, 3500), Vector3D(0, 0, 0), 10, 10);
	/*

	glPushMatrix();
		glTranslatef(4250, 500, 750);
		glScalef(0.75, 1.0, 0.75);
		//GetModel()->drawModel(mBox, tp.GetTexture(BOX));
	glPopMatrix();*/
}

void GameController::DrawTexttest()
{ 
	//glMatrixMode(GL_PROJECTION);
	
	/*glLoadIdentity();
	gluOrtho2D(0, 790, 490, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Draw-Text:
	glPushMatrix();
		DrawManager dm;
		std::stringstream ss;
		ss << "X: " << camXpos << " " << " Y: " << camYpos << " " << " Z: " << camZpos << " ";
		dm.RenderString(10,10,GLUT_BITMAP_HELVETICA_18, (const char*) ss.str().c_str());
		glPushMatrix();
	glPopMatrix();
	
	// Reset Perspective Projection
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	//glMatrixMode(GL_PROJECTION);
	glPopMatrix();*/
}

int test = 0;
bool c = false;

void GameController::Update()  //this function should be used for updating variables (try to avoid updating variables in the draw function!)
{ 
	
	if (cd.Collision(camXpos, camYpos, camZpos))
	{ 
		std::cout << "collision changed: " << c << std::endl;
		test++;
	}
	c = (cd.Collision(camXpos, camYpos, camZpos));
	
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

void GameController::Reshape() 
{
	Reshape(width, height);
}

void GameController::Reshape(int w, int h) 
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
void GameController::SpecialKey(int key, int x, int y) 
{

}

//---------------------------------------------------------
void GameController::SpecialKeyUp(int key, int x, int y) 
{

}

//--------------------------------------------------------------------------------------

void GameController::Keyboard(unsigned char key, int x, int y)
{
	camKeyStates[key] = true; // Set the state of the current key to pressed
}

//--------------------------------------------------------------------------------------
void GameController::KeyboardUp(unsigned char key, int x, int y)
{
	camKeyStates[key] = false; // Set the state of the current key to not pressed
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void GameController::Mouse(int button, int state, int x, int y)
{
	camLastx = x; //set lastx to the current x position
	camLasty = y; //set lasty to the current y position
	
	if ((button == GLUT_LEFT_BUTTON) || (button == GLUT_RIGHT_BUTTON)) 
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
void GameController::PassiveMotion(int x, int y) 
{
}

void GameController::MouseMotion(int x, int y)
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
//  Draw the Objects
//--------------------------------------------------------------------------------------
void GameController::DrawObjects() 
{
	glPushMatrix();
		glTranslatef(2000, 0, 3500);
		glScalef(0.75, 1.0, 0.75);
		//GetModel()->drawModel(mBox, tp.GetTexture(BOX));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 750);
		glScalef(0.75, 1.0, 0.75);
		//GetModel()->drawModel(mBox, tp.GetTexture(BOX));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(750, 500, 750);
		//GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 1250);
		//GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4250, 500, 4250);
		//GetModel()->drawModel(mButton, tp.GetTexture(BUTTON));
	glPopMatrix();

	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOMB));
		glPushMatrix();
		glTranslatef(750, 500, 4250);
		//GetModel()->drawModel(mButton, tp.GetTexture(BUTTON)); //ray, jon, don't do it like this!
	glPopMatrix();
}


//--------------------------------------------------------------------------------------
//  Draw the 3D Models
//--------------------------------------------------------------------------------------
void GameController::Draw3DModels()
{
	glPushMatrix();
		glTranslatef(4250, 0, 2500);
		glRotatef(90, 0, 1, 0);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PLATFORM4X1));
		glTranslatef(2500, 0, 4250);
		GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(PLATFORM4X1)); //*JW
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2250, 450, 1500);
		glRotatef(90, 0, 1, 0);
		//GetModel()->drawModel(m4x1platform, GetTexture()->getTextureID(taWelcome)); //tp.GetTexture(PLATFORM4X1)); //*JW
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
void GameController::DrawOuterWalls()
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
void GameController::DrawArchitecture()
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
void GameController::DrawControlRoom()
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
//  RF: Enables depth testing, lighting and shading model
//--------------------------------------------------------------------------------------
void GameController::Enable(void) 
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}

//--------------------------------------------------------------------------------------
//  RF: Controls key presses
//--------------------------------------------------------------------------------------
void GameController::KeyOperations(void)
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

	if(camKeyStates['o'])
	{
		camYpos += 1.0f;
	}
	if(camKeyStates['l'])
	{
		camYpos -= 1.0f;
	}
}
