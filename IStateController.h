/**
 * @class IStateController
 * @brief Interface defines a StateController with its functions
 *
 * Defines the basic functions a StateController that interacts with the user should implement such as Init(), Update(), Draw()
 *
 * @author Johanna Wald
 * @version 01
 * @date 19/09/2013 Johanna Wald - Basic Implementation
 */

#pragma once

class IStateController {
public:	
	/**
		* @brief empty, virtual destructor that makes sure that the class will clear the memory
		* virtual is important since the class should be cleared even if there is there is a list of pointers of it
	*/
	virtual ~IStateController() {};
	/**
		* @brief abstract, virtual init-function
	*/
	virtual void Init() = 0;
	/**
		* @brief abstract, virtual Update function for the state 
	*/
	virtual void Update() = 0;
	/**
		* @brief abstract, virtual Draw function for the state
	*/
	virtual void Draw() = 0;
	/**
		* @brief abstract, virtual SpecialKey function for the state
	*/
	virtual void SpecialKey(int key, int x, int y) = 0;
	/**
		* @brief abstract, virtual SpecialKeyUp function for the state
	*/
	virtual void SpecialKeyUp(int key, int x, int y) = 0;
	/**
		* @brief abstract, virtual KeyboardUp function for the state
	*/
	virtual void KeyboardUp(unsigned char key, int x, int y) = 0;
	/**
		* @brief abstract, virtual Keyboard function for the state
	*/
	virtual void Keyboard(unsigned char key, int x, int y) = 0;
	/**
		* @brief abstract, virtual Mouse function for the state
	*/
	virtual void Mouse(int button, int state, int x, int y) = 0;
	/**
		* @brief abstract, virtual PassiveMotion function for the state
	*/	
	virtual void PassiveMotion(int x, int y) = 0;
	/**
		* @brief abstract, virtual Reshape function for the state
	*/	
	virtual void Reshape(int w, int h) = 0;
};
