#include "ModelManager.h"
#include "ModelLoader.h"

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

	mModels[0]->load("models/advertisement.obj");
	mModels[1]->load("models/4x1platform.obj");
	mModels[2]->load("models/console.obj");
	mModels[3]->load("models/ladder.obj");
	mModels[4]->load("models/box.obj");
	mModels[5]->load("models/button.obj");
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
