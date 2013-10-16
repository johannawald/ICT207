#include "TextureManager.h"

TextureManager::TextureManager()
{
	init();
}

TextureManager::~TextureManager()
{
	clearMemory();
}

GLuint TextureManager::Loadimage(const char* filename)
{
	return SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
				  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
				  SOIL_FLAG_COMPRESS_TO_DXT);
}

void TextureManager::init()
{
	Textures[tAdOreo] = Loadimage("textures/welcome.raw");
	Textures[taAdOreo_Text] = Loadimage("textures/welcome.raw");
	Textures[taGrass] = Loadimage("textures/CocaCola.bmp");
	Textures[taGrass2] = Loadimage("textures/CocaCola.bmp");
	Textures[taSomeTexture] = Loadimage("textures/CocaCola.bmp");
	Textures[tatext] = Loadimage("textures/CocaCola.bmp");
	Textures[taWelcome] = Loadimage("textures/CocaCola.bmp");
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