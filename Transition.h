//  Transition.h //*JW

#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>

//--------------------------------------------------------------------------------------

enum TransitionState { tsNone, tsVendingMachine, tsNumberPad, tsHole, tsFallAnimation };
enum ReachtTransition {PlaySound, Move};

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
	virtual ~Transition();
	//get-functions
	TransitionState getstate();
	std::string getInsertedCode();
	int getAnimationFrame();
	
	void Update(TransitionState tstate);
	void AutoCorrection();
	bool IsCorrectCode();
	bool IsCodeStartedCorrect();
	bool IsPlayMechanicSound();
	void CheckMouseInput();
	void CheckMousePosition(int x, int y, int width, int height);
};

#endif