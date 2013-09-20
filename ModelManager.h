//  @ Unit : ICT207
//  @ File Name : ModelManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssetManager.h"
#include <GL/freeglut.h>

enum eModels { mAdvertisement,
			 MODELS_SIZE };

class ModelLoader;
class ModelManager: public IAssetManager {
private:
	ModelLoader* Models[MODELS_SIZE]; 	
public:		
	ModelManager();
	~ModelManager();		
	void init();
	void reload();
	void clearMemory();
	void drawModel(eModels model, GLuint texture = 0);
};
