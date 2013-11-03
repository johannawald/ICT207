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

void AudioManager::FmodErrorCheck(FMOD_RESULT pResult)	// this is an error handling function
{						// for FMOD errors
	if (pResult != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", pResult, FMOD_ErrorString(pResult));
		exit(-1);
	}
}

void AudioManager::init()
{
	/*FMOD_RESULT result;
	result = FMOD_System_Create(&mFMOD);
	FmodErrorCheck(result);*/

	//result = mFMOD->init();
	//->init(32, FMOD_INIT_NORMAL, 0);
	//FmodErrorCheck(result);

	// sound objects - later we should not work with the CEasySound
	mSound = CEasySound::Instance();
	mSounds[sStep] = mSound->GetSound(mSound->Load("sounds/step.wav"));
	mSounds[sMetalicCrash] = mSound->GetSound(mSound->Load("sounds/Mechanical.wav")); 
	mSounds[sIncorrectCode] = mSound->GetSound(mSound->Load("sounds/131657__bertrof__game-sound-wrong.wav"));
	mSounds[sBgMusic] = mSound->GetSound(mSound->Load("sounds/BackgroundMusic.wav"));
	mSounds[sBomb] = mSound->GetSound(mSound->Load("sounds/TimeBomb.wav"));
	mSounds[sTextMsg] = mSound->GetSound(mSound->Load("sounds/TextMsg.wav"));
	std::cout << "Sounds Loaded." << std::endl;
}

void AudioManager::reload()
{
	clearMemory();
	init();
}

void AudioManager::playSound(const eSounds mAudio) const
{
	mSounds[mAudio]->Play();
}

void AudioManager::StopSound(const eSounds mAudio) const //why??
{
	mSounds[mAudio]->Stop();
}

void AudioManager::clearMemory()
{
	delete mSound;
	for (int i = 0; i<2 ;i++)
		mSound->Unload(mSounds[i]);
}
