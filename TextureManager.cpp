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
	Textures[taWoodenDoor] = Loadimage("textures/woodendoor.bmp");
	Textures[taFarExit] = Loadimage("textures/FarExit.bmp");
	Textures[taHallway1] = Loadimage("textures/hallway1.bmp");
	Textures[taHallway2] = Loadimage("textures/hallway2.bmp");
	Textures[taHallway3] = Loadimage("textures/hallway3.bmp");
	Textures[taHallway4] = Loadimage("textures/hallway4.bmp");
	Textures[taHallway5] = Loadimage("textures/hallway5.bmp");
	Textures[taHallway6] = Loadimage("textures/hallway6.bmp");
	Textures[taHallway7] = Loadimage("textures/hallway7.bmp");
	Textures[taHallway8] = Loadimage("textures/hallway8.bmp");
	Textures[taHallway9] = Loadimage("textures/hallway9.bmp");
	Textures[taHallway10] = Loadimage("textures/hallway10.bmp");
	Textures[taHallway11] = Loadimage("textures/hallway11.bmp");
	Textures[taHallway12] = Loadimage("textures/hallway12.bmp");
	Textures[taHallway13] = Loadimage("textures/hallway13.bmp");
	Textures[taHallway14] = Loadimage("textures/hallway14.bmp");
	Textures[taBoard1] = Loadimage("textures/board1.bmp");
	Textures[taBoard2] = Loadimage("textures/board2.bmp");
	Textures[taBoard3] = Loadimage("textures/board3.bmp");
	Textures[taBoard4] = Loadimage("textures/board4.bmp");
	//LevelOneController:
	Textures[taBox] = Loadimage("textures/box.bmp");
	Textures[taButton] = Loadimage("textures/button.bmp");
	Textures[taBomb] = Loadimage("textures/bomb.bmp");
	Textures[ta4x1platform] = Loadimage("textures/4x1platform.png");
	Textures[taConsole] = Loadimage("textures/console.png");
	Textures[taTilefloor] = Loadimage("textures/tilefloor.bmp");
	Textures[taTilewall] = Loadimage("textures/tilewall.bmp");
	Textures[taConcWall] = Loadimage("textures/concwall.bmp");
	Textures[taRustyWall] = Loadimage("textures/rustywall.png");
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