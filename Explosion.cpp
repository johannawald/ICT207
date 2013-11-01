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
//#include <glut.h>

Explosion::Explosion(): mNumParticles(1000), mNumDebris(100) {
	mParticles = new particle[mNumParticles];
	mDebris = new debrisData[mNumDebris];
	mFuel = 0;
	mSpeed = 0.2;
}

Explosion::Explosion(float s): mNumParticles(1000), mNumDebris(100) {
	mParticles = new particle[mNumParticles];
	mDebris = new debrisData[mNumDebris];
	mFuel = 0;
	mSpeed = s;
}

void Explosion::newSpeed(float dest[3]){
	float x, y, z, len;
	srand (time(NULL));

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
	for(int i = 0; i < mNumParticles; i++)
	{
		mParticles[i].position[0] = x;
		mParticles[i].position[1] = y;
		mParticles[i].position[2] = z;

		mParticles[i].colour[0] = 1.0;
		mParticles[i].colour[1] = 1.0;
		mParticles[i].colour[2] = 0.5;
		
		newSpeed(mParticles[i].speed);
	}

	for (int i = 0; i < mNumDebris; i++)
    {
      mDebris[i].position[0] = x;
      mDebris[i].position[1] = y;
      mDebris[i].position[2] = z;

      mDebris[i].orientation[0] = 0.0;
      mDebris[i].orientation[1] = 0.0;
      mDebris[i].orientation[2] = 0.0;

      mDebris[i].color[0] = 0.7;
      mDebris[i].color[1] = 0.7;
      mDebris[i].color[2] = 0.7;

      mDebris[i].scale[0] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      mDebris[i].scale[1] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      mDebris[i].scale[2] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

      newSpeed (mDebris[i].speed);
      newSpeed (mDebris[i].orientationSpeed);
    }

	mFuel = 100;
}

void Explosion::draw(void){

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glLoadIdentity();

	glPushMatrix();

	glBegin(GL_POINTS);
	for(int i = 0; i < mNumParticles; i++)
	{
		glColor3fv(mParticles[i].colour);
		glVertex3fv(mParticles[i].position);
	}
	glEnd();

	glPopMatrix();

	//glNormal3f(0.0, 0.0, 1.0);

	for (int i = 0; i < mNumDebris; i++)
	{
	  glColor3fv (mDebris[i].color);

	  glPushMatrix ();
      
	  glTranslatef (mDebris[i].position[0],
			mDebris[i].position[1],
			mDebris[i].position[2]);

	  glRotatef (mDebris[i].orientation[0], 1.0, 0.0, 0.0);
	  glRotatef (mDebris[i].orientation[1], 0.0, 1.0, 0.0);
	  glRotatef (mDebris[i].orientation[2], 0.0, 0.0, 1.0);

	  glScalef (mDebris[i].scale[0],
		    mDebris[i].scale[1],
		    mDebris[i].scale[2]);

	  glBegin (GL_TRIANGLES);
	  glVertex3f (0.0, 0.5, 0.0);
	  glVertex3f (-0.25, 0.0, 0.0);
	  glVertex3f (0.25, 0.0, 0.0);
	  glEnd ();	  
	  
	  glPopMatrix ();
	}

  //glutSwapBuffers (); 
  idle();
	*/
  int    i;


  glLoadIdentity ();

  /* Place the camera */

  glTranslatef (0.0, 0.0, -10.0);
 // glRotatef (angle, 0.0, 1.0, 0.0);

  /* If no explosion, draw cube */
  glPushMatrix ();

      glDisable (GL_LIGHTING);
      glDisable (GL_DEPTH_TEST);

      glBegin (GL_POINTS);

	  for (i = 0; i < mNumParticles; i++)
	  {
		  glColor3fv (mParticles[i].colour);
	  glVertex3fv (mParticles[i].position);
	  }
  
      glEnd ();

      glPopMatrix ();

      glEnable (GL_LIGHTING); 
      glEnable (GL_LIGHT0); 
      glEnable (GL_DEPTH_TEST);

      glNormal3f (0.0, 0.0, 1.0);

      for (i = 0; i < mNumParticles; i++)
	{
		glColor3fv (mDebris[i].color);

	  glPushMatrix ();
      
	  glTranslatef (mDebris[i].position[0],
			mDebris[i].position[1],
			mDebris[i].position[2]);

	  glRotatef (mDebris[i].orientation[0], 1.0, 0.0, 0.0);
	  glRotatef (mDebris[i].orientation[1], 0.0, 1.0, 0.0);
	  glRotatef (mDebris[i].orientation[2], 0.0, 0.0, 1.0);

	  glScalef (mDebris[i].scale[0],
		    mDebris[i].scale[1],
		    mDebris[i].scale[2]);

	  glBegin (GL_TRIANGLES);
	  glVertex3f (0.0, 0.5, 0.0);
	  glVertex3f (-0.25, 0.0, 0.0);
	  glVertex3f (0.25, 0.0, 0.0);
	  glEnd ();	  
	  
	  glDisable (GL_LIGHTING); 
      glDisable (GL_LIGHT0); 

	  glPopMatrix ();
	}
}

void Explosion::idle(void){
	int i;
	if(mFuel > 0){
		for(i = 0; i < mNumParticles; i++){
			mParticles[i].position[0] += mParticles[i].speed[0] * mSpeed;
			mParticles[i].position[1] += mParticles[i].speed[1] * mSpeed;
			mParticles[i].position[2] += mParticles[i].speed[2] * mSpeed;

			mParticles[i].colour[0] -= 1.0 / 500.0;
			if(mParticles[i].colour[0] < 0.0)
				mParticles[i].colour[0] = 0.0;

			mParticles[i].colour[1] -= 1.0 / 100.0;
			if(mParticles[i].colour[1] < 0.0)
				mParticles[i].colour[1] = 0.0;

			mParticles[i].colour[2] -= 1.0 / 50.0;
			if(mParticles[i].colour[2] < 0.0)
				mParticles[i].colour[2] = 0.0;
		}

		for (i = 0; i < mNumDebris; i++)
	    {
	      mDebris[i].position[0] += mDebris[i].speed[0] * mSpeed;
	      mDebris[i].position[1] += mDebris[i].speed[1] * mSpeed;
	      mDebris[i].position[2] += mDebris[i].speed[2] * mSpeed;
	      
	      mDebris[i].orientation[0] += mDebris[i].orientationSpeed[0] * 10;
	      mDebris[i].orientation[1] += mDebris[i].orientationSpeed[1] * 10;
	      mDebris[i].orientation[2] += mDebris[i].orientationSpeed[2] * 10;
	    }

		--mFuel;
	}

	glutPostRedisplay();
}

