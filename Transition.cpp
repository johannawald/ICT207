#include "Transition.h"
#include <GL/glut.h>
#include "StateMachine.h"
#include "GameController.h"

Transition::Transition(): Code("1337"), InsertedCode(""), state(tsVendingMachine), Char(' '), AnimationFrame(0)
{

}

TransitionState Transition::getstate() const
{
	return state;
}

std::string Transition::getInsertedCode() const
{
	return InsertedCode;
}

int Transition::getAnimationFrame() const
{
	return AnimationFrame;
}

void Transition::Update(TransitionState tstate) 
{
	if (tstate==tsHole) {
		AnimationFrame++;
		if (AnimationFrame>100) {
			InsertedCode = "";
		}
		glutSetCursor(0);
	}
	else if (tstate==tsNone)
	{
		AnimationFrame=0;
		glutSetCursor(0);
	}

	state = tstate;
}

void Transition::CheckMouseInput() 
{
	if ((state == tsNumberPad) && (Char!=' ')) {
		if (Char=='*') 
			InsertedCode = "";
		else
			InsertedCode += Char;
	}
}

void Transition::CheckMousePosition(int x, int y, int width, int height)
{	
	if (x>(width * 0.65) && (state == tsVendingMachine))  
		state = tsNumberPad;
 	if (state == tsNumberPad)
	{
		if (state == tsNumberPad)
		{
			bool mouse = (x>(width * 0.7)) && (y<height*0.3);
			glutSetCursor(0);
		
			if (state == tsNumberPad) {
				if ((x>(width*0.64)) && (x<(width*0.67))) {
					if ((y>height*0.15) && (y<height*0.2)) Char = 'A';
					else if ((y>height*0.26) && (y<height*0.34)) Char = 'D';
					else if ((y>height*0.38) && (y<height*0.45)) Char = 'C';
					else if ((y>height*0.49) && (y<height*0.56)) Char = '1';
					else if ((y>height*0.61) && (y<height*0.69)) Char = '4';
					else if ((y>height*0.72) && (y<height*0.80)) Char = '7';
					else if ((y>height*0.85) && (y<height*0.92)) Char = '*';
					else Char = ' ';
				}
				//2nd row 
				else if ((x>(width*0.70)) && (x<(width*0.73))) {
					if ((y>height*0.15) && (y<height*0.23)) Char = 'B';
					else if ((y>height*0.26) && (y<height*0.34)) Char = 'E';
					else if ((y>height*0.38) && (y<height*0.46)) Char = 'H';
					else if ((y>height*0.51) && (y<height*0.59)) Char = '2';
					else if ((y>height*0.63) && (y<height*0.71)) Char = '5';
					else if ((y>height*0.76) && (y<height*0.84)) Char = '8';
					else if ((y>height*0.88) && (y<height*0.97)) Char = '0';
					else Char = ' ';
				}
				//3rd row
				else if ((x>(width*0.76)) && (x<(width*0.81))) {
					if ((y>height*0.15) && (y<height*0.23)) Char = 'C';
					else if ((y>height*0.26) && (y<height*0.35)) Char = 'F';
					else if ((y>height*0.38) && (y<height*0.48)) Char = 'J';
					else if ((y>height*0.53) && (y<height*0.61)) Char = '3';
					else if ((y>height*0.66) && (y<height*0.76)) Char = '6';
					else if ((y>height*0.79) && (y<height*0.88)) Char = '9';
					else if ((y>height*0.91) && (y<height)) Char = '#';
					else Char = ' ';
				}
				else Char = ' ';
			
				if (Char!=' ') 
					glutSetCursor(GLUT_CURSOR_INFO);
				else 
					glutSetCursor(0);  
			}
		}
	}	  
}

bool Transition::IsCorrectCode() const
{ 
	return InsertedCode == Code;
}

bool Transition::IsCodeStartedCorrect() const
{ 
	if (InsertedCode.length() > Code.length())
		return false;
	else 
		return Code.substr(0,InsertedCode.length()) == InsertedCode; 
}

bool Transition::IsPlayMechanicSound() const
{ 
	return AnimationFrame==0;
} 

void Transition::AutoCorrection()  { 
	InsertedCode = "";
} 
