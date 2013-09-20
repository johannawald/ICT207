#include "Stairs.h"


Stairs::Stairs(void)
{
	m_stepWidth = 0;
	m_stepHeight = 0;
	m_stepDepth = 0;
	m_numberOfSteps = 0;
}


Stairs::Stairs(float w, float h, float d, int n)
{
	m_stepWidth = w;
	m_stepHeight = h;
	m_stepDepth = d;
	m_numberOfSteps = n;
}


Stairs::~Stairs(void)
{
}


bool Stairs::SetValues(float w, float h, float d, int n)
{
	bool isValid;

	if (w > 0 && h > 0 && d > 0 && n > 0)
	{
		m_stepWidth = w;
		m_stepHeight = h;
		m_stepDepth = d;
		m_numberOfSteps = n;
		isValid = true;
	}
	else
	{
		isValid = false;
	}

	return isValid;
}


void Stairs::DrawStairs(float xpos, float ypos, float zpos,
						float xrot, float yrot, float zrot,
						float scale, GLuint htexture, GLuint dtexture)
{
	float doffset = -m_stepDepth; //used for translating individual steps on depth plane
	float hoffset = m_stepHeight; //used for translating individual steps on height plane

	glPushMatrix();
		glTranslatef(xpos, ypos, zpos);
		glRotatef(xrot, 1, 0, 0); //rotate on x axis by xrot degrees
		glRotatef(yrot, 0, 1, 0); //rotate on y axis by yrot degrees
		glRotatef(zrot, 0, 0, 1); //rotate on z axis by zrot degrees
		glScalef(scale, scale, scale);
		
		glEnable(GL_TEXTURE_2D); //enable textures
		for (int i = 0; i < m_numberOfSteps; i++) 
		{
			glPushMatrix();
				glTranslatef(0, i*hoffset, i*doffset);
				DrawStep(htexture, dtexture);	
			glPopMatrix();
		}

	glPopMatrix();

}


void Stairs::DrawStep(GLuint htex, GLuint dtex)
{
	//draw height planes
	glEnable(GL_TEXTURE_2D); //enable textures
	glBindTexture(GL_TEXTURE_2D, htex); //apply height plane texture
	glBegin(GL_QUADS);
		//draw front plane
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0, 0, 0); //bottom left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(m_stepWidth, 0, 0); //bottom right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(m_stepWidth, m_stepHeight, 0); //top right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, m_stepHeight, 0); //top left corner

		//draw back plane
		glTexCoord2f(0.0, 0.0);
		glVertex3f(m_stepWidth, 0, m_stepDepth); //bottom left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0, 0, m_stepDepth); //bottom right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(0, m_stepHeight, m_stepDepth); //top right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(m_stepWidth, m_stepHeight, m_stepDepth); //top left corner
	glEnd();
	glDisable(GL_TEXTURE_2D); //disable texturing

	//draw depth planes
	glEnable(GL_TEXTURE_2D); //enable textures
	glBindTexture(GL_TEXTURE_2D, dtex); //apply depth plane texture
	glBegin(GL_QUADS);
		//draw top plane
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0, m_stepHeight, 0); //front left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(m_stepWidth, m_stepHeight, 0); //front right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(m_stepWidth, m_stepHeight, m_stepDepth); //back right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, m_stepHeight, m_stepDepth); //back left corner

		//draw bottom plane
		glTexCoord2f(0.0, 0.0);
		glVertex3f(m_stepWidth, 0, 0); //front right corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0, 0, 0); //front left corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(0, 0, m_stepDepth); //back left corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(m_stepWidth, 0, m_stepDepth); //back right corner
	glEnd();
	glDisable(GL_TEXTURE_2D); //disable texturing

	//draw end caps
	glEnable(GL_TEXTURE_2D); //enable textures
	glBindTexture(GL_TEXTURE_2D, htex); //apply height plane texture
	glBegin(GL_QUADS);
		//draw left end cap
		glTexCoord2f(0.0, 0.0);
		glVertex3f(0, 0, m_stepDepth); //bottom left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0, 0, 0); //bottom right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(0, m_stepHeight, 0); //top right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, m_stepHeight, m_stepDepth); //top left corner

		//draw left end cap
		glTexCoord2f(0.0, 0.0);
		glVertex3f(m_stepWidth, 0, 0); //bottom left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(m_stepWidth, 0, m_stepDepth); //bottom right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(m_stepWidth, m_stepHeight, m_stepDepth); //top right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(m_stepWidth, m_stepHeight, 0); //top left corner
	glEnd();
	glDisable(GL_TEXTURE_2D); //disable texturing
}


static void Stairs::drawStairs(float stairWidth, float stairHeight, float stairDepth, float numSteps)
{
	//work out step dimensions
	float stepHeight, stepDepth;
	stepHeight = stairHeight / numSteps;
	stepDepth = stairDepth / numSteps;

	//draw vertical step faces
	for (int i = 0; i < numSteps; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.125, 0.5);		glVertex3f(0.0, stepHeight * i, stepDepth * i);
			glTexCoord2f (0.0, 0.5);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * i);
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * i);
			glTexCoord2f (0.125, 0.0);		glVertex3f(stairWidth, stepHeight * i, stepDepth * i);
		glEnd();
	}

	//draw horizontal step faces
	for (int i = 0; i < numSteps; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.125, 0.5);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * i);
			glTexCoord2f (0.0, 0.5);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.125, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * i);
		glEnd();
	}

	//draw sides of staircase
	for (int i = 0; i < numSteps; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f (0.125, 0.125);	glVertex3f(0.0, 0.0, stepDepth * i);
			glTexCoord2f (0.0, 0.125);		glVertex3f(0.0, 0.0, stepDepth * (i + 1));
			glTexCoord2f (0.0, 0.0);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.125, 0.0);		glVertex3f(0.0, stepHeight * (i + 1), stepDepth * i);

			glTexCoord2f (0.125, 0.125);	glVertex3f(stairWidth, 0.0, stepDepth * i);
			glTexCoord2f (0.0, 0.125);		glVertex3f(stairWidth, 0.0, stepDepth * (i + 1));
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * (i + 1));
			glTexCoord2f (0.125, 0.0);		glVertex3f(stairWidth, stepHeight * (i + 1), stepDepth * i);
		glEnd();
	}

	//draw rear of staircase
		glBegin(GL_QUADS);
			glTexCoord2f (0.5, 0.5);		glVertex3f(0.0, 0.0, stairDepth);
			glTexCoord2f (0.0, 0.5);		glVertex3f(stairWidth, 0.0, stairDepth);
			glTexCoord2f (0.0, 0.0);		glVertex3f(stairWidth, stairHeight, stairDepth);
			glTexCoord2f (0.5, 0.0);		glVertex3f(0.0, stairHeight, stairDepth);
		glEnd();
}