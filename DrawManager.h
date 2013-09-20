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
#include <GL/GL.h>

class DrawManager {
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
	void RenderString(float x, float y, void *font, const char* str, unsigned r = 0, unsigned g = 0, unsigned b = 0);
	void drawStairs(float stairWidth, float stairHeight, float stairDepth, float numSteps);
};
