/**
 * @class TextureManager
 * @brief Controller class for the texture assets
 *
 * Implements the basic functions to work with texture files: init(), reload(), clearMemory(), getTextureID and a List to manage them
 *
 * @author Johanna Wald
 * @version 01
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

#include "IAssetManager.h"
#include <GL/freeglut.h>
//#include "TextureLoader.h"
#include "include\SOIL.h"

//ray, should we do that with a map?

enum eTextures { tAdOreo, 
				 taSomeTexture,
				 taAdOreo_Text, 
				 taSome,
				 taGrass, taGrass2, tatext,
				 taWelcome,
				 TEXTURE_SIZE };

class TextureManager: public IAssetManager {
private:
	//change that later to a better image loader
	//TextureLoader* tl;
	GLuint Textures[TEXTURE_SIZE]; 	
public:	
	TextureManager();
	~TextureManager();	
	/**
		* @brief loads the texture files
        * @param none
		* @return void
	*/
	void init();
	/**
		* @brief reload the texture files
        * @param none
		* @return void
	*/
	void reload();
	/**
		* @brief clear the memory / free the loaded textures
        * @param none
		* @return void
	*/
	void clearMemory();
	/**
		* @brief Returns the Texture ID of the textures stored at position "texture" in the list the class holds 
        * @param eTextures texture - represents the position / index of the requested texture in the array
		* @return GLuint - the Texture ID, you can pass to the BindTexture()-function
	*/
	GLuint getTextureID(const eTextures texture) const;
	/**
		*** comment missing
	*/	
	GLuint Loadimage(const char* filename);
};
