//  @ Project : QPT 1 - pacmet
//  @ File Name : DrawManager.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#pragma once

#include <string>

// Implementiert viele n�tzliche Funktionen zum Zeichnen von Grafiken und Texten, 
// sowie allgemeine statische Variablen f�r die Standard Font und Color von z. B. dem Men�, Steht BasisView als Instanz zur Verf�gung

class Element;
class DrawManager {
private:			

public:		
	DrawManager();	
	~DrawManager();
	//void drawPicture(GameImages image, ci::Vec2f &vect);
	//void drawPicture(GameImages image, ci::Rectf &rect);
	//void drawText(std::string txt, ci::Vec2f& pos, bool UseStdFont);
	/*void drawText(std::string txt, ci::Vec2f& pos, ci::Font* font);
	void drawText(std::string txt, ci::Vec2f& pos, ci::Font* font, bool UseWhite);
	void drawSpite(Element* element, int row = 1, int col = 1);
	void stretchViewport();

	ci::Font* getStdFont();
	ci::Font* getBigFont();
	ci::Font* getMenueFont();
	ci::Color* getStdColor();
	ci::Color* getWhite();*/
};
