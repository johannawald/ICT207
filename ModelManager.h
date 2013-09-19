//  @ Unit : ICT207
//  @ File Name : ModelManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssertManager.h"
#include <GL/freeglut.h>

enum eModels { mAdvertisement,
			 MODELS_SIZE };

class ModelLoader;
class ModelManager: public IAssertManager {
private:
	ModelLoader* Models[MODELS_SIZE]; 	
public:		
	ModelManager();
	~ModelManager();		
	void init();
	void reaload();
	void drawModel(eModels model, GLuint texture = 0);
};
