//  @ Unit : ICT207
//  @ File Name : AudioManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssertManager.h"

enum AudioSounds { asStep, asMetalicCrash, asIncorrectCode, 
				   AUDIOSOUNDS_SIZE };

class CSound;
class CEasySound;
class AudioManager: public IAssertManager {
private:
	CEasySound* es;
	CSound* Sounds[AUDIOSOUNDS_SIZE]; 	
public:		
	AudioManager();
	~AudioManager();		
	void init();
	void reaload();
	void playSound(AudioSounds audio);
};
