//  Transition.cpp

#include "Transition.h"

Transition::Transition(): Code("000"), state(tsNone), DisplayVendingMachine(false), Number(""), MouseRightSideScreen(false), Char(' '), FallAnimation(false), DisplayBuySweets(false), waited_frames(0), DisplaySecretStairs(false)
{

}

Transition::~Transition()
{
	
}

void Transition::Update() 
{
	
}
