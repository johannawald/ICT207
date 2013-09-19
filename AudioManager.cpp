#include "AudioManager.h"
#include "EasySound.h"

AudioManager::AudioManager()
{
	init();
}

AudioManager::~AudioManager()
{
	//clear(); abstract?
	for (int i = 0; i<2 ;i++)
		es->Unload(Sounds[i]);
}

void AudioManager::init()
{
	// sound objects - later we should not work 
	es = CEasySound::Instance();
	Sounds[0] = es->GetSound(es->Load("sounds/step.wav"));
	Sounds[1] = es->GetSound(es->Load("sounds/Mechanical.wav")); 
	Sounds[2] = es->GetSound(es->Load("sounds/131657__bertrof__game-sound-wrong.wav")); 
}

void AudioManager::reaload()
{
	//do we really need that function?
}

void AudioManager::playSound(eSounds audio)
{
	Sounds[audio]->Play();
}
