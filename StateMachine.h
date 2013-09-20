/**
 * @StateMachine.h
 *
 * @author Johanna Wald, StateMachine, 16/09/2013
 * @version 01
 * @date 16/09/2013 Johanna Wald
 */

#pragma once

#include <vector>

class IStateController;
class ModelManager;
class TextureManager;
class AudioManager;
class StateMachine {
private:
	//save the bushcourtcontroller in a member-variable, since it takes a long time to reload it
	ModelManager* modelmanager;
	TextureManager* texturemanager;
	AudioManager* audiomanager;

	static IStateController* bushcourtcontroller; 
	static bool init;
    static StateMachine* statemachine;
	//private constructor since the state machine is a singelton
	StateMachine(IStateController* gamestate);
public:	
	IStateController* state;
	static StateMachine* getInstance();
	static void setBushCourtController();
	static void setController(IStateController* controller);

	~StateMachine();
	//These functions are called by the glut-events
	void Init();
	void Draw();
	void Update();
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void PassiveMotion(int x, int y);
	void Reshape(int w, int h);
};