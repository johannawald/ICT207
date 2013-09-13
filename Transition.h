//  Transition.h //*JW

#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>

//--------------------------------------------------------------------------------------

enum TransitionState { tsNone, tsVendingMachine, tsMouseBuyButton, tsNumberPad, tsHole, tsFallAnimation };

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
	void Update();
};

#endif