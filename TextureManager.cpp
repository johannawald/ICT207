#include "TextureManager.h"
#include <iostream>

//work in progress!

TextureManager::TextureManager()
{
	init();
}

TextureManager::~TextureManager()
{
	//clear(); abstract?
	for (int i = 0; i<TEXTURE_SIZE ;i++)
		tl->FreeTexture(&Textures[i]);
}

void TextureManager::init()
{
	tl = new TextureLoader();
	//for (int i = 0; i < TEXTURE_SIZE; i++) 
	//	Textures[i] = new TextureLoader();

	tl->LoadTextureFromDisk("data\\Oreo.tga", &Textures[0]);
	//tl->SetAlphaMatch(TRUE, 0, 0xFF, 0xFF);
	tl->LoadTextureFromDisk("data\\Oreo - Kopie.png", &Textures[1]);
	
	int i;
	std::cout << "";
}

void TextureManager::reload()
{
	//do we really need that function?
}

GLuint TextureManager::getTextureID(eTextures texture)
{
	return Textures[texture].TextureID;
}
