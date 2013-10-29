/**
 * @class MoveController
 * @brief Controls camera using keyboard and mouse input.
 *
 * @author Raymond Forster
 * @version 1
 * @date 25/10/2013 Raymond Forster - Started
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

class DrawManager;
class MoveController
{
	private:
		const bool mJump;
		DrawManager* mDrawManager;
		BoundingBox* mCameraBB; //we need that later!
		float mSpeed;
		// angle of rotation values
		Vector3D mPos;
		Vector3D mStartPosition;
		/*float mXpos;  
		float mYpos;  
		float mZpos;*/ 

		Vector3D mPosDiff;
		Vector3D mCameraTranslation;
		float mCameraRotation;
		/*float mXposDiff;  
		float mYposDiff;  
		float mZposDiff; */

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
	public:
		MoveController();
	/*	float GetXpos();
		float GetYpos();
		float GetZpos();
		float GetXposDiff();
		float GetYposDiff();
		float GetZposDiff();*/
		const Vector3D& GetposDiff() const;
		const Vector3D& Getpos() const;
		void SetCameraPosition();
		void MoveCamera(); //const bool pMoveX = true, const bool pMoveY = true, const bool pMoveZ = true);
		void PrepareMovement(float xpos, float ypos, float zpos, float rotation);
		void SetDiffValues(float x, float y, float z);
		void SpecialKey(int key, int x, int y);
		void SpecialKeyUp(int key, int x, int y);
		void KeyboardUp(unsigned char key, int x, int y);
		void Keyboard(unsigned char key, int x, int y);
		void Mouse(int button, int state, int x, int y);
		void MouseMotion(int x, int y);
		void SetPull(const int pFactor = -1);
		BoundingBox* GetCameraBB() const;
};
#endif //end of MoveController class