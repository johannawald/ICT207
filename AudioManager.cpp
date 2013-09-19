#include "AudioManager.h"
#include "EasySound.h"

AudioManager::AudioManager()
{
	init();
}

AudioManager::~AudioManager()
{
	for (int i = 0; i<2 ;i++)
		es->Unload(Sounds[i]);
}

void AudioManager::init()
{
	// sound objects
	es = CEasySound::Instance();
	Sounds[0] = es->GetSound(es->Load("sounds/step.wav"));
	Sounds[1] = es->GetSound(es->Load("sounds/Mechanical.wav")); 
}

void AudioManager::reaload()
{
	//
}

void AudioManager::playSound(AudioSounds audio)
{
	Sounds[audio]->Play();
}
