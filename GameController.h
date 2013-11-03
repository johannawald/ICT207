/**
 * @class GameController
 * @brief The GameController should manage the Game itself
 *
 * The GameController should later manage the game itself with it levels 
 * and settings and stuff like that
 *
 * @author Johanna Wald
 * @version 01
 * @date 15/09/2013 Johanna Wald - set up class
 * @date 01/10/2013 Johanna Wald - added all the gamecontroller basic functions
 * @date 10/10/2013 Johanna Wald - changed base class to BasisGameController

 */

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include "texturedPolygons.h"
#include "IStateController.h"
#include "BasisGameController.h"
#include "CollisionDetection.h"
#include "GameObject.h"
#include "MoveController.h"
#include "Explosion.h"

class GameController : public IStateController, public BasisGameController
{
private:
	Explosion mExplosion; //member variable for the explsion-class
	const bool mSoundOn; //const variable to active the sounds

	bool mLostAnimation; //variable for triggering the lost animation
	bool mBombSoundPlaying; //variable that saves the state of the bomb sound
	const int c_mLostTime; //variable for showing the game over screen after x seconds (time of the animation)

	const bool ObjectIsBox(const int pIndex) const;
	const bool ObjectIsBomb(const int pIndex) const;
	
	virtual void DrawObjects();
	virtual void InitGameObjects();
protected:
	int mBombIndex;

	/**
		* @brief placeholder / helping variable for the Collision Index in the draw functions of the derived classes
	*/
	int mCollisionIndex;
		/**
         * @brief array of ints that saves the collision boxes of the boxes
		 */
	int* mBoxesCollisionIndex;
		/**
         * @brief draws the current timer in the left edge of the screen
		 * @param none
	  	 * @return void
		 */
	void DrawTimer();

	void SetNewExplosion(const float x, const float y, const float z);
public:
		/**
        * @brief constructor creates a new GameController object.
		*/
	GameController(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture);
	int CheckCollision();
	virtual void BeforeCollision(int pIndex, float pCollisionValue);
	
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void Reshape(int w, int h);
	virtual void SpecialKey(int key, int x, int y);
	virtual void SpecialKeyUp(int key, int x, int y);
	virtual void KeyboardUp(unsigned char key, int x, int y);
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void Mouse(int button, int state, int x, int y);
	virtual void PassiveMotion(int x, int y);
	virtual void MouseMotion(int x, int y);
};
