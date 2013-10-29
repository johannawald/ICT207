#include "AudioManager.h"
#include "EasySound.h"
#include <iostream>

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
	mSound = CEasySound::Instance();
	mSounds[sStep] = mSound->GetSound(mSound->Load("sounds/step.wav"));
	mSounds[sMetalicCrash] = mSound->GetSound(mSound->Load("sounds/Mechanical.wav")); 
	mSounds[sIncorrectCode] = mSound->GetSound(mSound->Load("sounds/131657__bertrof__game-sound-wrong.wav"));
	mSounds[sBgMusic] = mSound->GetSound(mSound->Load("sounds/BackgroundMusic.wav"));
	mSounds[sBomb] = mSound->GetSound(mSound->Load("sounds/TimeBomb.wav"));
	std::cout << "Sounds Loaded." << std::endl;
}

void AudioManager::reload()
{
	clearMemory();
	init();
}

void AudioManager::playSound(const eSounds audio) const
{
	mSounds[audio]->Play();
}

void AudioManager::clearMemory()
{
	delete mSound;
	for (int i = 0; i<2 ;i++)
		mSound->Unload(mSounds[i]);
}
