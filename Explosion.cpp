// explosion.cpp
//
// implementation file for explosion class
// defines all the methods declared
//
// Daniel Manganaro, October 2013
//--------------------------------------------------------------------

#include "Explosion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL\glut.h>
#include <iostream>

Explosion::Explosion(): mNumParticles(10000), mNumDebris(100) {
	mFuel = 0;
	mSpeed = 0.5;
}

Explosion::Explosion(float s): mNumParticles(10000), mNumDebris(100) {
	mFuel = 0;
	mSpeed = s;
}

void Explosion::setSize(const int p, const int d){
	//mParticles = new Particle[p];
	//mDebris = new DebrisData[d];
}

void Explosion::newSpeed(float dest[3]){
	float x, y, z, len;

	x = (2.0 * ((GLfloat) rand()) / ((GLfloat) RAND_MAX)) - 1.0;
	y = (2.0 * ((GLfloat) rand()) / ((GLfloat) RAND_MAX)) - 1.0;
	z = (2.0 * ((GLfloat) rand()) / ((GLfloat) RAND_MAX)) - 1.0;

	len = sqrt (x * x + y * y + z * z);

	if(len){
		x = x / len;
		y = y / len;
		z = z / len;
	}

	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}

void Explosion::newExplosion(float x, float y, float z) {
	srand (time (NULL));
	for(int i = 0; i < mNumParticles; i++)
	{
		mParticles[i].mPosition[0] = x;
		mParticles[i].mPosition[1] = y;
		mParticles[i].mPosition[2] = z;

		mParticles[i].mColour[0] = 1.0;
		mParticles[i].mColour[1] = 1.0;
		mParticles[i].mColour[2] = 0.5;
		
		newSpeed(mParticles[i].mSpeed);
	}

	for (int i = 0; i < mNumDebris; i++)
    {
      mDebris[i].mPosition[0] = x;
      mDebris[i].mPosition[1] = y;
      mDebris[i].mPosition[2] = z;

      mDebris[i].mOrientation[0] = 0.0;
      mDebris[i].mOrientation[1] = 0.0;
      mDebris[i].mOrientation[2] = 0.0;

      mDebris[i].mColor[0] = 0.7;
      mDebris[i].mColor[1] = 0.7;
      mDebris[i].mColor[2] = 0.0;

      mDebris[i].mScale[0] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      mDebris[i].mScale[1] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      mDebris[i].mScale[2] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

	  newSpeed (mDebris[i].mSpeed);
      newSpeed (mDebris[i].mOrientationSpeed);
    }

	mFuel = 900;
}

void Explosion::Draw()
{
	

	int i;
  
	glPushAttrib(GL_CURRENT_BIT);
		glLoadIdentity ();
 
		/* Place the camera */
	
		glTranslatef (0.0, 0.0, -30.0);
		// glRotatef (angle, 0.0, 1.0, 0.0);

		glPushMatrix ();

			glDisable (GL_LIGHTING);
			glDisable (GL_DEPTH_TEST);
			glBindTexture(GL_TEXTURE_2D, -1);
			
			
			glBegin (GL_POINTS);
				  for (i = 0; i < mNumParticles; i++)
				  {
					  glColor3fv (mParticles[i].mColour);
					  glVertex3fv (mParticles[i].mPosition);
				  }
			glEnd ();


		glPopMatrix ();

		for (i = 0; i < mNumDebris; i++)
		{
			//glColor3f(1,1,1);
			//glColor3fv (mDebris[i].mColor);
			//glColor3f (1,0,0);

			glPushMatrix ();
			
				glTranslatef (mDebris[i].mPosition[0],
					mDebris[i].mPosition[1],
					mDebris[i].mPosition[2]);

				glRotatef (mDebris[i].mOrientation[0], 1.0, 0.0, 0.0);
				glRotatef (mDebris[i].mOrientation[1], 0.0, 1.0, 0.0);
				glRotatef (mDebris[i].mOrientation[2], 0.0, 0.0, 1.0);

				glScalef (mDebris[i].mScale[0],
					mDebris[i].mScale[1],
					mDebris[i].mScale[2]);

				glBegin (GL_TRIANGLES);
					glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 0.5, 0.0);
					glTexCoord2f(1.0, 0.0); glVertex3f (-0.25, 0.0, 0.0);
					glTexCoord2f(0.0, 0.0); glVertex3f (0.25, 0.0, 0.0);
				glEnd ();	  
	  
				//glDisable (GL_LIGHTING); 
				//glDisable (GL_LIGHT0); 

			glPopMatrix ();
		} 
	 glPopAttrib();
}

void Explosion::Update(void){
	int i;
	if(mFuel > 0){
		for(i = 0; i < mNumParticles; i++){
			mParticles[i].mPosition[0] += mParticles[i].mSpeed[0] * mSpeed;
			mParticles[i].mPosition[1] += mParticles[i].mSpeed[1] * mSpeed;
			mParticles[i].mPosition[2] += mParticles[i].mSpeed[2] * mSpeed;

			mParticles[i].mColour[0] -= 1.0 / 5000.0;
			if(mParticles[i].mColour[0] < 0.0)
				mParticles[i].mColour[0] = 0.0;

			mParticles[i].mColour[1] -= 1.0 / 1000.0;
			if(mParticles[i].mColour[1] < 0.0)
				mParticles[i].mColour[1] = 0.0;

			mParticles[i].mColour[2] -= 1.0 / 500.0;
			if(mParticles[i].mColour[2] < 0.0)
				mParticles[i].mColour[2] = 0.0;
		}

		for (i = 0; i < mNumDebris; i++)
	    {
	      mDebris[i].mPosition[0] += mDebris[i].mSpeed[0] * mSpeed;
	      mDebris[i].mPosition[1] += mDebris[i].mSpeed[1] * mSpeed;
	      mDebris[i].mPosition[2] += mDebris[i].mSpeed[2] * mSpeed;
	      
	      mDebris[i].mOrientation[0] += mDebris[i].mOrientationSpeed[0] * 10;
	      mDebris[i].mOrientation[1] += mDebris[i].mOrientationSpeed[1] * 10;
	      mDebris[i].mOrientation[2] += mDebris[i].mOrientationSpeed[2] * 10;
	    }

		--mFuel;
	}

	glutPostRedisplay();
}

