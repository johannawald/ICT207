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

class MoveController
{
	private:
		float mSpeed;
		// angle of rotation values
		float mXpos;  
		float mYpos;  
		float mZpos;  
		float mXrot; 
		float mYrot; 
	
		// distance from character
		float mRadius; 

		// max and min camera angle
		float mMaxAngle; 
		float mMinAngle; 
		float mLastx; // last mouse x position // last mouse y position
		float mLasty; 
		int mDiffy;
		int mDiffx;
		float mYrotrad;
		float mXrotrad;
		bool mMouseClicked;
		bool mKeyStates[256]; 
		bool mSpecialKeyStates[4];
		void Enable(void);
		void KeyOperations(void);
		
	public:
		MoveController();
		float GetXpos();
		float GetYpos();
		float GetZpos();
		void SetCameraPosition(float xpos, float ypos, float zpos, float rotation);
		void MoveCamera(const bool pMoveX = true, const bool pMoveY = true, const bool pMoveZ = true);
		void SpecialKey(int key, int x, int y);
		void SpecialKeyUp(int key, int x, int y);
		void KeyboardUp(unsigned char key, int x, int y);
		void Keyboard(unsigned char key, int x, int y);
		void Mouse(int button, int state, int x, int y);
		void MouseMotion(int x, int y);
};
#endif //end of MoveController class