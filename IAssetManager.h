/**
 * @class IAssetManager.h
 * @brief Interface defines a AssetManager with its functions
 *
 * Defines the basic functions a AssetManager should implement: init(), reload(), clearMemory()
 *
 * @author Johanna Wald
 * @version 01
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

class IAssetManager {
public:			
	/**
		* @brief abstract function; should initialize the assets
        * @param none
		* @return void
	*/
	virtual void init() = 0;
	/**
		* @brief abstract function; should reload the assets
        * @param none
		* @return void
	*/
	virtual void reload() = 0;
	/**
		* @brief abstract function; should clear all the memory
        * @param none
		* @return void
	*/
	virtual void clearMemory() = 0;
};
