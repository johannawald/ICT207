/**
 * @class Transition
 * @brief Class to control the Transition to the game level
 *
 * It manages the transition state (with the enum 'TransitionState') and variables for the 
 * Animation and the user interface to insert the code
 * 
 * @author Johanna Wald
 * @version 01
 * @date 18/09/2013 Johanna Wald - Basic Implementation
 */


#pragma once

#include <string>

enum TransitionState { tsNone, tsVendingMachine, tsNumberPad, tsHole, tsFallAnimation };

class Transition
{
private:
	TransitionState state; 
	std::string InsertedCode; 
	char Char;
	int AnimationFrame;
	const std::string Code;
public:
	Transition();
	/**
		* @brief get-function for the private state member variable
        * @param none
		* @return TransitionState - current transition state
	*/
	TransitionState getstate();
	/**
		* @brief get-function for the private InsertedCode member variable
        * @param none
		* @return std::string - the inserted code for the vending machine
	*/
	std::string getInsertedCode();
	/**
		* @brief get-function for the private AnimationFrame member variable
		* It represents the Frame-Count since the Transition started
        * @param none
		* @return int - returns the value of the member variable "AnimationFrame"s
	*/
	int getAnimationFrame();
	/**
		* @brief Set-function for the state member variable
        * @param TransitionState
		* @return void
	*/
	void Update(TransitionState tstate);
	/**
		* @brief Procedure to perform the auto correction of the code 
		* (if the inserted is wrong + play sound)
        * @param none
		* @return void
	*/
	void AutoCorrection();
	/**
		* @brief Returns true, if the user enterd the right code
        * @param none
		* @return bool - true, if the code is correct
	*/
	bool IsCorrectCode();
	/**
		* @brief Returns true, if the user input starts correct
        * @param none
		* @return bool - true, if the beginning of the code is correct, but some digits are missing
	*/
	bool IsCodeStartedCorrect();
	/**
		* @brief Returns true, if the animation of the just started (AnimationFrame is 0)
        * @param none
		* @return bool - true, if the animation of the just started
	*/
	bool IsPlayMechanicSound();
	/**
		* @brief Handles the Mouse input especially if the user 
		* clicks on the buttons on the numberpad of the vending machine
        * @param none
		* @return void
	*/
	void CheckMouseInput();
	/**
		* @brief Handles the mouse position and changes the cursor if the mouse if over a "button"
        * @param int x - x-coordinate of the mouse on the screen
	    * @param int y - y-coordinate of the mouse on the screen
		* @param int width - width of the screen
		* @param int height - height of the screen
		* @return void
	*/
	void CheckMousePosition(int x, int y, int width, int height);
};
