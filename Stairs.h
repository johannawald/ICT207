//--------------------------------------------------------------------------------------

#ifndef STAIRS_H
#define STAIRS_H

//--------------------------------------------------------------------------------------

#include <windows.h>
#include <GL\gl.h>

class Stairs
{
	private:
		float m_stepWidth;
		float m_stepHeight;
		float m_stepDepth;
		int m_numberOfSteps;

		void DrawStep(GLuint htex, GLuint dtex);

	public:
		Stairs(void);
		Stairs(float w, float h, float d, int n);
		~Stairs(void);

		bool SetStairDimensions(float w, float h, float d, int n);

		void DrawStairs(float xpos, float ypos, float zpos,
						float xrot, float yrot, float zrot,
						float scale, GLuint htexture, GLuint dtexture);
};

#endif //end of Stairs class