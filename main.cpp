/**
 * @main.cpp
 * @brief Encapsulates Shay's World (Campus Tour)
 *
 * Encapsulates Shays World (Campus Tour) / turning it into its
 * own class (BushCourtController) and using a State Machine
 *
 * @author Shay Leary - Original, March 2005
 * @author Johanna Wald - Encapsulation as Class / Implementing a State Machine, 01/09/2013
 * @version 01
 * @date 01/03/2005 Shay Leary - Original
 * @date 14/09/2013 Johanna Wald
 */

#include <GL/glut.h>
#include "StateMachine.h" 


//--------------------------------------------------------------------------------------
//  glut events 
//--------------------------------------------------------------------------------------
void SpecialKey(int key, int x, int y);
void SpecialKeyUp(int key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Display();
void Mouse(int button, int state, int x, int y);
void PassiveMotion(int x, int y);
void Reshape(int w, int h);

//--------------------------------------------------------------------------------------
//  Main function 
//--------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("Murdoch University Campus Tour");
	//initialize the State of the StateMachine (Bush court is set as the first state)
	StateMachine::getInstance();
	//call initialize function of the state the StateMachine is storing
	StateMachine::getInstance()->Init();
	//set glut events:
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutKeyboardUpFunc(KeyboardUp);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(PassiveMotion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return(0);
}

//--------------------------------------------------------------------------------------
//  glut events 
//--------------------------------------------------------------------------------------

void SpecialKey(int key, int x, int y)
{
	StateMachine::getInstance()->SpecialKey(key,x,y);
}

void SpecialKeyUp(int key, int x, int y)
{
	StateMachine::getInstance()->SpecialKeyUp(key,x,y);
}

void KeyboardUp(unsigned char key, int x, int y) 
{
	StateMachine::getInstance()->KeyboardUp(key,x,y);
}

void Keyboard(unsigned char key, int x, int y)
{
	StateMachine::getInstance()->Keyboard(key,x,y);
}

void Display() 
{
	StateMachine::getInstance()->Update();
	StateMachine::getInstance()->Draw();
}

void Mouse(int button, int state, int x, int y) 
{
	StateMachine::getInstance()->Mouse(button, state, x, y);
}

void PassiveMotion(int x, int y)
{
	StateMachine::getInstance()->PassiveMotion(x, y);
}

void Reshape(int w, int h) 
{
	StateMachine::getInstance()->Reshape(w,h);
}
