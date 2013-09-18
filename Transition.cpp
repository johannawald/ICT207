//  Transition.cpp

//Transition to-do / Johanna's:
//-correct position 2D screen (top) -> size fullscreen support
//-3D-model advertisement
//-Buttons click lighting
//-Edge of the Building - where is it?
//-Show the inserted code -> + correct it?
//-get rid of the encapsulating of the sound in the camera-class!

#include "Transition.h"
#include <GL/glut.h>

//42 4F 4D 42 = B O M B
Transition::Transition(): Code("000"), InsertedCode(""), state(tsVendingMachine), Char(' '), AnimationFrame(0)
{

}

Transition::~Transition()
{
	
}

void Transition::Update(TransitionState tstate) 
{
	if (tstate==tsHole) {
		AnimationFrame++;
		if (AnimationFrame>100) {
			InsertedCode = "";
		}
	}
	state = tstate;
}

void Transition::CheckMouseInput() 
{
	if (state == tsMouseBuyButton)
		state = tsNumberPad;
	if ((state == tsNumberPad) && (Char!=' '))
		InsertedCode += Char;
}

void Transition::CheckMousePosition(int x, int y, int width, int height)
{	
	if ((x>(width * 0.7)) && (y<height*0.3) && (state == tsVendingMachine))  
		state = tsMouseBuyButton;
 	if (state == tsMouseBuyButton)
		//glutSetCursor(GLUT_CURSOR_CYCLE); //this doesn't work at my computer?
		glutSetCursor(GLUT_CURSOR_INFO);
	else 
	{
		bool mouse = (x>(width * 0.7)) && (y<height*0.3);
		glutSetCursor(0);
		
		if (state == tsNumberPad) {
			if ((x>(width*0.64)) && (x<(width*0.67))) {
				if ((y>height*0.08) && (y<height*0.16)) Char = 'A';
				else if ((y>height*0.19) && (y<height*0.27)) Char = 'D';
				else if ((y>height*0.31) && (y<height*0.38)) Char = 'C';
				else if ((y>height*0.42) && (y<height*0.49)) Char = '1';
				else if ((y>height*0.54) && (y<height*0.62)) Char = '4';
				else if ((y>height*0.65) && (y<height*0.73)) Char = '7';
				else if ((y>height*0.78) && (y<height*0.85)) Char = '*';
				else Char = ' ';
			}
			//2nd row 
			else if ((x>(width*0.70)) && (x<(width*0.73))) {
				if ((y>height*0.08) && (y<height*0.16)) Char = 'B';
				else if ((y>height*0.19) && (y<height*0.27)) Char = 'E';
				else if ((y>height*0.31) && (y<height*0.39)) Char = 'H';
				else if ((y>height*0.44) && (y<height*0.52)) Char = '2';
				else if ((y>height*0.56) && (y<height*0.64)) Char = '5';
				else if ((y>height*0.69) && (y<height*0.77)) Char = '8';
				else if ((y>height*0.81) && (y<height*0.90)) Char = '0';
				else Char = ' ';
			}
			//3rd row
			else if ((x>(width*0.76)) && (x<(width*0.81))) {
				if ((y>height*0.08) && (y<height*0.16)) Char = 'C';
				else if ((y>height*0.19) && (y<height*0.28)) Char = 'F';
				else if ((y>height*0.31) && (y<height*0.41)) Char = 'J';
				else if ((y>height*0.46) && (y<height*0.54)) Char = '3';
				else if ((y>height*0.59) && (y<height*0.69)) Char = '6';
				else if ((y>height*0.72) && (y<height*0.81)) Char = '9';
				else if ((y>height*0.84) && (y<height*0.95)) Char = '#';
				else Char = ' ';
			}
			else Char = ' ';
			
			if (Char!=' ') 
				glutSetCursor(GLUT_CURSOR_CYCLE);
			else 
				glutSetCursor(0);  
		}
	}	  
}

bool Transition::IsRightCode() { 
	return InsertedCode == Code;
} 

bool Transition::IsPlayMechanicSound() { 
	return AnimationFrame==0;
} 
