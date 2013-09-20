/**
 * @class BasisController.h
 * @brief Controller provides Manager
 *
 * Defines the basic functions a AssetManager should implement: init(), reload(), clearMemory()
 *
 * @author Johanna Wald
 * @version 01
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

#include "ModelManager.h"
#include "AudioManager.h"
#include "DrawManager.h"
#include "TextureManager.h"

class BasisController {
private:
	DrawManager* drawmanager;
	AudioManager* audio;
	ModelManager* model;
	TextureManager* texture;
protected:
	AudioManager* GetAudio() const;
	ModelManager* GetModel() const;
	TextureManager* GetTexture() const;

	void SetAudio(AudioManager* am);
	void SetModel(ModelManager* mm);
	void SetTexture(TextureManager* tm);
public:	
	BasisController(AudioManager* audiomanager, ModelManager* modelmanager, TextureManager* texturemanager); //const AudioManager* audiomanager, const ModelManager* modelmanager, TextureManager* texturemanager);
};
