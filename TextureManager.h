/**
 * @class TextureManager
 * @brief Controller class for the texture assets
 *
 * Implements the basic functions to work with texture files: init(), reload(), clearMemory(), getTextureID and a List to manage them
 *
 * @author Johanna Wald
 * @version 03
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 * @date 01/10/2013 Daniel Manganaro / Raymond Forster - Added textures used in the hallway
 */

#pragma once

#include "IAssetManager.h"
#include <GL/freeglut.h>
#include "include\SOIL.h"

enum eTextures { tAdOreo, 
				 taSomeTexture,
				 taAdOreo_Text, 
				 taGrass, taGrass2, tatext,
				 taWelcome, taWoodenDoor, taFarExit, 
				 taHallway1, taHallway2, taHallway3,
				 taHallway4, taHallway5, taHallway6,
				 taHallway7, taHallway8, taHallway9, 
				 taHallway10, taHallway11, taHallway12,
				 taHallway13, taHallway14, taBoard1,
				 taBoard2, taBoard3, taBoard4,
				 //LevelOneController:
				 taBox, taButton, taBomb, ta4x1platform, taConsole, 
				 taTilefloor, taTilewall, taConcWall, taRustyWall,
				 //Game over screens
				 taGameOver, taGameWin,						
				 taRoberWelcome1, taRoberWelcome2, taRoberConsoleSreen,
				 taRobot,
				 TEXTURE_SIZE };

class TextureManager: public IAssetManager {
private:
	GLuint mTextures[TEXTURE_SIZE]; 	
	GLuint Loadimage(const char* filename);
public:	
	TextureManager();
	~TextureManager();	
	/**
		* @brief loads the texture files
        * @param none
		* @return void
	*/
	void init();
	/**
		* @brief reload the texture files
        * @param none
		* @return void
	*/
	void reload();
	/**
		* @brief clear the memory / free the loaded textures
        * @param none
		* @return void
	*/
	void clearMemory();
	/**
		* @brief Returns the Texture ID of the textures stored at position "texture" in the list the class holds 
        * @param eTextures texture - represents the position / index of the requested texture in the array
		* @return GLuint - the Texture ID, you can pass to the BindTexture()-function
	*/
	GLuint getTextureID(const eTextures texture) const;
};
