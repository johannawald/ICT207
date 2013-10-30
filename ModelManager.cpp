#include "ModelManager.h"
#include "ModelLoader.h"
#include <iostream>

ModelManager::ModelManager()
{
	init();
}

ModelManager::~ModelManager()
{
	clearMemory();
}

void ModelManager::init()
{
	for (int i = 0; i < MODELS_SIZE; i++) 
		mModels[i] = new ModelLoader;

	mModels[mAdvertisement]->load("models/advertisement.obj");
	mModels[m4x1platform]->load("models/4x1platform.obj");
	mModels[mConsole]->load("models/console.obj");
	mModels[mLadder]->load("models/ladder.obj");
	mModels[mBox]->load("models/robot.obj"); //box
	mModels[mButton]->load("models/button.obj");
	//mModels[mBox2]->load("models/box4.obj");
	std::cout << "Models Loaded." << std::endl;
}

void ModelManager::reload()
{
	clearMemory();
	init();
}

void ModelManager::drawModel(const eModels model, const GLuint texture) const
{
	glPushMatrix();
		if (texture>0)
			glBindTexture(GL_TEXTURE_2D, texture);
		mModels[model]->draw();
		glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}

void ModelManager::clearMemory()
{
	//work in progress
	//delete Models[5]; ?
}
