//  @ Unit : ICT207
//  @ File Name : TextureManager.h
//  @ Author : Johanna Wald
//
//

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
