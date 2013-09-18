//  @ File Name : DrawManager.h
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet


#pragma once

#include <string>
#include <windows.h>

// Implements a lot of different draw functions like to draw text, staris ...

class DrawManager {
private:			

public:		
	DrawManager();	
	~DrawManager();
	void RenderString(float x, float y, void *font, const char* str);

	void drawStairs(float stairWidth, float stairHeight, float stairDepth, float numSteps);
};
