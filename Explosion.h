// explosion.h
// header file for explosion class
//
//
// Daniel manganaro
#include <GL/glut.h>

#ifndef EXPLOSION_H
#define EXPLOSION_H
#define NUM_PARTICLES 1000
#define NUM_DEBRIS 100

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
	particle mParticles[NUM_PARTICLES];
	debrisData mDebris[NUM_DEBRIS];
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


