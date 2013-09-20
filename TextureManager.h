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
#include "TextureLoader.h"

enum eTextures { tAdOreo, taAdOreo_Text,
				 TEXTURE_SIZE };

class TextureManager: public IAssetManager {
private:
	//change that later to a better image loader!!
	//TexturedPolygons tp;
	TextureLoader* tl;
	glTexture Textures[TEXTURE_SIZE]; 	
public:		
	TextureManager();
	~TextureManager();		
	void init();
	void reload();
	void clearMemory();
	GLuint getTextureID(const eTextures texture) const;
};
