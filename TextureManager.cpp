#include "TextureManager.h"
#include <iostream>

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
	mTextures[tAdOreo] = Loadimage("textures/welcome.raw");
	mTextures[taAdOreo_Text] = Loadimage("textures/welcome.raw");
	mTextures[taGrass] = Loadimage("textures/CocaCola.bmp");
	mTextures[taGrass2] = Loadimage("textures/CocaCola.bmp");
	mTextures[taSomeTexture] = Loadimage("textures/CocaCola.bmp");
	mTextures[tatext] = Loadimage("textures/CocaCola.bmp");
	mTextures[taWelcome] = Loadimage("textures/CocaCola.bmp");
	mTextures[taWoodenDoor] = Loadimage("textures/woodendoor.bmp");
	mTextures[taFarExit] = Loadimage("textures/FarExit.bmp");
	mTextures[taHallway1] = Loadimage("textures/hallway1.bmp");
	mTextures[taHallway2] = Loadimage("textures/hallway2.bmp");
	mTextures[taHallway3] = Loadimage("textures/hallway3.bmp");
	mTextures[taHallway4] = Loadimage("textures/hallway4.bmp");
	mTextures[taHallway5] = Loadimage("textures/hallway5.bmp");
	mTextures[taHallway6] = Loadimage("textures/hallway6.bmp");
	mTextures[taHallway7] = Loadimage("textures/hallway7.bmp");
	mTextures[taHallway8] = Loadimage("textures/hallway8.bmp");
	mTextures[taHallway9] = Loadimage("textures/hallway9.bmp");
	mTextures[taHallway10] = Loadimage("textures/hallway10.bmp");
	mTextures[taHallway11] = Loadimage("textures/hallway11.bmp");
	mTextures[taHallway12] = Loadimage("textures/hallway12.bmp");
	mTextures[taHallway13] = Loadimage("textures/hallway13.bmp");
	mTextures[taHallway14] = Loadimage("textures/hallway14.bmp");
	mTextures[taBoard1] = Loadimage("textures/board1.bmp");
	mTextures[taBoard2] = Loadimage("textures/board2.bmp");
	mTextures[taBoard3] = Loadimage("textures/board3.bmp");
	mTextures[taBoard4] = Loadimage("textures/board4.bmp");
	//LevelOneController:
	mTextures[taBox] = Loadimage("textures/box.bmp");
	mTextures[taButton] = Loadimage("textures/button.bmp");
	mTextures[taBomb] = Loadimage("textures/bomb.bmp");
	mTextures[ta4x1platform] = Loadimage("textures/4x1platform.png");
	mTextures[taTilefloor] = Loadimage("textures/tilefloor.bmp");
	mTextures[taTilewall] = Loadimage("textures/tilewall.bmp");
	mTextures[taConcWall] = Loadimage("textures/concwall.bmp");
	mTextures[taRustyWall] = Loadimage("textures/rustywall.png");
	mTextures[taConsole] = Loadimage("textures/console.bmp");
	//gameover
	mTextures[taGameOver] = Loadimage("textures/gameover.png"); //updated 29.10 *JM
	mTextures[taGameWin] = Loadimage("textures/gamewin.png");
	mTextures[taRoberWelcome1] = Loadimage("textures/ROBERWelcome01.png");
	mTextures[taRoberWelcome2] = Loadimage("textures/ROBERWelcome02.png");
	mTextures[taRoberConsoleSreen] = Loadimage("textures/ROBERControlScreen.png");
	std::cout << "Textures Loaded." << std::endl;
}

void TextureManager::reload()
{
	clearMemory();
	init();
}

GLuint TextureManager::getTextureID(const eTextures texture) const
{
	return mTextures[texture];
}

void TextureManager::clearMemory() 
{
	//ray, can you free the images?
	//SOIL_free_image_data
	/*delete tl;
	for (int i = 0; i<TEXTURE_SIZE ;i++)
		tl->FreeTexture(&Textures[i]);*/
}