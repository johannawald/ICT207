#include <GL/glut.h>
#include "StateMachine.h" 

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

void Draw() 
{
	StateMachine::getInstance()->Draw();
}

void Mouse(int button, int state, int x, int y) 
{
	StateMachine::getInstance()->Mouse(button, state, x, y);
}

void PassiveMotion(int x, int y)
{
	//StateMachine::getInstance()->PassiveMotion(x, y);
}

void Update(int w, int h) 
{
	StateMachine::getInstance()->Update(w,h);
}

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

	StateMachine::getInstance();
	StateMachine::getInstance()->Init();
	
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutKeyboardUpFunc(KeyboardUp);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Draw);
	glutIdleFunc(Draw);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(PassiveMotion);
	glutReshapeFunc(Update);
	glutMainLoop();
	return(0);
}

/*
void CheckNumberpad() { //*JW
	//*JW 24500
	//cam.GetLR() ist groß desto weiter man links ist 34400 -> 34300 -> 34700 -> 34900 -> 35200 (näher an vending machine) -> 35400 -> 35500 -> 35300
	transition.Update();
	if (transition.Number == "000") { //42 4F 4D 42 = B O M B
		if (transition.waited_frames==0) 
			cam.PlayMechanicSound();
		cam.DirectionFB(-1);

		transition.waited_frames++;
		if (transition.waited_frames>100) {
			
			transition.Number = "";
			//(transition.state = tsHole;
			transition.DisplaySecretStairs = true;
			transition.DisplayBuySweets = false;
			transition.DisplayVendingMachine = false;
			//transition.state = tsHole;
		}
	}
	//if (!(transition.state = tsHole, (transition.state = tsVendingMachine)
	if (!(transition.DisplaySecretStairs || transition.DisplayVendingMachine))
		transition.DisplayBuySweets = ((cam.GetFB() > 24500) && (cam.GetFB() < 25300) && (cam.GetLR() < 35000) /*border links - desto größer desto weiter links*/ // && (cam.GetLR() > 34759));
	/*else 
		transition.FallAnimation = (cam.GetFB() > 24900) && (cam.GetFB() < 25200) && (cam.GetLR() < 35200);
	
	if (transition.FallAnimation) { 
		cam.DirectionUD(-1); 
		cam.DirectionRotateLR(2); 
		//cam.DirectionLookUD(5);
	}
}

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------
void Display()
{
	// check for movement
	cam.CheckCamera();
	CheckNumberpad(); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// DISPLAY TEXTURES
	//enable texture mapping
	glEnable (GL_TEXTURE_2D);
	glPushMatrix();	
		// displays the welcome screen
		if (DisplayWelcome) cam.DisplayWelcomeScreen (width, height, 1, tp.GetTexture(WELCOME));	
		// displays the game entry screen / numberpad
		//*JW
		//if (transition.state == tsVendingMachine)
		if (transition.DisplayBuySweets) cam.DisplayGameEntryScreen(width, height, 1, tp.GetTexture(VENDING_MACHINE)); //*JW
		if (transition.DisplayVendingMachine) {
			if (transition.waited_frames==0)
				cam.DisplayGameEntryScreen(width, height, 1, tp.GetTexture(NUMBERPAD)); //*JW
			else 
				cam.DisplayGameEntryScreen(width, height, 1, 0); //*JW
		}
		//e*JW
		// displays the exit screen
 		if (DisplayExit) cam.DisplayWelcomeScreen (width, height, 0, tp.GetTexture(EXIT) );
		// displays the map
		if (DisplayMap) cam.DisplayMap(width, height, tp.GetTexture(MAP));
		// display no exit sign (position check should really be in an object, but didn't have time)
		if ((cam.GetLR() > 35500.0) && (cam.GetFB() < 25344.0) ||
			(cam.GetLR() > 34100.0) && (cam.GetFB() > 41127.0))
		{
			cam.DisplayNoExit(width, height,tp.GetTexture(NO_EXIT));
		}
				// set the movement and rotation speed according to frame count
		IncrementFrameCount();
		cam.SetMoveSpeed (stepIncrement);
		cam.SetRotateSpeed (angleIncrement);
		// display images
		DrawBackdrop();
	glPopMatrix();
	glDisable (GL_TEXTURE_2D); 

	// clear buffers
	glFlush();
	glutSwapBuffers();
}

//--------------------------------------------------------------------------------------
void keys(unsigned char key, int x, int y)
{
	int i = 0;
	switch (key)
	{
		
		//*JW
		case 8: {
			transition.Number = ""; //debug setting 
			break;
		}
		//e*JW
		/* default: 
		{
			if (DisplayBuySweets && (key > 47) && (key < 58)) {
				TelefonNumber += key;
			}
			break;
		}
	}
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	// exit tour if clicked on exit splash screenH
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		//*JW
		if (transition.MouseRightSideScreen) {
			//transition.state = tsVendingMachine;
			transition.DisplayVendingMachine = true;
			transition.DisplayBuySweets = false;
		}
		//if ((transition.state == tsVendingMachine) && (transition.Char!=' ')) {
		if (transition.DisplayVendingMachine && (transition.Char!=' ')) {
			transition.Number = transition.Number + transition.Char;
		}
		//e*JW
		if ((DisplayExit) && (x <= width/2.0 + 256.0) && (x >= width/2.0 - 256.0)
			&& (y <= height/2.0 + 256.0) && (y >= height/2.0 - 256.0))
		{
			DeleteImageFromMemory(image);
			exit(1);
		}
  	 }
}

//--------------------------------------------------------------------------------------
//  Mouse Movements (NOT USED)
//  Can be used to rotate around screen using mouse, but keyboard used instead
//--------------------------------------------------------------------------------------
void mouseMove(int x, int y)
{
		//*JW
		// 
		transition.MouseRightSideScreen = (x>(width * 0.7)) && (y<height*0.3);
		//if (transition.state = tsVendingMachine) {
		if (transition.DisplayBuySweets) {
			if (transition.MouseRightSideScreen) // && (y>100) && (x<600) && (y<200))
				glutSetCursor(GLUT_CURSOR_CYCLE); //GLUT_CURSOR_SPRAY);
			else 
				glutSetCursor(0);
		}
		//else if (transition.state == tsVendingMachine) {
		else if (transition.DisplayVendingMachine) {
			
			//1st row:
			if ((x>(width*0.64)) && (x<(width*0.67))) {
				if ((y>height*0.08) && (y<height*0.16)) transition.Char = 'A';
				else if ((y>height*0.19) && (y<height*0.27)) transition.Char = 'D';
				else if ((y>height*0.31) && (y<height*0.38)) transition.Char = 'C';
				else if ((y>height*0.42) && (y<height*0.49)) transition.Char = '1';
				else if ((y>height*0.54) && (y<height*0.62)) transition.Char = '4';
				else if ((y>height*0.65) && (y<height*0.73)) transition.Char = '7';
				else if ((y>height*0.78) && (y<height*0.85)) transition.Char = '*';
				else transition.Char = ' ';
			}
			//2nd row 
			else if ((x>(width*0.70)) && (x<(width*0.73))) {
				if ((y>height*0.08) && (y<height*0.16)) transition.Char = 'B';
				else if ((y>height*0.19) && (y<height*0.27)) transition.Char = 'E';
				else if ((y>height*0.31) && (y<height*0.39)) transition.Char = 'H';
				else if ((y>height*0.44) && (y<height*0.52)) transition.Char = '2';
				else if ((y>height*0.56) && (y<height*0.64)) transition.Char = '5';
				else if ((y>height*0.69) && (y<height*0.77)) transition.Char = '8';
				else if ((y>height*0.81) && (y<height*0.90)) transition.Char = '0';
				else transition.Char = ' ';
			}
			//3rd row
			else if ((x>(width*0.76)) && (x<(width*0.81))) {
				if ((y>height*0.08) && (y<height*0.16)) transition.Char = 'C';
				else if ((y>height*0.19) && (y<height*0.28)) transition.Char = 'F';
				else if ((y>height*0.31) && (y<height*0.41)) transition.Char = 'J';
				else if ((y>height*0.46) && (y<height*0.54)) transition.Char = '3';
				else if ((y>height*0.59) && (y<height*0.69)) transition.Char = '6';
				else if ((y>height*0.72) && (y<height*0.81)) transition.Char = '9';
				else if ((y>height*0.84) && (y<height*0.95)) transition.Char = '#';
				else transition.Char = ' ';
			}
			else transition.Char = ' ';

			if (transition.Char!=' ') 
				glutSetCursor(GLUT_CURSOR_CYCLE);
			else 
				glutSetCursor(0);
		}

	    //e*JW
		/*if (x < 0)
			cam.DirectionRotateLR(0);
		else if (x > width)
			cam.DirectionRotateLR(0);
		else if (x > width/2.0)
		{
			cam.DirectionRotateLR(1);
			Display();
			glutWarpPointer(width/2.0,height/2.0);
		}
		else if (x < width/2.0)
		{
			cam.DirectionRotateLR(-1);
			Display();
			glutWarpPointer(width/2.0,height/2.0);
		}
		else
			cam.DirectionRotateLR(0);
		if (y < 0 || y > height)
			cam.DirectionLookUD(0);

		else if (y > height/2.0) {
			cam.DirectionLookUD(-1);
			Display();
			glutWarpPointer(width/2.0,height/2.0);
		}
		else if (y < height/2.0) {
			cam.DirectionLookUD(1);
			Display();
			glutWarpPointer(width/2.0,height/2.0);
		}
		else
			cam.DirectionLookUD(0);*/
