/**
 * @class DrawManager
 * @brief Helping class that provides general draw-functions
 *
 * It's a helping class stored in the controller (composition) as RenderString and drawStairs
 *
 * @author Johanna Wald
 * @version 06
 * @date 20/09/2013 Johanna Wald - start programming
 * @date 12/10/2013 Johanna Wald - changed the stair-class call
 * @date 21/10/2013 Johanna Wald - added functions to draw collision objects
 * @date 22/10/2013 Johanna Wald - added a vector class and used it everywhere
 * @date 24/10/2013 Johanna Wald - changed name of stair member class object
 * @date 25/10/2013 Johanna Wald - cleaned code, changed variable names (to naming convention)
 */

#pragma once

#include <string>
#include <Windows.h>
#include <GL/GL.h>
#include "Stairs.h"
#include "BoundingBox.h"

class CollisionDetection;
class DrawManager {
private:
	Stairs mStairs;
public:
	/**
        * @brief function that draws a string
		*
		* It draws a colored, positioned string on the chosen position
		*
        * @param const float x - x-position the text should be drawn at
		* @param const float y - y-position the text should be drawn at
		* @param void *font - the font should be used to draw the text
		* @param const const char* str - the string should be written
		* @param const unsigned r - default parameter, the red part of the rgb-color the text should have
		* @param const unsigned g - default parameter, the green part of the rgb-color the text should have
		* @param const unsigned b - default parameter, the blue part of the rgb-color the text should have
		* @return void
    */
	void RenderString(const float x, const float y, void *font, const char* str, const unsigned r = 0, const unsigned g = 0, const unsigned b = 0) const;
	/**
        * @brief function that draws staris with the stair class (member variable mStairs)
		*
		* @param const float stairWidth - width of the Stairs
		* @param const float stairHeight - height of the Stairs
		* @param const float stairDepth - depth of the Stairs
		* @param const float numSteps - number of steps
		* @return void
    */
	void DrawStairs(const float stairWidth, const float stairHeight, const float stairDepth, const float numSteps) const;
	/**
        * @brief draws a rect at position(x,y,z) with pWidth, pHeight, pDepth and a Texture 
		*
		* @param const GLint pTexture - the texture that should be binded for drawing the rect
		* @param const float TexCoordX - the texture x-coordinate for the texture
		* @param const float TexCoordY - the texture y-coordinate for the texture 
		* @param const int pPosition - the position of the rect 
		* @param const Vector3D& pSize - the size of the rect
		* @return void
    */	
	void DrawRect(const GLint pTexture, 
				  const float TexCoordX, const float TexCoordY, 
				  const Vector3D& pPosition,
				  const Vector3D& pSize) const;
	/**
        * @brief draws a rect with calling it's overloaded function (rect()) 
		* at position(x,y,z) with pWidth, pHeight, pDepth and a Texture and rotation(x,y,z)
		* it is used to draw a cube
		*
		* @param const GLint pTexture - the texture that should be binded for drawing the rect
		* @param const float TexCoordX - the texture x-coordinate for the texture
		* @param const float TexCoordY - the texture y-coordinate for the texture 
		* @param const int pPosition - the position of the Rect 
		* @param const int pWidth - the width of the Rect 
		* @param const int pDepth - the depth of the Rect 
		* @param const int pHeight - the height of the Rect 
		* @param const int pAngle - the rotation of the Rect
		* @return void
    */	
	void DrawRect(const GLint pTexture, 
				  const float TexCoordX, const float TexCoordY, 
				  const Vector3D& pPosition,  
				  const GLdouble pWidth, const GLdouble pHeight, const Vector3D& pAngle) const;
	/**
        * @brief draws a cube at position(x,y,z) with pWidth, pHeight, pDepth and a Texture
		*
		* @param const GLint pTexture - the texture that should be binded for drawing the cube
		* @param const float TexCoordX - the texture x-coordinate for the texture
		* @param const float TexCoordY - the texture y-coordinate for the texture 
		* @param const Vector3D& pPosition - the position of the cube 
		* @param const int pWidth - the width of the cube 
		* @param const int pDepth - the depth of the cube 
		* @param const int pHeight - the height of the cube 
		* @return void
    */	
	void DrawCube(const GLint pTexture, 
				  const float pTexCoordX, const float pTexCoordY, 
				  const Vector3D& pPosition,  
				  const GLdouble pWidth, const GLdouble pHeight, const GLdouble pDepth) const;
	/**
        * @brief draws a rect at position(x,y,z) with pWidth, pHeight, pDepth and a Texture with a collision box
		*
		* @param CollisionDetection* collision - the collisionDetection-element what should be used to add the collision box to
		* @param const GLint pTexture - the texture that should be binded for drawing the rect
		* @param const float TexCoordX - the texture x-coordinate for the texture
		* @param const float TexCoordY - the texture y-coordinate for the texture 
		* @param const Vector3D& pPosition - the position of the rect and the collision box
		* @param const int pSize - the size of the rect and the collision box (pWidth, pHeight, pDepth)
		* @return void
    */	
	void DrawCollisionRect(CollisionDetection* collision, const GLint pTexture, 
				const float pTexCoordX, const float pTexCoordY, 
				const Vector3D& pPosition,  
				const Vector3D& pSize) const;
	/**
        * @brief draws a cube at position(x,y,z) with pWidth, pHeight, pDepth and a Texture with a collision box
		*
		* @param CollisionDetection* collision - the collisionDetection-element what should be used to add the collision box to
		* @param const GLint pTexture - the texture that should be binded for drawing the rect
		* @param const float TexCoordX - the texture x-coordinate for the texture
		* @param const float TexCoordY - the texture y-coordinate for the texture 
		* @param const Vector3D& pPosition - the position of the rect and the collision box
		* @param const int pSize - the size of the rect and the collision box (pWidth, pHeight, pDepth)
		* @return void
    */	
	void DrawCollisionCube(CollisionDetection* collision, const GLint pTexture, 
				const float pTexCoordX, const float pTexCoordY, 
				const Vector3D& pPosition,
				const Vector3D& pSize) const;
	/**
        * @brief draws the (parameter) collision box with lines
		*
		* @param const BoundingBox* pBoundingBox - the bounding box that should be drawn
		* @return void
    */	
	void DrawCollisionBox(const BoundingBox& pBoundingBox) const;
	/**
        * @brief draws the (parameter) collision box with filled rects
		*
		* @param const BoundingBox* pBoundingBox - the bounding box that should be drawn
		* @return void
    */	
	void DrawCollisionBoxColored(const BoundingBox& pBoundingBox) const;
	//ray, please comment:
	void RenderBitmapString(const float x, const float y, const float z, void *pFont, const char *pString) const;
	void RenderStrokeFontString(const float x, const float y, const float z, void *pFont, const char *pString) const;
	void SetOrthographicProjection() const;
	void RestorePerspectiveProjection() const;

};
