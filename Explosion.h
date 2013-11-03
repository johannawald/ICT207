// explosion.h
// header file for explosion class
//
//
// Daniel manganaro
// Johanna Wald - changed variable names - naming convention

#include <GL/glut.h>

#ifndef EXPLOSION_H
#define EXPLOSION_H

struct Particle {
	GLfloat mPosition[3];
	GLfloat mSpeed[3];
	GLfloat mColour[3];
};

struct DebrisData
{
	float mPosition[3];
	float mSpeed[3];
	float mOrientation[3];       
	float mOrientationSpeed[3];
	float mColor[3];
	float mScale[3];
};

class Explosion {
private:
	const int mNumParticles;
	const int mNumDebris;

	Particle mParticles[10000];
	DebrisData mDebris[5000];
	int mFuel;
	float mSpeed;

public:
	Explosion();
	Explosion(float);
	void setSize(const int p, const int d);
	void newSpeed(float[]);
	void newExplosion(float x, float y, float z);
	void idle();
	void draw(const GLint pTexture);
};

#endif


