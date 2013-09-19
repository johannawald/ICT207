#include "GameController.h"
#include <GL/glut.h>
#include "StateMachine.h"
#include "BushCourtController.h"

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
GameController::GameController()
{

}

void GameController::Init() {
	int a;
}

void GameController::Draw() 
{
	glClearColor(0, 0, 0, 0);
	glColor3b(1,0,0);
	glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, 0, h, -1, 1);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // important
    glTranslatef( 0.5, 0.5, 0 );

    float offset = 40;
    glColor3ub( 255, 0, 0 );
    glBegin(GL_LINE_LOOP);
    glVertex2f( 0+offset, 0+offset );
    glVertex2f( 0+offset, h-offset );
    glVertex2f( w-offset, h-offset );
    glVertex2f( w-offset, 0+offset );
    glEnd();

    glutSwapBuffers();
}

void GameController::Update() {
}

void GameController::Reshape(int x, int y) 
{
		
}

void GameController::SpecialKey(int key, int x, int y)
{
	switch (key)
	{
		
	}
}

//---------------------------------------------------------
void GameController::SpecialKeyUp(int key, int x, int y) 
{
	switch (key)
	{

	}
}

void GameController::Keyboard(unsigned char key, int x, int y)
{
	int i = 0;
	switch (key)
	{
		// step left
		case 'e':
			StateMachine::setController(StateMachine::bushcourtcontroller);
			StateMachine::bushcourtcontroller->Init();
			break;
	}
}

//--------------------------------------------------------------------------------------
void GameController::KeyboardUp(unsigned char key, int x, int y)
{
	
}

void GameController::Mouse(int button, int state, int x, int y)
{
	
}

void GameController::PassiveMotion(int x, int y) 
{
		
}
