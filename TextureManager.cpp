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

void TextureManager::init()
{
	tl = new TextureLoader();
	//tl->LoadTextureFromDisk("data\\Oreo.tga", &Textures[0]);
}

void TextureManager::reload()
{
	clearMemory();
	init();
}

GLuint TextureManager::getTextureID(const eTextures texture) const
{
	return Textures[texture].TextureID;
}

void TextureManager::clearMemory() 
{
	delete tl;
	for (int i = 0; i<TEXTURE_SIZE ;i++)
		tl->FreeTexture(&Textures[i]);
}