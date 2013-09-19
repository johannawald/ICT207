#include "TextureManager.h"

TextureManager::TextureManager()
{
	init();
}

TextureManager::~TextureManager()
{
	//clear(); abstract?
	/*for (int i = 0; i<2 ;i++)
		es->Unload(Sounds[i]);
	*/
}

void TextureManager::init()
{
	Textures[0] = tp.LoadTexture("data/abovechanctext.raw", 128, 1024);
	tp.CreateTexture(ABOVE_CHANC_TEXT, (unsigned char*) Textures[0], 128, 1024);

}

void TextureManager::reaload()
{
	//do we really need that function?
}

GLuint TextureManager::getTexture(eTextures texture)
{
	return 0; //Textures[texture];
}
