//  @ Unit : ICT207
//  @ File Name : AudioManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssertManager.h"

enum AudioSounds { asStep, asMetalicCrash };

class CSound;
class CEasySound;
class AudioManager: public IAssertManager {
private:
	CEasySound* es;
	CSound* Sounds[1]; 	
public:		
	AudioManager();
	~AudioManager();		
	void init();
	void reaload();
	void playSound(AudioSounds audio);
};
