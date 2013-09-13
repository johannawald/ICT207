//  @ Project : QPT 1 - pacmet
//  @ File Name : AssertManager.cpp
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#include "AssertManager.h"

AssertManager* AssertManager::assertmanager = nullptr;

AssertManager::AssertManager() {
}

void AssertManager::clear() {
	for (int i = 0; i <= 15; i++)
		delete List[i];
}

AssertManager* AssertManager::getInstance() {	
	if(AssertManager::assertmanager==nullptr)
    {
        assertmanager = new AssertManager();        
        return assertmanager;
    }
    else return assertmanager;
}

AssertManager::~AssertManager() {	
	clear();
}

/*ci::gl::Texture AssertManager::getimage(GameImages images) {
	return List[images]->image;
}

int AssertManager::getrow(GameImages images) {
	return List[images]->row;
}

int AssertManager::getcol(GameImages images) {
	return List[images]->col;
}*/

void AssertManager::init() {	
	//Verschiedene Elemente:
	/*List[imgPoint] = new GameImage(loadImage(ci::app::loadAsset("point.png")),0,0);
	List[imgPacman] = new GameImage(loadImage(ci::app::loadAsset("pacman.png")),7,3);
	List[imgGhostBlue] = new GameImage(loadImage(ci::app::loadAsset("GhostBlue.png")),0,0);
	List[imgGhostGreen] = new GameImage(loadImage(ci::app::loadAsset("GhostGreen.png")),0,0);
	List[imgGhostPurple] = new GameImage(loadImage(ci::app::loadAsset("GhostPurple.png")),0,0);
	List[imgGhostFollow] = new GameImage(loadImage(ci::app::loadAsset("GhostPurple.png")),0,0);
	List[imgCherry] = new GameImage(loadImage(ci::app::loadAsset("Cherry.png")),0,0);
	List[imgStrawberry] = new GameImage(loadImage(ci::app::loadAsset("Strawberry.png")),0,0);
	List[imgFireBall] = new GameImage(loadImage(ci::app::loadAsset("fireball.png")),0,0);	
	List[imgFireFlower] = new GameImage(loadImage(ci::app::loadAsset("FireFlower.png")),0,0);	
	List[imgCannonBall] = new GameImage(loadImage(ci::app::loadAsset("Canone.png")),0,0);	
	//Hintergründe:
	List[imgStartMenue] = new GameImage(loadImage(ci::app::loadAsset("Menue.png")),1,1);		
	List[imgGameOverMenue] = new GameImage(loadImage(ci::app::loadAsset("GameOver.png")),1,1);
	List[imgGamePlayBG] = new GameImage(loadImage(ci::app::loadAsset("GamePlay.png")),1,1);
	List[imgGameBG] = new GameImage(loadImage(ci::app::loadAsset("GamePlay.png")),1,1);
	List[imgGamePlayBGSingle] = new GameImage(loadImage(ci::app::loadAsset("GamePlaySingle.png")),1,1);
	List[imgYouLost] = new GameImage(loadImage(ci::app::loadAsset("YouLost.png")),1,1);
	List[imgYouWon] = new GameImage(loadImage(ci::app::loadAsset("YouWon.png")),1,1);	
	List[imgPauseMenue] = new GameImage(loadImage(ci::app::loadAsset("PauseMenue.png")),1,1);	
	List[imgClearBG] = new GameImage(loadImage(ci::app::loadAsset("ClearBG.png")),1,1);
	List[imgTestRect] = new GameImage(loadImage(ci::app::loadAsset("TestRect.png")),1,1);*/
}

void AssertManager::realoadimages() {
	//Speicher freigeben
	clear();	
	init();
}