/*}

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
void CreateBoundingBoxes()
{
...

	// phy sci block 3rd panel
	cam.SetAABBMaxX(6, 35879.0);
	cam.SetAABBMinX(6, 33808.0);
	cam.SetAABBMaxZ(6, 41127.0);
	cam.SetAABBMinZ(6, 37855.0);

	// drinks machine
	cam.SetAABBMaxX(7, 35879.0);
	//*JW
	//if (DisplaySecretStairs) 
		cam.SetAABBMinX(7, 35004.0);
	//else 
	//	cam.SetAABBMinX(7, 34704.0);
	//e*JW
	cam.SetAABBMaxZ(7, 25344.0);
	cam.SetAABBMinZ(7, 24996.0);
	
	// bottom of steps
	cam.SetAABBMaxX(8, 33808.0);
	cam.SetAABBMinX(8, 0.0);
	cam.SetAABBMaxZ(8, 4688.0);
	cam.SetAABBMinZ(8, 0.0);

}

//--------------------------------------------------------------------------------------
// Load and Create Textures
//--------------------------------------------------------------------------------------
void CreateTextures()
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// set texture count
	tp.SetTextureCount(251); //*JW

	// load and create textures
	image = tp.LoadTexture("data/abovechanctext.raw", 128, 1024);
	tp.CreateTexture(ABOVE_CHANC_TEXT, image, 128, 1024);

	...

	image = tp.LoadTexture("data/sweetMachine.raw", 256, 256);
	tp.CreateTexture(SWEET_MACHINE, image, 256, 256);

	//*JW
	image = tp.LoadTexture("data/check.raw", 1280, 720);
	tp.CreateTexture(BANNER, image, 1280, 720);
	//e*JW

	image = tp.LoadTexture("data/telephoneback.raw", 512, 512);
	tp.CreateTexture(TELEPHONE_BACK, image, 512, 512);

	...

	image = tp.LoadTexture("data/thanks.raw", 512, 512);
	tp.CreateTexture(EXIT, image, 512, 512);

	//*JW
	image = tp.LoadTexture("data/numberpad.raw", 850, 525);
	tp.CreateTexture(NUMBERPAD, image, 850, 525); //letztes ist höhe, vorderes ist breite

	image = tp.LoadTexture("data/vending_machine.raw", 595, 356);
	tp.CreateTexture(VENDING_MACHINE, image, 595, 356); //letztes ist höhe, vorderes ist breite
	//e*JW 

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}
	
void DrawAboveWindowBlock ()
{

//--------------------------------------------------------------------------------------
//  Display Pavement
//--------------------------------------------------------------------------------------
void DisplayPavement ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	for (int i = 72; i < 74; i ++) glCallList(i);
	glCallList(28);
	glCallList(828); //*JW
	glCallList(928); //*JW
	for (int i = 81; i < 89; i ++) glCallList(i);
	...
}

void DrawPavement ()
{
	...

	// PAVEMENTSIDE_LEFT
	tp.CreateDisplayList (XZ, 75,  64.0, 64.0, 31568.0, 10000.0, 10096.0, 1.0, 480.0);
	tp.CreateDisplayList (XZ, 436,  64.0, 64.0, 31568.0, 9086.0, 3408.0, 1.0, 45.0);	// Side paving at entrance
	// PAVEMENTSIDE_RIGHT
	tp.CreateDisplayList (XZ, 76,  64.0, 64.0, 4784.0, 10000.0, 10000.0, 1.0, 481.5);
	// PAVEMENTSIDE_TOP
	tp.CreateDisplayList (XZ, 77,  64.0, 64.0, 4848.0, 10000.0, 40816.0, 417.5, 1.0);
	// PAVEMENT_STEPS_CORNER					
	tp.CreateDisplayList (XZ, 78,  128.0, 64.0, 32568, 10000.0, 10000.0, 1.0, 1.5);   // corner above chanc steps
	tp.CreateDisplayList (XZ, 80,  32.0, 64.0, 31568.0, 10000.0, 9950.0, 70.0, 0.797);  // strip along top of chanc steps
	//hole under the sweets machine!
	//*JW!! 
	//10000 is the y-position of the ground, 35100 der start von links desto größer, desto weiter links, 24896 weg vom gehen
	tp.CreateDisplayList (XZ, 28, 128.0, 64.0,  33744.0, 10000.0, 21696.0, 17.2, 52.0); // between chanc and phy sci
	tp.CreateDisplayList (XZ, 928, 128.0, 64.0,  33760, 10000.0, 24956, 8, 10); // between chanc and phy sci
	tp.CreateDisplayList (XZ, 828, 128.0, 64.0,  35020, 10000.0, 24956, 8, 10); // between chanc and phy sc
	//e*JW
	tp.CreateDisplayList (XZ, 248, 128.0, 64.0,  33744.0, 10000.0, 10449.0, 1.5, 16.0); // doorway to chanc
	tp.CreateDisplayList (XZ, 247, 128.0, 64.0,  33744.0, 10000.0, 39185.0, 1.5, 23.0); // doorway to red posts
	tp.CreateDisplayList (XZ, 249, 128.0, 64.0, 31632.0, 9086.0, 3408.0, 18.0, 45.0);	//entry (bottom of steps)
	tp.CreateDisplayList (XZ, 81, 128.0, 64.0,  33744.0, 10000.0, 26704.0, 2.5, 11.0);	//phys sci doorway 1
	
	tp.CreateDisplayList (XZ, 82, 128.0, 64.0,  33744.0, 10000.0, 27344.0, 4.5, 3.5);	//phys sci doorway 1
	tp.CreateDisplayList (XZ, 83, 128.0, 64.0,  33744.0, 10000.0, 36304.0, 5.0, 5.3);	//phys sci doorway 2
	tp.CreateDisplayList (XZ, 84, 128.0, 64.0,  33744.0, 10000.0, 36624.0, 2.5, 9.0);	//phys sci doorway 2
	tp.CreateDisplayList (XZ, 85, 128.0, 64.0,  33744.0, 10000.0, 37200.0, 5.0, 10.5);	//phys sci doorway 2
	tp.CreateDisplayList (XZ, 86, 128.0, 64.0,  33744.0, 10000.0, 28624.0, 2.5, 13.5);	//phys sci toilet doorways
}

//--------------------------------------------------------------------------------------
// Display Extras (signs etc)
//--------------------------------------------------------------------------------------
void DisplayExtras ()
{
	...
		glCallList(321);
	glPopMatrix();
	glCallList(320);
	glPushMatrix();
		glTranslatef(255.0, 0.0, 0.0);
		glCallList(322);
	glPopMatrix();

	//*JW!
	if (!transition.DisplaySecretStairs) {
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SWEET_MACHINE)); //*JW
		const GLdouble SweetMachine_zStart = 25016;
		const GLdouble SweetMachine_xStart = 34778; 
		const GLdouble SweetMachine_xSize = 250.0;
		const GLdouble SweetMachine_yStart = 10000.0; 
		const GLdouble SweetMachine_ySize = 593.22;
		const GLdouble SweetMachine_xImgSize = 0.59; 
		const GLdouble SweetMachine_yImgSize = 1.0;
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(SweetMachine_xStart, SweetMachine_yStart, SweetMachine_zStart);
			glTexCoord2f(SweetMachine_xImgSize, 0.0);
			glVertex3f(SweetMachine_xStart + SweetMachine_xSize, SweetMachine_yStart, SweetMachine_zStart);
			glTexCoord2f(SweetMachine_xImgSize, SweetMachine_yImgSize);
			glVertex3f(SweetMachine_xStart + SweetMachine_xSize, SweetMachine_yStart + SweetMachine_ySize, SweetMachine_zStart);
			glTexCoord2f(0.0, SweetMachine_yImgSize);
			glVertex3f(SweetMachine_xStart, SweetMachine_yStart + SweetMachine_ySize, SweetMachine_zStart);	
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0); //*JW
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES_2));
		glCallList(323);
		glPushMatrix();
			glTranslatef(250.0, 0.0, 0.0); //*JW correction
			glCallList(323);
		glPopMatrix();
	}
	//e*JW

	// Doorway Carpet
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
	...
}

void DrawExtras ()
{

	tp.CreateDisplayList (XY, 315, 256.0, 128.0, 33660.0, 10836.0, 20113.0, 0.578, 0.561);	// PSC sign

	tp.CreateDisplayList (YZ, 316, 256.0, 128.0, 33808.0, 10256.0, 34126.0, 1.0, 1.0);		// CO sign

	tp.CreateDisplayList (YZ, 317, 64.0, 64.0, 35856.0, 10000.0, 24996.0, 11.5, 5.47);		// Drinks Machine
	tp.CreateDisplayList (XY, 319, 64.0, 64.0, 34704.0, 10672.0, 24996.0, 18.0, 1.0);		// Drinks Machine
	tp.CreateDisplayList (XZ, 318, 64.0, 64.0, 34704.0, 10736.0, 24996.0, 18.0, 5.5);		// Drinks Machine
	tp.CreateDisplayList (XY, 320, 16.0, 2.0, 35840.0, 10000.0, 24996.0, 1.0, 336.0);		// Drinks Machine
	tp.CreateDisplayList (YZ, 321, 1.0, 1.0, 35458.0, 10000.0, 25016.0, 660.0, 300.0);		// Drinks Machine Sides
	tp.CreateDisplayList (YZ, 322, 1.0, 1.0, 35163.0, 10000.0, 25016.0, 586.2, 300.0);		// Drinks Machine Sides
	tp.CreateDisplayList (YZ, 323, 1.0, 1.0, 34778.0, 10000.0, 25016.0, 593.22, 300.0);		// Sweets Machine Sides //*JW

}

// --------------------------------------------------------------------------------------
// Display larger textures such as windows and doors
// --------------------------------------------------------------------------------------

void DisplayLargerTextures ()
{
	...

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COKE_MACHINE));
	glCallList(370);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COFFEE_MACHINE));
	glCallList(371);
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SWEET_MACHINE)); //*JW
	//glCallList(372); //*JW

	// Phys sci door 1
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_13));
	glCallList(373);
}

//--------------------------------------------------------------------------------------
//  Map and Welcome screens
//--------------------------------------------------------------------------------------
void DrawMapExit ()
{
	tp.CreateDisplayList (0, 448, 256.0, 256.0, 10.0, 10.0, 0.0, 0.855, 1.0); // map
	tp.CreateDisplayList (0, 449, 512.0, 512.0, 0.0, 0.0, 0.0, 1.0, 1.0);	  // welcome screen
	tp.CreateDisplayList (0, 454, 256.0, 64.0, 0.0, 0.0, 0.0, 1.0, 1.0);	  // welcome screen

	tp.CreateDisplayList (0, 4000, 792, 492, 0.0, 0.0, 0.0, 1.0, 1.0);	  // whole image //*JW
}

}*/