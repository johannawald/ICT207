/**
 * @class GameControllerLevelOne
 * @brief The GameController should manage the Game itself
 *
 * The GameController should later manage the game itself with it levels 
 * and settings and stuff like that
 *
 * @author Johanna Wald
 * @version 01
 * @date 15/09/2013
 */

#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include "IStateController.h"
#include "GameObject.h"
#include "GameController.h"

class GameControllerLevelOne : public GameController
{
private:
	virtual void DrawObjects();	
	virtual void InitGameObjects();
public:
	GameControllerLevelOne(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture);

};
