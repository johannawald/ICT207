#include "ModelManager.h"
#include "ModelLoader.h"

ModelManager::ModelManager()
{
	init();
}

ModelManager::~ModelManager()
{
	//clear(); abstract?
	/*for (int i = 0; i<2 ;i++)
		es->Unload(Sounds[i]);
	*/
}

void ModelManager::init()
{
	for (int i = 0; i < MODELS_SIZE; i++) 
		Models[i] = new ModelLoader;

	Models[0]->load("data/test.obj"); //advertisement
}

void ModelManager::reload()
{
	//do we really need that function?
}

void ModelManager::drawModel(eModels model, GLuint texture)
{
	glPushMatrix();
		if (texture>0)
			glBindTexture(GL_TEXTURE_2D, texture);
		Models[model]->draw();
		glBindTexture(GL_TEXTURE_2D, -1);
	glPopMatrix();
}
