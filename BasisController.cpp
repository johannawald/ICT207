#include "BasisController.h"
#include "DrawManager.h"
#include "AudioManager.h"

BasisController::BasisController(AudioManager* audiomanager, ModelManager* modelmanager, TextureManager* texturemanager): audio(audiomanager), model(modelmanager), texture(texturemanager)
{	
	drawmanager = new DrawManager();
}

AudioManager* BasisController::GetAudio() const
{	
	return audio;
}

ModelManager* BasisController::GetModel() const
{	
	return model;
}

TextureManager* BasisController::GetTexture() const
{	
	return texture;
}

void BasisController::SetAudio(AudioManager* am)
{	
	audio = am;
}

void BasisController::SetModel(ModelManager* mm)
{	
	model = mm;
}

void BasisController::SetTexture(TextureManager* tm)
{	
	texture = tm;
}
