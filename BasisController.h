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
	DrawManager* drawmanager; /**<  Provides help functions to draw (such as drawing Text)*/
	AudioManager* audio; /**<  Stores a list of audios and allows to play them */
	ModelManager* model; /**< Stores a list of models and allows to draw them */
	TextureManager* texture; /**< Stores a list of textures and provides a function that returns the TextureID */
protected:
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
    * @brief SetMethod of the TextureManager member variable
		*
		* Sets the texturemanager member variable to the value of the parameter
     	*
	    * @param AudioManager* - the new value of the member variable "audio"
		* @return void
    */
	void SetAudio(AudioManager* am);
	/**
    * @brief SetMethod of the ModelManager member variable
		*
		* Sets the modelmanager member variable to the value of the parameter
     	*
	    * @param ModelManager* - the new value of the member variable "model"
		* @return void
    */
	void SetModel(ModelManager* mm);
	/**
    * @brief SetMethod of the TextureManager member variable
		*
		* Sets the texturemanager member variable to the value of the parameter
     	*
	    * @param TextureManager* - the new value of the member variable "texture"
		* @return void
    */
	void SetTexture(TextureManager* tm);
public:	
	/**
    * @brief constructor of the BasisController
		*
		* initialized the member variables audio, model and texture
     	*
	    * @param AudioManager* audiomanager, ModelManager* modelmanager, TextureManager* texturemanager - the new value of the member variables
		* @return void
    */
	BasisController(AudioManager* audiomanager, ModelManager* modelmanager, TextureManager* texturemanager); 
};
