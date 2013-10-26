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
	mSound = CEasySound::Instance();
	mSounds[0] = mSound->GetSound(mSound->Load("sounds/step.wav"));
	mSounds[1] = mSound->GetSound(mSound->Load("sounds/Mechanical.wav")); 
	mSounds[2] = mSound->GetSound(mSound->Load("sounds/131657__bertrof__game-sound-wrong.wav")); 
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
	for (int i = 0; i<2 ;i++)
		mSound->Unload(mSounds[i]);
	delete mSound;
}
