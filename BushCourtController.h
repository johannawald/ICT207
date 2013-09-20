/**
 * @class BushCourtController
 * @brief Encapsulates Shay's World (Campus Tour)
 *
 * Encapsulates Shays World (Campus Tour) turning it into its
 * own class.
 *
 * @author Shay Leary - Original, March 2005
 * @author Raymond Forster - Encapsulation as Class, September 2013
 * @version 01
 * @date 01/03/2005 Shay Leary - Original
 * @date 06/09/2013 Raymond Forster - started
 */

#pragma once

#include <cstdlib>
#include <math.h>
#include <GL/glut.h>
#include <time.h>

#include <windows.h> // only used if mouse is required (not portable)
#include "camera.h"
#include "texturedPolygons.h"
#include "Transition.h"
#include "IStateController.h"
#include "BasisController.h";

enum TextureImgAxises { XY, XZ, YZ, YZ_FLIP, XY_FLIP };
enum PlainTypes  { FLAT_PLAIN, XY_PLAIN, ZY_PLAIN };

class BushCourtController : public IStateController, BasisController
{
private:
	bool loaded; 
	Transition transition;

	GLdouble movementSpeed;
	GLdouble rotationSpeed;
	
	GLdouble stepIncrement;
	GLdouble angleIncrement;
	int frameCount;
	clock_t lastClock;

	unsigned char* BushCourtController::image;
	// ratio of screen
	float ratio;
	// screen width and height
	int width, height;
	// display campus map
	bool DisplayMap;
	// display welcome screen
	bool DisplayWelcome;
	// display exit screen
	bool DisplayExit;
	// display light fittings
	bool lightsOn;
	// display ECL block
	bool displayECL;
	// varibles used for tarnslating graphics etc
	GLdouble step, step2, stepLength;	
	// Glut Cylinder
	GLUquadricObj *glu_cylinder;

	Camera cam;
	TexturedPolygons tp;

	void CheckNumberPad();
public:
	BushCourtController(AudioManager* am, ModelManager* mm, TextureManager* tm);
	virtual ~BushCourtController(void);
	void SetCamPosition(GLdouble const & tempX,
				   GLdouble const & tempY,
				   GLdouble const & tempZ,
				   GLdouble const & tempAngle);

	void Init();
	void Draw();
	void Reshape();
	void Update();
	void Reshape(int w, int h);
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void PassiveMotion(int x, int y);

	//Draw Functions
	void DrawBackdrop();
	void DrawMensRoom();
	void DrawGrass ();
	void DrawChancPosts ();
	void DrawDoorPosts ();
	void DrawPurplePosts ();
	void DrawRedPosts ();
	void DrawMainPosts ();
	void DrawAboveWindowBlock ();
	void DrawDoorPaving ();
	void DrawPhysSciPosts ();
	void DrawLibraryPosts ();
	void DrawBricks ();
	void DrawPavement ();
	void DrawExtras ();
	void DrawRoof();
	void DrawEntranceSteps ();
	void DrawLargerTextures ();
	void DrawLights ();
	void DrawBench ();
	void DrawCylinders ();
	void DrawAngledRoofBeam (int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize);
	void DrawAngledRoofBeam2 (int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize);
	void DrawStepBricks ();
	void Draw2DImages(); //*JW
	void DrawECL ();
	void Draw3DModels(); //*JW
	void DrawAdPosterModels(); //*JW
	void DrawControlRoom();

	//Display Functions
	void DisplayBench ();
	void DisplayBricks ();
	void DisplayChancPosts ();
	void DisplayCylinders ();
	void DisplayDoorPaving ();
	void DisplayDoorPosts ();
	void DisplayEntranceSteps ();
	void DisplayExtras ();
	void DisplayGrass ();
	void DisplayLargerTextures ();
	void DisplayLibraryPosts ();
	void DisplayMainPosts ();
	void DisplayPavement ();
	void DisplayPhysSciPosts ();
	void DisplayPurplePosts ();
	void DisplayRedPosts ();
	void DisplayRoof();
	void DisplayStepBricks ();
	void DisplayLights ();
	void DisplayECL ();
	void DisplayAboveWindowBlock ();
	void DisplayWestExit(); //*DM
	// calls functions to create display lists (below)
	void CreateTextureList();	
	void BindBridgeWall(GLint LR);
	void BindBuildingWall();
	void BindWallPosts(GLint LR);

	void IncrementFrameCount();	
	// loads images and creates texture
	void CreateTextures();
	// creates bounding boxes for collsion detection
	void CreateBoundingBoxes();
	// creates different plains
	void CreatePlains();
	// deletes image and clears memory
	void DeleteImageFromMemory(unsigned char* tempImage);
};
