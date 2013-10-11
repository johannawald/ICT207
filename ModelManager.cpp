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
		Models[i] = new ModelLoader;

	Models[0]->load("models/advertisement.obj");
	Models[1]->load("models/4x1platform.obj");
	Models[2]->load("models/console.obj");
	Models[3]->load("models/ladder.obj");
	Models[4]->load("models/box.obj");
	Models[5]->load("models/button.obj");
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
		Models[model]->draw();
		glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}

void ModelManager::clearMemory()
{
	//work in progress
	//delete Models[5]; ?
}
