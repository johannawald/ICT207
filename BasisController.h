/**
 * @class BasisController
 * @brief The BasisController provides all the basic functionality
 *
 * It holds variables for the audio-, the model- and the texturemanager
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

#include "ModelManager.h"
#include "AudioManager.h"
#include "DrawManager.h"
#include "TextureManager.h"

class BasisController {
private:
	// ratio of screen
	float mRatio;
	// screen width and height
	int mScreenWidth, mScreenHeight;

	DrawManager* mDrawManager; /**<  Provides help functions to draw (such as drawing Text)*/
	AudioManager* mAudioManager; /**<  Stores a list of audios and allows to play them */
	ModelManager* mModelManager; /**< Stores a list of models and allows to draw them */
	TextureManager* mTextureManager; /**< Stores a list of textures and provides a function that returns the TextureID */
protected:
	bool pLoaded; //not sure if we can change that

	virtual void Reshape(int pWidth, int pHeight);
	virtual void Reshape();
	virtual void Init();
	virtual void Draw();
	virtual void DrawObjects() = 0;

	/**
		* @brief GetMethod of the AudioManager member variable
		*
		* Returns the audiomanager
     	*
	    * @param none
		* @return AudioManager* - the stored member variable
    */
	AudioManager* GetAudio() const;
	/**
    * @brief GetMethod of the ModelManager member variable
		*
		* Returns the modelmanager
     	*
	    * @param none
		* @return ModelManager* - the stored member variable
    */
	ModelManager* GetModel() const;
	/**
    * @brief GetMethod of the TextureManager member variable
		*
		* Returns the texturemanager
     	*
	    * @param none
		* @return TextureManager* - the stored member variable
    */
	TextureManager* GetTexture() const;

	/**
    * @brief GetMethod of the TextureManager member variable "drawmanager"
		*
		* Returns the drawmanager member variable
     	*
	    * @param none
		* @return DrawManager*: the membervariable DrawManager*
    */
	DrawManager* GetDrawManager();

	int GetWindowWidth();
	int GetWindowHeight();

public:	
	/**
    * @brief constructor of the BasisController
		*
		* initialized the member variables audio, model and texture
     	*
	    * @param AudioManager* audiomanager, ModelManager* modelmanager, TextureManager* texturemanager - the new value of the member variables
		* @return void
    */
	BasisController(AudioManager* pAudioManager, ModelManager* pModelManager, TextureManager* pTextureManager); 
};
