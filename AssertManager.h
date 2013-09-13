//  @ Project : QPT 1 - pacmet
//  @ File Name : AssertManager.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//  
//

// Dieses Singelton-Pattern Verwaltet die Images in einer Liste vom Typ GameImage
// Sie dient dazu, das Laden von den Images während des Games zu verhindern
// Die Liste des AssertManagers und somit die Bilder werden bei Programmstart geladen, somit ergeben sich keine / kaum Verzögerungen beim "Laden" eines neues Bildes

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
	//ci::gl::Texture getimage(GameImages images);
	//int getrow(GameImages images);
	//int getcol(GameImages images);
};
