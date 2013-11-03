#include "MoveController.h"
#include "DrawManager.h"
#include <iostream>

MoveController::MoveController()
{
	// intialise camera values
	mStartPosition.x = 0;
	mStartPosition.y = 0;
	mStartPosition.z = 0;
	mCameraRotation = 0;

	mSpeed = 100.0; 
	mPos.x = 0.0; 
	mPos.y = 0.0; 
	mPos.z = 0.0; 
	mXrot = 0.0; 
	mYrot = 0.0;
	mPosDiff.x = 0.0;
	mPosDiff.y= 0.0;  
	mPosDiff.z = 0.0;
	mRadius = 300.0f;
	mMaxAngle = 45.0;
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
	mDrawManager = new DrawManager();
	mCameraBB.SetBoundingBox(mPos, Vector3D(100.0f, 100.0f, 100.0f));
}

void MoveController::SetCameraPosition()
{
	glRotatef(mCameraRotation, 0.0, 1.0, 0.0); //rotate camera 180 degrees
	glTranslatef(mStartPosition.x, mStartPosition.y, mStartPosition.z); //translate camera starting position
}

void MoveController::PrepareMovement(float xpos, float ypos, float zpos, float rotation) //const
{
	mStartPosition.x = xpos;
	mStartPosition.y = ypos;
	mStartPosition.z = zpos;
	mCameraRotation = rotation;
	// enable depth testing, lighting and shading
	Enable();
	// check for movement
	KeyOperations();
	double deltaTime = mTimer.Duration();
	mTimer.Reset();
	SetPosDiff(deltaTime);
}

void MoveController::SetDiffValues(float x, float y, float z)
{
	mPosDiff.x = x;
	mPosDiff.y = y;
	mPosDiff.z = z;
}

void MoveController::SetPosDiff(const float pDeltaTime)
{
	mPosDiff.x *= pDeltaTime;
	mPosDiff.y *= pDeltaTime;
	mPosDiff.z *= pDeltaTime;
}

void MoveController::MoveCamera()  //try to avoid updating variables in the draw function! -> do that in the update-funciton
{		

	mPos.x += mPosDiff.x;
	mPos.z += mPosDiff.z;

	ResetDiffValues();
	glTranslatef(0.0f, 0.0f, -mRadius);
	
	glRotatef(mXrot,1.0,0.0,0.0);
	
	glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
			glRotatef(0, 1, 0, 0);
			glColor3f(1.0f, 0.0f, 0.0f);
			//glutSolidCube(50); //Our character to follow - WILL CHANGE TO CHARACTER
		glPopMatrix();
	glPopAttrib();
    
	glRotatef(mYrot,0.0,1.0,0.0);  //rotate the camera on the y-axis (up and down)

	mCameraBB.Translate(mPos);
	mCameraBB.Move(mPosDiff);
	glTranslated(-mPos.x, 0.0f, -mPos.z); //translate the screen to the position of our camera
	//glTranslated(-mPos.x, -mPos.y, -mPos.z); //translate the screen to the position of our camera
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
		mPosDiff.x -= float(cos(mYrotrad)) * mSpeed;
		mPosDiff.z -= float(sin(mYrotrad)) * mSpeed;
	}

	if(mKeyStates['e'])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mPosDiff.x += float(cos(mYrotrad)) * mSpeed;
		mPosDiff.z += float(sin(mYrotrad)) * mSpeed;
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
		mPosDiff.x += float(sin(mYrotrad)) * mSpeed;
		mPosDiff.z -= float(cos(mYrotrad)) * mSpeed;
		mPosDiff.y -= float(sin(mXrotrad)) * mSpeed;
	}

	if(mKeyStates['s'])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXrotrad = (mXrot / 180 * 3.141592654f); 
		mPosDiff.x -= float(sin(mYrotrad)) * mSpeed;
		mPosDiff.z += float(cos(mYrotrad)) * mSpeed;
		mPosDiff.y += float(sin(mXrotrad)) * mSpeed;
	}

	if(mKeyStates['a'])
	{
		if(!mMouseClicked)
		{
			mYrot += -1.0f; //rotate view left if mouse not clicked
		}
		else
		{
			//strafe left if mouse is clicked
			mYrotrad = (mYrot / 180 * 3.141592654f);
			mPosDiff.x -= float(cos(mYrotrad)) * mSpeed;
			mPosDiff.z -= float(sin(mYrotrad)) * mSpeed;
		}

	}

	if(mKeyStates['d'])
	{
		if(!mMouseClicked)
		{
			mYrot += 1.0f; //rotate view right if mouse not clicked
		}
		else
		{
			//strafe right if mouse is clicked
			mYrotrad = (mYrot / 180 * 3.141592654f);
			mPosDiff.x += float(cos(mYrotrad)) * mSpeed;
			mPosDiff.z += float(sin(mYrotrad)) * mSpeed;
		}
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
		mPosDiff.x += float(sin(mYrotrad)) * mSpeed;
		mPosDiff.z -= float(cos(mYrotrad)) * mSpeed;
		mPosDiff.y -= float(sin(mXrotrad)) * mSpeed;
	}

	if(mSpecialKeyStates[3])
	{
		mYrotrad = (mYrot / 180 * 3.141592654f);
		mXrotrad = (mXrot / 180 * 3.141592654f); 
		mPosDiff.x -= float(sin(mYrotrad)) * mSpeed;
		mPosDiff.z += float(cos(mYrotrad)) * mSpeed;
		mPosDiff.y += float(sin(mXrotrad)) * mSpeed;
	}

	if(mKeyStates['o'])
	{
		mPosDiff.y += 1.0f * mSpeed;
	}
	if(mKeyStates['l'])
	{
		mPosDiff.y -= 1.0f * mSpeed;
	}
	//should not be used
	mPosDiff.y= 0.0;  
}

void MoveController::ResetDiffValues()
{
	mPosDiff.x = 0;
	mPosDiff.y = 0;
	mPosDiff.z = 0;
}


const Vector3D& MoveController::GetposDiff() const
{
	return mPosDiff; 
}

const Vector3D& MoveController::Getpos() const
{
	return mPos;
}

const BoundingBox& MoveController::GetCameraBB() const
{
	return mCameraBB;
}