//  @ Unit : ICT207
//  @ File Name : TextureManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssetManager.h"
#include <GL/freeglut.h>
#include "TexturedPolygons.h"

enum eTextures { tCocaCola,
				 TEXTURE_SIZE };

class TextureManager: public IAssetManager {
private:
	//change that later to a better image loader!!
	TexturedPolygons tp;
	GLubyte* Textures[TEXTURE_SIZE]; 	
public:		
	TextureManager();
	~TextureManager();		
	void init();
	void reload();
	GLuint getTexture(eTextures texture);
};
