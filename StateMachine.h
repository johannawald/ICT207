/**
 * @StateMachine
 *
 * @author Johanna Wald, StateMachine, 16/09/2013
 * @version 1
 * @date 16/09/2013 Johanna Wald - Started
 * @date 01/10/2013 Johanna Wald - Added forward declaration for faster compiling
 * @date 10/10/2013 Johanna Wald - Added MouseMotion()-function
 */

#pragma once

class IStateController;
class ModelManager;
class TextureManager;
class AudioManager;
class StateMachine {
private:
	//save the bushcourtcontroller in a member-variable, since it takes a long time to reload it
	ModelManager* mModelmanager;
	TextureManager* mTexturemanager;
	AudioManager* mAudiomanager;

	static IStateController* mBushcourtController; 
	static bool mInit;
    static StateMachine* mStateMachine;
	//private constructor since the state machine is a singelton
	StateMachine(IStateController* pController);
public:	
		/**
         * @brief Current state of the program (All the control functions below will call the function of this state)
		 */
	IStateController* mState;
		/**
         * @brief initalization / access method for the singelton (it's the only way to create the object, since the constructor is private)
		 */
	static StateMachine* getInstance();
		/**
         * @brief function to set the bush court controller (avoid reloading all the images)
		 */
	static void setBushCourtController();
		/**
         * @brief Set function for the state - changes the current state of the game
		 * @param IStateController* - the new state
		 */
	static void setController(IStateController* pController);
		/**
         * @brief Destructor destroys StateMachine object when it goes out of scope.
         */
	~StateMachine();

		/**
         * @brief Calls the Init() function of the appropriate State.
        */
	void Init();

		/**
         * @brief Calls the Draw() function of the appropriate State.
         */
	void Draw();

		/**
         * @brief Calls the Update() function of the appropriate State.
         */
	void Update();

		/**
         * @brief Calls the SpecialKey() function of the appropriate State.
		 *
		 * @param int key - the key pressed
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	void SpecialKey(int key, int x, int y);

		/**
         * @brief Calls the SpecialKeyUp() function of the appropriate State.
		 *
		 * @param int key - the key pressed
		 * @param int x - the x position of the mouse
		 * @param int y - the y poition of the mouse
         */
	void SpecialKeyUp(int key, int x, int y);

		/**
         * @brief Calls the KeyboardUp() function of the appropriate State.
		 *
		 * @param unsigned char key - the keyboard key
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	void KeyboardUp(unsigned char key, int x, int y);

		/**
         * @brief Calls the Keyboard() function of the appropriate State.
		 *
		 * @param unsigned char key - the keyboard key pressed
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	void Keyboard(unsigned char key, int x, int y);

		/**
         * @brief Calls the Mouse() function of the appropriate State.
		 *
		 * @param int button - the mouse button pressed
		 * @param int state - the state of the mouse button pressed (eg. state == GLUT_DOWN)
		 * @param int x - the x position of the mouse
		 * @param int y - the y position of the mouse
         */
	void Mouse(int button, int state, int x, int y);

		/**
         * @brief Calls the PassiveMotion() function of the appropriate State.
		 *
		 * @param int x - the x position of the mouse 
		 * @param int y - the y position of the mouse
         */
	void PassiveMotion(int x, int y);
		/**
         * @brief Calls the MouseMotion() function of the appropriate State.
		 *
		 * @param int x - the x position of the mouse 
		 * @param int y - the y position of the mouse
         */
	void MouseMotion(int x, int y);
		/**
         * @brief Calls the Reshape() function of the appropriate State.
		 *
		 * @param int w - the width of the screen
		 * @param int h - the height of the screen
         */
	void Reshape(int w, int h);
};