#include "AudioManager.h"
#include "EasySound.h"

AudioManager::AudioManager()
{
	init();
}

AudioManager::~AudioManager()
{
	clearMemory();
}

void AudioManager::init()
{
	// sound objects - later we should not work with the CEasySound
	es = CEasySound::Instance();
	Sounds[asStep] = es->GetSound(es->Load("sounds/step.wav"));
	Sounds[asMetalicCrash] = es->GetSound(es->Load("sounds/Mechanical.wav")); 
	Sounds[asIncorrectCode] = es->GetSound(es->Load("sounds/131657__bertrof__game-sound-wrong.wav"));
	Sounds[asBgMusic] = es->GetSound(es->Load("sounds/BackgroundMusic.wav"));
	Sounds[asBomb] = es->GetSound(es->Load("sounds/TimeBomb.wav"));
}

void AudioManager::reload()
{
	clearMemory();
	init();
}

void AudioManager::playSound(const eAudioSounds audio) const
{
	Sounds[audio]->Play();
}

void AudioManager::clearMemory()
{
	delete es;
	for (int i = 0; i<2 ;i++)
		es->Unload(Sounds[i]);
}
