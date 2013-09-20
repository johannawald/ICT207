/**
 * @class GameController
 * @brief The GameController should manage the Game itself
 *
 * The GameController should later manage the game itself with it levels 
 * and settings and stuff like that
 *
 * @author Johanna Wald
 * @version 01
 * @date 15/09/2013
 */

#pragma once

#include "IStateController.h"
#include "BasisController.h"
#include "AudioManager.h"
#include "ModelManager.h"
#include "TextureManager.h"

class GameController : public IStateController, BasisController
{
public:
	GameController(AudioManager* am, ModelManager* mm, TextureManager* tm);
	/**
		* @brief init-function, functionality yet to be implemented
	*/
	void Init(const ModelManager* mm, const AudioManager* am, const TextureManager* tm);
	/**
		* @brief draw function for the game state, functionality yet to be implemented
	*/
	void Draw();
	/**
		* @brief update function for the game state, functionality yet to be implemented
	*/
	void Update();
	/**
		* @brief SpecialKey function for the game state, functionality yet to be implemented
	*/
	void SpecialKey(int key, int x, int y);
	/**
		* @brief SpecialKeyUp function for the state, functionality yet to be implemented
	*/
	void SpecialKeyUp(int key, int x, int y);
	/**
		* @brief KeyboardUp function for the state, functionality yet to be implemented
	*/
	void KeyboardUp(unsigned char key, int x, int y);
	/**
		* @brief Keyboard function for the state, functionality yet to be implemented
	*/
	void Keyboard(unsigned char key, int x, int y);
	/**
		* @brief Mouse function for the state, functionality yet to be implemented
	*/
	void Mouse(int button, int state, int x, int y);
	/**
		* @brief PassiveMotion function for the state, functionality yet to be implemented
	*/	
	void PassiveMotion(int x, int y);
	/**
		* @brief Reshape function for the state, functionality yet to be implemented
	*/	
	void Reshape(int w, int h);
};
