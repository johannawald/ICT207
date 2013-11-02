 #include "ControlRoom.h"
#include "StateMachine.h"
#include "ModelLoader.h"
#include "GameController.h"
#include "GameControllerLevelOne.h"

//--------------------------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------------------------
ControlRoom::ControlRoom(AudioManager* am, ModelManager* mm, TextureManager* tm): 
	GameController(am,mm,tm), mShowConsoleScreen(true)
{
}

void ControlRoom::DrawObjects()
{	
	glPopMatrix();
		if (mShowConsoleScreen)
			DrawConsoleScreen(1024.0, 768.0, 0.0, 0.0, 0.0, 1.0, 1.0, false);
		DrawTimer();
	glPopMatrix();
}

void ControlRoom::InitGameObjects()
{	
	addCollisionGameObject(Vector3D(100, GetGroundLevel(), 450), Vector3D(), Vector3D(80,300,50), Vector3D(0.15,0.3,0.3), Vector3D(), mLadder, taRustyWall, 1, 1, mIndexLadder);
	InitWalls();	
	InitFloor();	
}

void ControlRoom::BeforeCollision(int pIndex, float pCollisionValue)
{	
	GameController::BeforeCollision(pIndex, pCollisionValue);
	if (ObjectIsLadder(pIndex))
		StateMachine::setBushCourtController();
	else if (ObjectIsConsole(pIndex))
		StateMachine::setController(new GameControllerLevelOne(GetAudio(), GetModel(), GetTexture()));
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
}

void ControlRoom::InitFloor()
{
	//floor
	/*GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 2, Vector3D(-4000, 0, -6000), Vector3D(8000, 12000, 0));
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 1, 1, Vector3D(-2000, 0, -8000), Vector3D(4000, 2000, 0));
	//roof
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 3, 2, Vector3D(-4000, 4000, -6000), Vector3D(8000, 12000, 0));
	GetDrawManager()->DrawCollisionRect(&mCollision, GetTexture()->getTextureID(taTilefloor), 1, 1, Vector3D(-2000, 4000, -8000), Vector3D(4000, 2000, 0));
*/
}

void ControlRoom::InitWalls()
{
	int test = 0;
	addCollisionGameObject(Vector3D(-400, GetGroundLevel(), 600), Vector3D(), Vector3D(800, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 4, 1, test);
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), -600), Vector3D(), Vector3D(200, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(-400, GetGroundLevel(), -600), Vector3D(), Vector3D(200, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(),-800), Vector3D(), Vector3D(400, 0, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 2, 1, test);

	addCollisionGameObject(Vector3D(-400, GetGroundLevel(),-600), Vector3D(), Vector3D(0, 1200, 400), Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 6, 1, test);
	addCollisionGameObject(Vector3D(400, GetGroundLevel(),-600), Vector3D(), Vector3D(0, 1200, 400),Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 6, 1, test);
	addCollisionGameObject(Vector3D(-200, GetGroundLevel(),-800), Vector3D(), Vector3D(0, 200, 400),Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
	addCollisionGameObject(Vector3D(200, GetGroundLevel(), -800), Vector3D(), Vector3D(0, 200, 400),Vector3D(), Vector3D(), -1, GetTexture()->getTextureID(taTilewall), 1, 1, test);
}

/*void ControlRoom::DrawStairs()
{
	glBindTexture(GL_TEXTURE_2D, GetTexture()->getTextureID(taTilefloor));
	glPushMatrix();
		glTranslatef(2000, 0, -6000);
		glRotatef(180, 0, 1, 0);
		GetDrawManager()->DrawStairs(4000, 1000, 2000, 5);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, -1);
}

void ControlRoom::DrawConsole()
{
	glPushMatrix();
		//glTranslatef(1000, 0, 4500);
		glRotatef(180, 0, 1, 0);
		//glScalef(2, 2, 2);
		//GetModel()->drawModel(mConsole, GetTexture()->getTextureID(taConsole));
		//addCollisionGameObject(Vector3D(1000, 0, 4500), Vector3D(), Vector3D(100,100,100), Vector3D(1.5,3,3), Vector3D(), mLadder, taRustyWall, 1, 1, mIndexLadder);
		
	glPopMatrix();
}

void ControlRoom::DrawLadder()
{
	glPushMatrix();
		//glTranslatef(-500, 0, -6750);
		//glScalef(1.5, 3, 3);	
		//addCollisionGameObject(Vector3D(-500, 0, -6750), Vector3D(), Vector3D(100,100,100), Vector3D(1.5,3,3), Vector3D(), mLadder, taRustyWall, 1, 1, mIndexLadder);
		//GetModel()->drawModel(mLadder, GetTexture()->getTextureID(taRustyWall));
	glPopMatrix();
}*/

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