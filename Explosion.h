/** 
 * @class Explosion
 * @brief implements an explosion at a given point
 *
 * @author Daniel manganaro
 * @date 30/10/2013 Johanna Wald - changed variable names - naming convention
 */

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
	const int mNumParticles; /**<number of particles in the explosion */
	const int mNumDebris; /**< number of debris in the explosion */

	Particle mParticles[10000];
	DebrisData mDebris[5000];
	int mFuel;
	float mSpeed;

public:
	/*
	 * @brief constructor of the explosion
	 */
	Explosion();
	/*
	 * @brief alternative constructor of the explosion
	 */ 
	Explosion(float);
	/*
	 * @brief sets the size of the explosion
	 * @param const int p number of particles, const int d number of debris 
	 * @return void
	 */
	void setSize(const int p, const int d);
	/*
	 * @brief sets the speed of the particles and the debris
	 * @param float[] array containing the x, y and z values for the speed
	 * @return void
	 */
	void newSpeed(float[]);
	/*
	 * @brief creates a new explosion at the position x, y and z
	 * @params float x, float y, float z, 
	 * @return void
	 */
	void newExplosion(float x, float y, float z);
	/*
	 * @brief updates the position of the particles and debris causing the explosion
	 * @params void
	 * @return void
	 */
	void Update();
	/*
	 * @brief draws the particles and debris in their initial position
	 * @params void
	 * @return void
	 */
	void Draw();
};

#endif


