/**
 * @class AudioManager
 * @brief Controller class for the audio assets
 *
 * Implements the basic functions to work with audio files: init(), reload(), clearMemory() and a List to manage them
 *
 * @author Johanna Wald
 * @version 01
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

#include "IAssetManager.h"

enum eSounds { asStep, asMetalicCrash, asIncorrectCode, AUDIOSOUNDS_SIZE };

class CSound;
class CEasySound;
class AudioManager: public IAssetManager {
private:
	CEasySound* es; /**< Helps the class to load and store the sounds in the list */
	CSound* Sounds[AUDIOSOUNDS_SIZE];  /**< Array that stores the sounds */	
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
		* @brief abstract function; should initialize the assets
        * @param eSounds audio - the enum of the sound that should be played it represents the position of the file in the list the class stores
		* @return void
	*/
	void playSound(const eSounds audio) const;
};
