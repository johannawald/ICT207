//  Transition.cpp

#include "Transition.h"
#include <GL/glut.h>

Transition::Transition(): Code("000"), state(tsNone), DisplayVendingMachine(false), Number(""), MouseRightSideScreen(false), Char(' '), FallAnimation(false), DisplayBuySweets(false), waited_frames(0), DisplaySecretStairs(false)
{

}

Transition::~Transition()
{
	
}

ReachtTransition Transition::Update() 
{
	return Move;
}

void Transition::CheckMouseInput() 
{
	if (MouseRightSideScreen) {
		DisplayVendingMachine = true;
		DisplayBuySweets = false;
	}
	//if ((transition.state == tsVendingMachine) && (transition.Char!=' ')) {
	if (DisplayVendingMachine && (Char!=' ')) {
		Number =+ Char;
	}
}

void Transition::CheckMousePosition(int x, int y, int width, int height)
{	
	MouseRightSideScreen = (x>(width * 0.7)) && (y<height*0.3);
	//if (transition.state = tsVendingMachine) {
	if (DisplayBuySweets) {
		if (MouseRightSideScreen) // && (y>100) && (x<600) && (y<200))
			glutSetCursor(GLUT_CURSOR_CYCLE); //GLUT_CURSOR_SPRAY);
		else 
			glutSetCursor(0);
	}
	//else if (transition.state == tsVendingMachine) {
	else if (DisplayVendingMachine) {			
		//1st row:
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
