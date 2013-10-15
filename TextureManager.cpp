#include "TextureManager.h"
#include <iostream>

//work in progress

TextureManager::TextureManager()
{
	init();
}

TextureManager::~TextureManager()
{
	clearMemory();
}

//GLuint LoadImage(string filename) SOIL_load_OGL_texture ray, please do that
//, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

void TextureManager::init()
{
	//tl = new TextureLoader();
	/*tl->LoadTextureFromDisk("textures\\CocaCola.bmp", &Textures[0]);
	tl->LoadTextureFromDisk("textures\\CocaCola.bmp", &Textures[1]);
	tl->LoadTextureFromDisk("textures\\CocaCola.bmp", &Textures[2]);
	tl->LoadTextureFromDisk("textures\\CocaCola.bmp", &Textures[3]);
	tl->LoadTextureFromDisk("textures\\welcome.raw", &Textures[4]);
	unsigned char* image;
	image = tl->LoadTexture("textures/numberpad.raw", 800, 500);*/

	Textures[tAdOreo] = SOIL_load_OGL_texture("textures/welcome.raw", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);

	Textures[taAdOreo_Text] = SOIL_load_OGL_texture("textures/welcome.raw", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);
	
	Textures[taGrass] = SOIL_load_OGL_texture("textures/CocaCola.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);
	Textures[taGrass2] = SOIL_load_OGL_texture("textures/CocaCola.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);

	Textures[taSomeTexture] = SOIL_load_OGL_texture("textures/CocaCola.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);

	Textures[tatext] = SOIL_load_OGL_texture("textures/CocaCola.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);
	Textures[taWelcome] = SOIL_load_OGL_texture("textures/CocaCola.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);
}

void TextureManager::reload()
{
	clearMemory();
	init();
}

GLuint TextureManager::getTextureID(const eTextures texture) const
{
	return Textures[texture];
}

void TextureManager::clearMemory() 
{
	//ray, can you free the images?
	//SOIL_free_image_data
	/*delete tl;
	for (int i = 0; i<TEXTURE_SIZE ;i++)
		tl->FreeTexture(&Textures[i]);*/

}