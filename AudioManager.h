//  @ Unit : ICT207
//  @ File Name : AudioManager.h
//  @ Author : Johanna Wald
//
//

#pragma once

#include "IAssetManager.h"

enum eSounds { asStep, asMetalicCrash, asIncorrectCode, 
				   AUDIOSOUNDS_SIZE };

class CSound;
class CEasySound;
class AudioManager: public IAssetManager {
private:
	CEasySound* es;
	CSound* Sounds[AUDIOSOUNDS_SIZE]; 	
public:		
	AudioManager();
	~AudioManager();		
	void init();
	void reaload();
	void playSound(eSounds audio);
};
