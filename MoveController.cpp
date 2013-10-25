//--------------------------------------------------------------------------------------
// ModelLoader.cpp
// Implementation file for the MoveController class
// Controls camera using keyboard and mouse input.
//
// Author: Raymond Forster
// Version: 1
// Date 25/10/2013 Raymond Forster - Started
//--------------------------------------------------------------------------------------

#include "MoveController.h"

MoveController::MoveController()
{
	// intialise camera values
	mSpeed = 5.0;
	mXpos = 0.0; 
	mYpos = 0.0; 
	mZpos = 0.0; 
	mXrot = 0.0; 
	mYrot = 0.0;
	mXposDiff = 0.0;
	mYposDiff = 0.0;  
	mZposDiff = 0.0;
	mRadius = 500.0f;
	mMaxAngle = 35.0;
	mMinAngle = 0.0;
	mYrotrad;
	mXrotrad;
	mMouseClicked = false;
	mLastx = glutGet(GLUT_WINDOW_WIDTH)/2.0f; 
	mLasty = glutGet(GLUT_WINDOW_HEIGHT)/2.0f;

	//set camera key states to false (not pressed)
	for(int i=0; i<256; i++)
	{
		mKeyStates[i] = false;
	}

	//set camera special key states (arrow keys) to false (not pressed)
	for(int i=0; i<4; i++)
	{
		mSpecialKeyStates[i] = false;
	}
}


float MoveController::GetXpos()
{
	return mXpos;
}


float MoveController::GetYpos()
{
	return mYpos;
}


float MoveController::GetZpos()
{
	return mZpos;
}

float MoveController::GetXposDiff()
{
	return mXposDiff;
}

float MoveController::GetYposDiff()
{
	return mYposDiff;
}

float MoveController::GetZposDiff()
{
	return mZposDiff;
}

void MoveController::SetCameraPosition(float xpos, float ypos, float zpos, float rotation)
{
	glRotatef(rotation, 0.0, 1.0, 0.0); //rotate camera 180 degrees
	glTranslatef(xpos, ypos, zpos); //translate camera starting position
}

void MoveController::PrepareMovement()
{
	// enable depth testing, lighting and shading
	Enable();
	// check for movement
	KeyOperations();
}

void MoveController::SetDiffValues(float x, float y, float z)
{
	mXposDiff = x;
	mYposDiff = y;
	mZposDiff = z;
}

void MoveController::MoveCamera()  //try to avoid updating variables in the draw function! -> do that in the update-funciton
{		
	mXpos += mXposDiff;
	mYpos += mYposDiff;
	mZpos += mZposDiff;

	ResetDiffValues();
	glTranslatef(0.0f, -100.0f, -mRadius);
	glRotatef(mXrot,1.0,0.0,0.0);

	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidSphere(100, 12, 12); //Our character to follow - WILL CHANGE TO CHARACTER
	glPopMatrix();
    
	glRotatef(mYrot,0.0,1.0,0.0);  //rotate the camera on the y-axis (up and down)
	/*if (!pMoveX) 
		mXpos = 0;
	if (!pMoveY) 
		mYpos = 0;
	if (!pMoveZ) 
		mZpos = 0;*/

	glTranslated(-mXpos,-mYpos,-mZpos); //translate the screen to the position of our camera
	glColor3f(1.0f, 1.0f, 1.0f);	
}


void MoveController::SpecialKey(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
			mSpecialKeyStates[0] = true;
			break;

		case GLUT_KEY_RIGHT :
			mSpecialKeyStates[1] = true;
			break;

		case GLUT_KEY_UP : 
			mSpecialKeyStates[2] = true;
			break;

		case GLUT_KEY_DOWN : 
			mSpecialKeyStates[3] = true;
			break;
	}
}


void MoveController::SpecialKeyUp(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
			mSpecialKeyStates[0] = false;
			break;

		case GLUT_KEY_RIGHT :
			mSpecialKeyStates[1] = false;
			break;

		case GLUT_KEY_UP : 
			mSpecialKeyStates[2] = false;
			break;

		case GLUT_KEY_DOWN : 
			mSpecialKeyStates[3] = false;
			break;
	}
}


void MoveController::Keyboard(unsigned char key, int x, int y)
{
	mKeyStates[key] = true; // Set the state of the current key to pressed
}


