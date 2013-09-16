//  @ Unit : ICT207
//  @ File Name : AssertManager.h
//  @ Author : Johanna Wald
//
//

// This Singelton manages the states


#pragma once

class Image;
class images;
class GameImage;
class AssertManager {
private:
	static AssertManager* assertmanager;
	GameImage* List[19]; 
	AssertManager();
	void clear();	
public:		
	static AssertManager* getInstance();	
	~AssertManager();		
	void init();
	void realoadimages();
};
