//  Transition.h //*JW

#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>

//--------------------------------------------------------------------------------------

enum TransitionState { tsNone, tsVendingMachine, tsMouseBuyButton, tsNumberPad, tsHole, tsFallAnimation };
enum ReachtTransition {PlaySound, Move};

class Transition
{
//private:
public:
	TransitionState state; 

	bool DisplayVendingMachine; 
	bool DisplayBuySweets;
	bool DisplaySecretStairs;
	bool FallAnimation;
	bool MouseRightSideScreen;
	//number game entry:
	std::string Number; //*JW

	char Char;
	int waited_frames;
private:
	const std::string Code;
public:
	Transition();
	virtual ~Transition();
	ReachtTransition Update();
	void CheckMouseInput();
	void CheckMousePosition(int x, int y, int width, int height);
};

#endif