void MoveController::KeyboardUp(unsigned char key, int x, int y)
{
	mKeyStates[key] = false; // Set the state of the current key to not pressed
}


void MoveController::Mouse(int button, int state, int x, int y)
{
	mLastx = (float)x; //set lastx to the current x position
	mLasty = (float)y; //set lasty to the current y position
	
	if((button == GLUT_LEFT_BUTTON) || (button == GLUT_RIGHT_BUTTON)) 
	{
		mMouseClicked = (state == GLUT_DOWN);
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


void MoveController::MouseMotion(int x, int y)
{
	mDiffx = 0;// = x-lastx; //check the difference between the current x and the last x position
	mDiffy = 0;// = y-lasty; //check the difference between the current y and the last y position

	if(mMouseClicked)
	{
		mDiffx = x-(int)mLastx; //check the difference between the current x and the last x position
		mDiffy = y-(int)mLasty; //check the difference between the current y and the last y position
	}

	mLastx = (float)x; //set lastx to the current x position
	mLasty = (float)y; //set lasty to the current y position

	mXrot += (float) mDiffy; //set the xrot to xrot with the addition of the difference in the y position
	mYrot += (float) mDiffx; //set the yrot to yrot with the addition of the difference in the x position

	if(mXrot > mMaxAngle) //restrict maximum vertical camera angle to 45 degrees
		mXrot = mMaxAngle;
	else if(mXrot < mMinAngle) //restrict minimum vertical camera angle to 5 degrees
		mXrot = mMinAngle;
}


void MoveController::Enable(void) 
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}


void MoveController::KeyOperations(void)
{
	if(mKeyStates['q'])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXposDiff -= float(cos(mYrotrad)) * mSpeed;
		mZposDiff -= float(sin(mYrotrad)) * mSpeed;
	}

	if(mKeyStates['e'])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXposDiff += float(cos(mYrotrad)) * mSpeed;
		mZposDiff += float(sin(mYrotrad)) * mSpeed;
	}

	if(mKeyStates['r'])
	{
		if(mXrot < mMaxAngle) //restrict maximum vertical camera angle to 45 degrees
			mXrot += 1;
	}

	if(mKeyStates['f'])
	{
		if(mXrot > mMinAngle) //restrict minimum vertical camera angle to 5 degrees
			mXrot -= 1;
	}

	if(mKeyStates['w'])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXrotrad = (mXrot / 180 * 3.141592654f); 
		mXposDiff += float(sin(mYrotrad)) * mSpeed;
		mZposDiff -= float(cos(mYrotrad)) * mSpeed;
		mYposDiff -= float(sin(mXrotrad)) * mSpeed;
	}

	if(mKeyStates['s'])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXrotrad = (mXrot / 180 * 3.141592654f); 
		mXposDiff -= float(sin(mYrotrad)) * mSpeed;
		mZposDiff += float(cos(mYrotrad)) * mSpeed;
		mYposDiff += float(sin(mXrotrad)) * mSpeed;
	}

	if(mKeyStates['a'])
	{
		mYrot += -1.0f;
	}

	if(mKeyStates['d'])
	{
		mYrot += 1.0f;
	}

	if(mSpecialKeyStates[0])
	{
		mYrot += -1.0f;
	}

	if(mSpecialKeyStates[1])
	{
		mYrot += 1.0f;
	}

	if(mSpecialKeyStates[2])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXrotrad = (mXrot / 180 * 3.141592654f); 
		mXposDiff += float(sin(mYrotrad)) * mSpeed;
		mZposDiff -= float(cos(mYrotrad)) * mSpeed;
		mYposDiff -= float(sin(mXrotrad)) * mSpeed;
	}

	if(mSpecialKeyStates[3])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXrotrad = (mXrot / 180 * 3.141592654f); 
		mXposDiff -= float(sin(mYrotrad)) * mSpeed;
		mZposDiff += float(cos(mYrotrad)) * mSpeed;
		mYposDiff += float(sin(mXrotrad)) * mSpeed;
	}

	if(mKeyStates['o'])
	{
		mYposDiff += 1.0f * mSpeed;
	}
	if(mKeyStates['l'])
	{
		mYposDiff -= 1.0f * mSpeed;
	}
}

void MoveController::ResetDiffValues()
{
	mXposDiff = 0;
	mYposDiff = 0;
	mZposDiff = 0;
}
