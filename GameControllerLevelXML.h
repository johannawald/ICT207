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
 * @date 10/10/2013 Johanna Wald - set up class
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
#include "tinyxml\tinyxml.h"

class GameControllerLevelXML : public GameController
{
private:
	TiXmlDocument mDoc;
	TiXmlNode* mRoot;
	int GetCurrentLevel();
	virtual void DrawObjects();	
	virtual void InitGameObjects();
	Vector3D GetVecFromAttr(TiXmlElement* objelem, const char* pName);
	int GetIntAttribute(TiXmlElement* objelem, const char* pName);
	double GetDoubleAttribute(TiXmlElement* objelem, const char* pName);

protected:
	virtual void OnBeforeWin(); //*JW
public:
	GameControllerLevelXML(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture, float pHeight, float pWidth, int pLevelNr);
};
