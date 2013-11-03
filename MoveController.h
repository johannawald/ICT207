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
#include "ModelManager.h"
#include "TextureManager.h"

class DrawManager;
class MoveController
{
	private:
		DrawManager* mDrawManager; /**< Pointer to the DrawManager*/
		BoundingBox mCameraBB; /**< The camera bounding box for collision detection*/
		Vector3D mPos; /**< The camera position*/
		Vector3D mStartPosition; /**< The camera's initial position*/
		Vector3D mPosDiff; /**< The coordinates of the desired camera position*/
		Timer mTimer; /**< Timer variable used to normalise camera speed*/
		float mSpeed; /**< The camera speed*/
		float mCameraRotation; /**< The direction to face the camera*/
		float mXrot; /**< Amount to rotate on the x-axis*/
		float mYrot; /**< Amount to rotate on the y-axis*/
		float mRadius; /**< The distance from the character to the camera*/
		float mMaxAngle; /**< Maximum camera vertical angle*/
		float mMinAngle; /**< Minimum camera vertical angle*/
		float mLastx; /**< Last mouse x-position*/
		float mLasty; /**< Last mouse y-position*/
		float mXrotrad; /**< The amount to rotate on the x-axis*/
		float mYrotrad; /**< The amount to rotate on the y-axis*/
		int mDiffx; /**< Value of the difference between the curren and last x position*/
		int mDiffy; /**< Value of the difference between the current and last y position*/
		bool mMouseClicked; /**< Flag for whether or not the mouse button is clicked (true = mouse clicked, false = mouse not clicked*/
		bool mKeyStates[256]; /**< Tracks the states of keyboard keys (true = key pressed, false = key not pressed)*/
		bool mSpecialKeyStates[4]; /**< Tracks the states of special arrow keys (true = key pressed, false = key not pressed*/
		
			/**
             * @brief Enables Depth Test and Shading.
             *
             * @param none
			 * @return void
             */
		void Enable(void);

			/**
             * @brief Handles all key presses.
             *
			 * Handles all key presses by tracking their current state and 
			 * taking the appropriate action if the key is currently in the 
			 * down position.
			 *
             * @param none
			 * @return void
             */
		void KeyOperations(void);

			/**
             * @brief Resets the difference values for the camera position
             *
             * @param none
			 * @return void
             */
		void ResetDiffValues();

			/**
             * @brief Sets the camera positions.
			 * 
			 * Sets the camera positions as a product of the time difference
			 * to normalise camera speed.
			 *
			 * @param const float pDeltaTime - time difference between frames
			 * @return void
             */
		void SetPosDiff(const float pDeltaTime);

	public:
			/**
             * @brief Default constructor creates a new camera object
			 *
			 * @param none
             */
		MoveController();

			/**
             * @brief Get the desired camera position
			 *
			 * @param none
			 * @return Vector3D& mPosDiff
             */
		const Vector3D& GetposDiff() const;

			/**
             * @brief Get the current camera position
			 *
			 * @param none
			 * @return Vector3D& mPos
             */
		const Vector3D& Getpos() const;

			/**
             * @brief Move the camera to its start position
			 *
			 * @param none
			 * @return void
             */
		void SetCameraPosition();

			/**
             * @brief Move the camera to the desired position
			 *
			 * @param none
			 * @return void
             */
		void MoveCamera(const ModelManager& pModelManager, const TextureManager& pTextureManager);


			/**
             * @brief Prepares the camera for movement
			 * 
			 * Prepares the camera for movement by waiting for input from mouse or keyboard 
			 * and setting coordinates and rotation for desired movement.
			 *
			 * @param float xpos - the camera's x position
			 * @param float ypos - the camera's y position
			 * @param float zpos - the camera's z position
			 * @param float rotation - the camera's rotation
			 * @return void
             */
		void PrepareMovement(float xpos, float ypos, float zpos, float rotation);

			/**
             * @brief Set the camera positions
			 *
			 * @param float x - the x position
			 * @param float y - the y position
			 * @param float z - the z position
			 * @return void
             */
		void SetDiffValues(float x, float y, float z);

			/**
             * @brief Function to be passed as glutSpecialFunc()
			 *
			 * @param int key - the key that was pressed
			 * @param int x - the mouse x position
			 * @param int y - the mouse y position
			 * @return void
             */
		void SpecialKey(int key, int x, int y);

			/**
             * @brief Function to be passed as glutSpecialUpFunc()
			 *
			 * @param int key - the key that was released
			 * @param int x - the mouse x position
			 * @param int y - the mouse y position
			 * @return void
             */
		void SpecialKeyUp(int key, int x, int y);

			/**
             * @brief Function to be passed as glutKeyboardFunc()
			 *
			 * @param unsigned char key - the key that was pressed
			 * @param int x - the mouse x position
			 * @param int y - the mouse y position
			 * @return void
             */
		void Keyboard(unsigned char key, int x, int y);

			/**
             * @brief Function to be passed as glutKeyboardUpFunc()
			 *
			 * @param unsigned char key - the key that was released
			 * @param int x - the mouse x position
			 * @param int y - the mouse y position
			 * @return void
             */
		void KeyboardUp(unsigned char key, int x, int y);

			/**
             * @brief Function to be passed as glutMouseFunc()
			 *
			 * @param int button - the mouse button clicked
			 * @param int x - the mouse x position
			 * @param int y - the mouse y position
			 * @return void
             */
		void Mouse(int button, int state, int x, int y);

			/**
             * @brief Function to be passed as glutMotionFunc()
			 *
			 * @param int x - the mouse x position
			 * @param int y - the mouse y position
			 * @return void
             */
		void MouseMotion(int x, int y);

			/**
             * @brief Returns the camera's bounding box for collision
			 *
			 * @param none
			 * @return const BoundingBox& mCameraBB
             */
		const BoundingBox& GetCameraBB() const;
};
#endif //end of MoveController class