/**
 * @class MoveController
 * @brief Controls camera using keyboard and mouse input.
 *
 * @author Raymond Forster
 * @version 1
 * @date 25/10/2013 Raymond Forster - Started
 * @date 20/10/2013 Johanna Wald - changed movement variables to vectors
 * @date 25/10/2013 Johanna Wald - added delta time
 * @date 26/10/2013 Johanna Wald - deleted jump variables
 */

//--------------------------------------------------------------------------------------

#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

//--------------------------------------------------------------------------------------

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glut.h>
#include <stdlib.h>
#include <math.h>
#include "Vector3D.h"
#include "BoundingBox.h"
#include "Timer.h"

class DrawManager;
class MoveController
{
	private:
		Timer mTimer;	

		DrawManager* mDrawManager;
		BoundingBox mCameraBB; //we need that later!
		float mSpeed;
		
		// angle of rotation values
		Vector3D mPos;
		Vector3D mStartPosition;

		Vector3D mPosDiff;
		Vector3D mCameraTranslation;
		float mCameraRotation;

		float mXrot; 
		float mYrot; 
	
		// distance from character
		float mRadius; 

		// max and min camera angle
		float mMaxAngle; 
		float mMinAngle; 
		float mLastx; // last mouse x position 
		float mLasty; // last mouse y position
		int mDiffy;
		int mDiffx;
		float mYrotrad;
		float mXrotrad;
		bool mMouseClicked;
		bool mKeyStates[256]; 
		bool mSpecialKeyStates[4];
		void Enable(void);
		void KeyOperations(void);
		void ResetDiffValues();
		void SetPosDiff(const float pDeltaTime);
	public:
		MoveController();

		const Vector3D& GetposDiff() const;
		const Vector3D& Getpos() const;
		void SetCameraPosition();
		void MoveCamera(); 
		void PrepareMovement(float xpos, float ypos, float zpos, float rotation);
		void SetDiffValues(float x, float y, float z);
		void SpecialKey(int key, int x, int y);
		void SpecialKeyUp(int key, int x, int y);
		void KeyboardUp(unsigned char key, int x, int y);
		void Keyboard(unsigned char key, int x, int y);
		void Mouse(int button, int state, int x, int y);
		void MouseMotion(int x, int y);
		void SetPull(const int pFactor = -1);
		const BoundingBox& GetCameraBB() const;
};
#endif //end of MoveController class