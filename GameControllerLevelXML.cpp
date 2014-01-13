#include "GameControllerLevelXML.h"
#include "StateMachine.h"
#include "DrawManager.h"
#include <sstream>
#include <iostream>

GameControllerLevelXML::GameControllerLevelXML(AudioManager* pAudio, ModelManager* pModel, TextureManager* pTexture, float pHeight, float pWidth): 
	GameController(pAudio, pModel, pTexture, pHeight, pWidth)
{
	mDoc.LoadFile("levels.xml");
	mRoot = mDoc.FirstChild("levels");
	mLevelNr = GetCurrentLevel();
}

void GameControllerLevelXML::OnBeforeWin()
{
	TiXmlElement* nodeElement = mRoot->ToElement();
	if (mLevelNr==mMaxLevels)
	{
		nodeElement->SetAttribute("current", 1);
		mDoc.SaveFile();
	}
	else
	{
		nodeElement->SetAttribute("current", mLevelNr+1);
		mDoc.SaveFile();
		mNextState = new GameControllerLevelXML(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth());
	}
	
	GameController::OnBeforeWin();
}

int GameControllerLevelXML::GetCurrentLevel()
{
	TiXmlElement* nodeElement = mRoot->ToElement();
	std::string current = nodeElement->Attribute("current");
	return atoi(current.c_str());
}

void GameControllerLevelXML::DrawObjects() 
{
	glPushMatrix();
		DrawTimer();
	glPopMatrix();
}

Vector3D GameControllerLevelXML::GetVecFromAttr(TiXmlElement* objelem, const char* pName)
{
	TiXmlElement* elemente = objelem->FirstChild()->ToElement();
	TiXmlNode* node;
	const char* pValue = elemente->Value();
	while (strcmp(pName, pValue) != 0)
	{
		node = elemente->NextSibling();
		if (node!=nullptr) 
			elemente = node->ToElement();
		pValue = elemente->Value();
	}
	Vector3D vector = Vector3D(GetDoubleAttribute(elemente, "x"), GetDoubleAttribute(elemente, "y"), GetDoubleAttribute(elemente, "z"));
	return vector;
}

double GameControllerLevelXML::GetDoubleAttribute(TiXmlElement* objelem, const char* pName)
{
	std::string attr = objelem->Attribute(pName);
	return atof(attr.c_str());
}

int GameControllerLevelXML::GetIntAttribute(TiXmlElement* objelem, const char* pName)
{
	std::string attr = objelem->Attribute(pName);
	return atoi(attr.c_str());
}

void GameControllerLevelXML::InitGameObjects()
{
	int index = 0;
	int boxes = 0;
	
	TiXmlNode* node = mRoot->FirstChild();
	
	std::stringstream ss;
	ss << mLevelNr;
	std::string msLevelNr = ss.str();

	TiXmlElement* nodeElement;
	while (node!=nullptr)
	{
		nodeElement = node->ToElement();
		if (nodeElement->Attribute("number")==msLevelNr)
		{
			SetLevelTime(GetIntAttribute(nodeElement, "time"));
			TiXmlNode* object = node->FirstChild();
			while (object!=nullptr)
			{
				TiXmlElement* objelem = object->ToElement();
				std::string value = objelem->Value();
				if (value=="wall") 
					addCollisionGameObject(GetVecFromAttr(objelem, "position"), GetVecFromAttr(objelem, "movement"), GetVecFromAttr(objelem, "size"), GetVecFromAttr(objelem, "scale"), GetVecFromAttr(objelem, "rotation"), GetIntAttribute(objelem, "model"), GetIntAttribute(objelem, "texture"), GetIntAttribute(objelem, "TextureX"), GetIntAttribute(objelem, "TextureY"), index);
				else if (value=="bomb")
					addCollisionGameObject(GetVecFromAttr(objelem, "position"), GetVecFromAttr(objelem, "movement"), GetVecFromAttr(objelem, "size"), GetVecFromAttr(objelem, "scale"), GetVecFromAttr(objelem, "rotation"), GetIntAttribute(objelem, "model"), GetIntAttribute(objelem, "texture"), GetIntAttribute(objelem, "TextureX"), GetIntAttribute(objelem, "TextureY"), mBombIndex);
				else if (value=="box")
				{
					boxes++;
					if (boxes==0)
						addCollisionGameObject(GetVecFromAttr(objelem, "position"), GetVecFromAttr(objelem, "movement"), GetVecFromAttr(objelem, "size"), GetVecFromAttr(objelem, "scale"), GetVecFromAttr(objelem, "rotation"), GetIntAttribute(objelem, "model"), GetIntAttribute(objelem, "texture"), GetIntAttribute(objelem, "TextureX"), GetIntAttribute(objelem, "TextureY"), mBoxesCollisionIndex1);
					else if (boxes==1)
						addCollisionGameObject(GetVecFromAttr(objelem, "position"), GetVecFromAttr(objelem, "movement"), GetVecFromAttr(objelem, "size"), GetVecFromAttr(objelem, "scale"), GetVecFromAttr(objelem, "rotation"), GetIntAttribute(objelem, "model"), GetIntAttribute(objelem, "texture"), GetIntAttribute(objelem, "TextureX"), GetIntAttribute(objelem, "TextureY"), mBoxesCollisionIndex1);
					else if (boxes==2)
						addCollisionGameObject(GetVecFromAttr(objelem, "position"), GetVecFromAttr(objelem, "movement"), GetVecFromAttr(objelem, "size"), GetVecFromAttr(objelem, "scale"), GetVecFromAttr(objelem, "rotation"), GetIntAttribute(objelem, "model"), GetIntAttribute(objelem, "texture"), GetIntAttribute(objelem, "TextureX"), GetIntAttribute(objelem, "TextureY"), mBoxesCollisionIndex1);
				}
				object = object->NextSibling();
			}
		}
		node = node->NextSibling();
	}
}

