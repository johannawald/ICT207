/**
 * @class AudioManager
 * @brief Controller class for the audio assets
 *
 * Implements the basic functions to work with audio files: init(), reload(), clearMemory() and a List to manage them
 *
 * @author Johanna Wald
 * @version 01
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 * @date 25/10/2013 Raymond Forster - added loading of background music and bomb explosion
 * @date 26/10/2013 Raymond Forster - fixes to naming
 */

#pragma once

#include "IAssetManager.h"

enum eSounds { sStep, sMetalicCrash, sIncorrectCode,
			   sBgMusic, sBomb, sTextMsg,
			   AUDIOSOUNDS_SIZE };

class CSound;
class CEasySound;
class AudioManager: public IAssetManager {
private:
	CEasySound* mSound; /**< Helps the class to load and store the sounds in the list */
	CSound* mSounds[AUDIOSOUNDS_SIZE];  /**< Array that stores the sounds */	
public:
	/**
		* @brief constructor of the AudioManager
	*/
	AudioManager();
	/**
		* @brief destructor of the AudioManager
	*/
	~AudioManager();	
	/**
		* @brief loads the audio files
        * @param none
		* @return void
	*/
	void init();
	/**
		* @brief clears the memory and reloads the files it case they changed
        * @param none
		* @return void
	*/
	void reload();
	/**
		* @brief clearMemory	
        * @param none
		* @return void
	*/
	void clearMemory();
	/**
		* @brief calls the play-function of the sound-object 
		* stored in the list on position of the parameter audio
        * @param eSounds audio - the enum of the sound that should be played it represents the position of the file in the list the class stores
		* @return void
	*/
	void playSound(const eSounds mAudio) const;
	/**
		* @brief calls the stop-function of the sound-object 
		* stored in the list on position of the parameter audio
        * @param eSounds audio - the enum of the sound that should be played it represents the position of the file in the list the class stores
		* @return void
	*/
	void StopSound(const eSounds mAudio) const;
};
