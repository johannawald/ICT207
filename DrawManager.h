/**
 * @class DrawManager
 * @brief Helping class that provides general draw-functions
 *
 * It's a helping class stored in the controller (composition) as RenderString and drawStairs
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/09/2013 Johanna Wald - start programming
 */

#pragma once

#include <string>
#include <Windows.h>
#include <GL/GL.h>

class BoundingBox;
class CollisionDetection;
class DrawManager {
//private: Stairs class change the drawStairs function, call the method of the class
//please don't use a static function!!
//maybe set function for the staris (ray, please make another constructor with parameters for the whole stair length, etc.)
//ray, change the drawing in the LevelOneController, please (because the DrawManager is created over and over again)

public:
	DrawManager();	
	~DrawManager();
	/**
        * @brief function that draws a string
		*
		* It draws a colored, positioned string on the chosen position
		*
        * @param float x - x-position the text should be drawn at
		* @param float y - y-position the text should be drawn at
		* @param void *font - the font should be used to draw the text
		* @param const char* str - the string should be written
		* @param unsigned r - default parameter, the red part of the rgb-color the text should have
		* @param unsigned g - default parameter, the green part of the rgb-color the text should have
		* @param unsigned b - default parameter, the blue part of the rgb-color the text should have
		* @return void
    */
	void RenderString(const float x, const float y, void *font, const char* str, const unsigned r = 0, const unsigned g = 0, const unsigned b = 0) const;
	void DrawStairs(const float stairWidth, const float stairHeight, const float stairDepth, const float numSteps) const;
	
	void DrawRect(const GLint pTexture, 
				  const int TexCoordX, const int TexCoordY, 
				  const int pPositionX, const int pPositionY, const int pPositionZ, 
				  const GLdouble pWidth, const GLdouble pHeight) const;
	void DrawRect(const GLint pTexture, 
				  const int TexCoordX, const int TexCoordY, 
				  const int pPositionX, const int pPositionY, const int pPositionZ, 
				  const GLdouble pWidth, const GLdouble pHeight, const float angleX, const float angleY, const float angleZ) const;
	void DrawCube(const GLint pTexture, 
				  const int pTexCoordX, const int pTexCoordY, 
				  const int pPositionX, const int pPositionY, const int pPositionZ, 
				  const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth) const;
	void DrawCollisionRect(CollisionDetection* collision, const GLint pTexture, 
				const int pTexCoordX, const int pTexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight);
	void DrawCollisionCube(CollisionDetection* collision, const GLint pTexture, 
				const int pTexCoordX, const int pTexCoordY, 
				const int pPositionX, const int pPositionY, const int pPositionZ, 
				const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth);
	void DrawCollisionBox(BoundingBox *b);

};
