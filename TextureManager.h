//  @ Unit : ICT207
//  @ File Name : TextureManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssertManager.h"
#include <GL/freeglut.h>
#include "TexturedPolygons.h"

enum eTextures { tCocaCola,
				 TEXTURE_SIZE };

class TextureManager: public IAssertManager {
private:
	//change that later to a better image loader!!
	TexturedPolygons tp;
	GLubyte* Textures[TEXTURE_SIZE]; 	
public:		
	TextureManager();
	~TextureManager();		
	void init();
	void reaload();
	GLuint getTexture(eTextures texture);
};
