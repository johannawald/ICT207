// explosion.h
// header file for explosion class
//
//
// Daniel manganaro
#include <GL/glut.h>

#ifndef EXPLOSION_H
#define EXPLOSION_H

struct particle{
		GLfloat position[3];
		GLfloat speed[3];
		GLfloat colour[3];
};
typedef struct particle;

struct debrisData
{
  float   position[3];
  float   speed[3];
  float   orientation[3];       
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
};
typedef struct debrisData;

class Explosion{
private:
	const int mNumParticles;
	const int mNumDebris;

	particle* mParticles;
	debrisData* mDebris;
	int mFuel;
	float mSpeed;

public:
	Explosion();
	Explosion(float);
	void newSpeed(float[]);
	void newExplosion(float x, float y, float z);
	void idle(void);
	void draw(void);
};

#endif


