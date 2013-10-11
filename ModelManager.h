/**
 * @class ModelManager
 * @brief Controller class for the model assets
 *
 * Implements the basic functions to work with model files: 
 * init(), reload(), clearMemory(), drawModel and a List to manage them
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

#include "IAssetManager.h"
#include <GL/freeglut.h>

enum eModels { mAdvertisement, m4x1platform, mConsole, mLadder, mBox, mButton,
			   MODELS_SIZE };

class ModelLoader;
class ModelManager: public IAssetManager {
private:
	ModelLoader* Models[MODELS_SIZE]; 	
public:	
	ModelManager();
	~ModelManager();
	/**
		* @brief loads the model files
        * @param none
		* @return void
	*/
	void init();
	/**
		* @brief clears the memory and reloads the files it case they changed
        * @param none
		* @return void
	*/
	void reload();
	/**
		* @brief ensures that the memory is cleared	
        * @param none
		* @return void
	*/
	void clearMemory();
	/**
		* @brief calls the draw function of the modelloader 
		* that is stored at the position of enum in the array
		* Futhermore it calls bindtexture if the texture parameter is delivered
        * @param eModels model - represents the index of the object in the array the list holds
		* @param GLUint texture - represents the Texture ID that should be used to texture the model
		* @return void
	*/
	void drawModel(const eModels model, const GLuint texture = 0) const;
};
