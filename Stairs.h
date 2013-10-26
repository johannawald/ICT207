/**
 * @class Stairs
 * @brief Builds a set of stairs. 
 *
 * Builds a set of stairs of any step width, step height, step depth and number of steps.
 *
 * @author Raymond Forster
 * @version 2
 * @date 18/09/2013 Raymond Forster - Started
 * @date 20/09/2013 Jon Mace - Added function to draw a set of stairs with derived step 
 *							   height and step width
 * @date 26/10/2013 Johanna Wald - changed function to not static + const
 */

//--------------------------------------------------------------------------------------

#ifndef STAIRS_H
#define STAIRS_H

//--------------------------------------------------------------------------------------

#include <windows.h>
#include <GL\gl.h>

class Stairs
{
	private:
		float m_stepWidth; /**< Stores the width of each step*/
		float m_stepHeight; /**< Stores the height of each step*/
		float m_stepDepth; /**< Stores the depth of each step*/
		int m_numberOfSteps; /**< Stores the number of steps*/

			/**
             * @brief Draws a step.
			 *
             * @param GLuint htex - the texture to be applied to the vertical faces
			 * @param GLuint dtex - the texutre to be applied to the horizontal faces
             */
		void DrawStep(GLuint htex, GLuint dtex);

	public:
			/**
             * @brief Default constructor creates a new Stairs object.
             *
             * @param none
             */
		Stairs(void);

			/**
             * @brief Constructor creates a new Stairs object with given values.
             *
             * @param float w - the width of each step.
			 * @param float h - the height of each step.
			 * @param float d - the depth of each step.
			 * @param int n - the number of steps.
             */
		Stairs(float w, float h, float d, int n);

			/**
             * @brief Destructor destroys Stairs object when it goes out of scope.
             * @param none
             */
		~Stairs(void);

			/**
             * @brief Sets the values for step width, step height, step depth and number of steps.
             * 
			 * @param float w - the width of each step.
			 * @param float h - the height of each step.
			 * @param float d - the depth of each step.
			 * @param int n - the number of steps.
             */
		bool SetValues(float w, float h, float d, int n);

			/**
             * @brief Draw a set of stairs at the target location.
			 *
			 * Draw a set of stairs at the target location xpos, ypos, xpos. Apply desired rotation
			 * to x axis by xrot, y axis by yrot and z axis by zrot. Scale the dimensions to desired
			 * value using scale. Apply separate texture to vertical planes with htexture, and horizontal
			 * planes with dtexture.
			 *
             * @param float xpos - x world coordinate to place object
			 * @param float ypos - y world coordinate to place object
			 * @param float zpos - z world coordinate to place object
			 * @param float xrot - rotation in degrees to rotate on the x axis
			 * @param float yrot - rotation in degrees to rotate on the y axis
			 * @param float zrot - rotation in degrees to rotate on the z axis
			 * @param float scale - factor to scale object by
			 * @param GLuint htexture - texture for vertical faces
			 * @param GLuint dtexture - texture for horizontal faces
             */
		void DrawStairs(float xpos, float ypos, float zpos,
						float xrot, float yrot, float zrot,
						float scale, GLuint htexture, GLuint dtexture);

			/**
             * @brief Draw a set of stairs filling a specified volume.
			 *
			 * Draw a set of stairs filling a specified volume consisting of a specified number of steps. 
			 * The width of each step is provided. The height of each step is derived from the total height 
			 * of the area divided by the number of steps to be drawn. The depth of each step is derived from 
			 * the total depth of the area divided by  the number of steps to be drawn.
			 *
             * @param float stairWidth - the total width of the area
			 * @param float stairHeight - the total height of the area
			 * @param float stairDepth - the total depth of the area
			 * @param float numSteps - the number of steps to be drawn
			 */
		void DrawStairs(const float stairWidth, const float stairHeight, 
							  const float stairDepth, const float numSteps) const;
};

#endif //end of Stairs class