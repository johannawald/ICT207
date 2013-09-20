//  @ File Name : BasisController.h
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet -> later every state should have a view and maybe a model


// (general, abstract Controller-class for the MVC)
// provides virtual functions to set the model and the view
// all derived classes have to implement these (have their own view (derived from BasisView) and model (derived from BasisModel)) 

#pragma once

#include "ModelManager.h"
#include "TextureManager.h"

class DrawManager;
class AudioManager;
class BasisController {
private:
	
protected: //Is protected ok? Or should that be changed to privte? propably yes with a get function (just readable)
	DrawManager* drawmanager;
	AudioManager* audio;
	ModelManager* model;
	TextureManager* texture;
public:	
	BasisController();
	//how can I force the classes to have a constructor like this:
	//BasisController(const AudioManager* audiomanager, const ModelManager* modelmanager, TextureManager* texturemanager) = 0;
};
