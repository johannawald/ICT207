 #include "ControlRoom.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "GameController.h"
#include "GameControllerLevelOne.h"

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
ControlRoom::ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm, float pHeight, float pWidth): 
	GameController(am,mm,tm, pHeight, pWidth), mShowConsoleScreen(true)
{
	SetLevelTime(1000);
}

void ControlRoom::DrawObjects()
{	
	glPushMatrix();
		if (mShowConsoleScreen) DrawConsoleScreen(1024.0, 768.0, 0.0, 0.0, 0.0, 1.0, 1.0, false);
		DrawStairs();
	glPopMatrix();
}

void ControlRoom::InitGameObjects()
{	
	
	addCollisionGameObject(Vector3D(-40, GetGroundLevel()+350, 750), Vector3D(), Vector3D(60,300,50), Vector3D(0.2,0.3,0.3), Vector3D(), mLadder, GetTexture()->getTextureID(taRustyWall), 1, 1, mIndexLadder);
	addCollisionGameObject(Vector3D(-40, GetGroundLevel()+65, 750), Vector3D(), Vector3D(60,300,50), Vector3D(0.2,0.3,0.3), Vector3D(), mLadder, GetTexture()->getTextureID(taRustyWall), 1, 1, mIndexLadder);
	addCollisionGameObject(Vector3D(-100, GetGroundLevel()+5, -700), Vector3D(), Vector3D(200,200,100), Vector3D(0.2,0.2,0.2), Vector3D(), mConsole,  GetTexture()->getTextureID(taConsole), 1, 1, mIndexConsole);
		
	InitWalls();
	InitFloor();
}

void ControlRoom::BeforeCollision(int pIndex, float pCollisionValue)
{	
	GameController::BeforeCollision(pIndex, pCollisionValue);
	if (ObjectIsConsole(pIndex))
	{
		std::cout << "before enter" << std::endl;
		mNextState = new GameControllerLevelOne(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth());
	}
	else if (ObjectIsLadder(pIndex))
	{	
		StateMachine::mSetBushCourt = true;
	}
}

bool ControlRoom::ObjectIsLadder(const int pIndex)
{	
	return pIndex==mIndexLadder;
}

bool ControlRoom::ObjectIsConsole(const int pIndex)
{	
	return pIndex==mIndexConsole;	
}

void ControlRoom::Keyboard(unsigned char key, int x, int y)
{
	GameController::Keyboard(key,x,y);
	if(key == ' ')
		mShowConsoleScreen = !mShowConsoleScreen;
	if(key == 'z')
		mNextState = new ControlRoom(GetAudio(), GetModel(), GetTexture(), GetWindowHeight(), GetWindowWidth());
}

void ControlRoom::InitFloor()
{
	int test = 0;
	addCollisionGameObject(Vector3D(-400, GetGroundLevel(), -600), Vector3D(), Vector3D(800, 0, 1200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilefloor), 2, 2, test); //floor
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), -800), Vector3D(), Vector3D(400, 0, 200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilefloor), 1, 0.5, test);
	//addCollisionGameObject(Vector3D(-200, GetGroundLevel(), 600), Vector3D(), Vector3D(400, 0, 200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilefloor), 1, 1, test);
	//position, movement, size, size, scale, rotation, model, texure


	//FLOOR			x,		y = 0,	z,		positive size
	//RIGHTWALL		x = 0,	y,		z,		0, +ve, +ve
	//LEFTWALL		x = 0,	y,		z,		0, +ve, -ve
	//FARWALL		x,		y = 0,		z,	+ve, +ve, 0
	//CLOSEWALL		x,		y = 0,		z,	-ve, +ve, 0
}

void ControlRoom::InitWalls()
{
	int test = 0;
	int height = 700;

	addCollisionGameObject(Vector3D(400, GetGroundLevel(), -600), Vector3D(), Vector3D(0, height, 1200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test); //rightwall
	addCollisionGameObject(Vector3D(-400, GetGroundLevel(), 600), Vector3D(), Vector3D(0, height, -1200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test); //leftwall

	addCollisionGameObject(Vector3D(-400, GetGroundLevel(), -600), Vector3D(), Vector3D(200, height, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 0.5, 1, test); //topwall
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), -600), Vector3D(), Vector3D(200, height, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 0.5, 1, test); 
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), -800), Vector3D(), Vector3D(400, height, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), -800), Vector3D(), Vector3D(0, height, 200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 0.5, 1, test);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), -600), Vector3D(), Vector3D(0, height, -200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 0.5, 1, test);

	addCollisionGameObject(Vector3D(400, GetGroundLevel(), 600), Vector3D(), Vector3D(-200, height, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test); //bottomwall
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), 600), Vector3D(), Vector3D(-200, height, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), 800), Vector3D(), Vector3D(-400, height, 0), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), 600), Vector3D(), Vector3D(0, height, 200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(), 800), Vector3D(), Vector3D(0, height, -200), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);

}

void ControlRoom::DrawStairs()
{
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glPushMatrix();
		glTranslatef(-200, -65, 600);
		GetDrawManager()->DrawStairs(400, 100, 200, 5);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, -1);
}

void  ControlRoom::DrawConsoleScreen(const GLdouble &xImgSize, const GLdouble &yImgSize, 
							         const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
							         const GLdouble &xTimes, const GLdouble &yTimes, const bool &flip)
{
	
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, GetWindowWidth(), 0, GetWindowHeight());
	glScalef(1, -1, 1);
		
	// move to centre of screen
	glTranslatef(GetWindowWidth()/2 -512.0, -GetWindowHeight()/2 -384, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taRoberConsoleSreen));

	// display image
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0.0);
		glVertex3f(xStart, yStart, zStart);
		glTexCoord2f(0, yTimes);   
		glVertex3f(xStart, yStart + (yImgSize * yTimes), zStart);
		glTexCoord2f(xTimes, yTimes);
		glVertex3f(xStart + (xImgSize * xTimes), yStart + (yImgSize * yTimes), zStart);
		glTexCoord2f(xTimes, 0.0);
		glVertex3f(xStart + (xImgSize * xTimes), yStart, zStart);
	glEnd();

	// Reset Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}