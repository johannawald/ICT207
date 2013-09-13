//  @ Project : QPT 1 - pacmet
//  @ File Name : DrawManager.cpp
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#include "DrawManager.h"
#include "AssertManager.h"

DrawManager::DrawManager() {	
}

DrawManager::~DrawManager() {}

/*void DrawManager::drawPicture(GameImages image, ci::Vec2f &vect) {	
	drawPicture(image, ci::Rectf((float)vect.x,(float)vect.y, (float)(vect.x+15.0), (float)(vect.y+15.0)));
}

void DrawManager::drawPicture(GameImages image, ci::Rectf &rect) {
	ci::gl::draw(AssertManager::getInstance()->getimage(image), rect);
}

void DrawManager::drawSpite(Element* element, int row, int col) {		
	float elementwidth = element->getwidth();
	float elementheight = element->getheight();

	int rows = AssertManager::getInstance()->getrow(element->getimageindex());
	int cols = AssertManager::getInstance()->getcol(element->getimageindex());
	if ((row==1) && (col==1) && (rows==0) && (cols==0))		
		ci::gl::draw(AssertManager::getInstance()->getimage(element->getimageindex()), ci::Rectf((float)(element->getpoint().x), (float)(element->getpoint().y), (float)(element->getpoint().x+elementwidth), (float)(element->getpoint().y+elementheight)));
	else {
		int border_y_snipped = (int)(element->getbordersize().y+row*(element->getbordersize().y+element->getimgsnipheight()));
		const ci::Rectf rect((float)(element->getpoint().x), (float)(element->getpoint().y), (float)(elementwidth+element->getpoint().x), (float)(elementheight+element->getpoint().y));		
		const ci::Area area((int)element->getbordersize().x, (int)border_y_snipped, (int)(element->getimgsnipwidth()+element->getbordersize().x), (int)(element->getimgsnipwidth()+border_y_snipped));
		ci::gl::draw(AssertManager::getInstance()->getimage(element->getimageindex()), area, rect);		
	}
}

void DrawManager::drawText(std::string txt, ci::Vec2f& pos, bool UseStdFont) {
	if (UseStdFont)	
		ci::gl::drawString(txt,pos, ci::Color(1.0f, 1.0f, 1.0f),*StdFont);
	else 
		ci::gl::drawString(txt,pos, ci::Color(1.0f, 1.0f, 1.0f),*BigFont);
}

void DrawManager::drawText(std::string txt, ci::Vec2f& pos, ci::Font* font) {
	ci::gl::drawString(txt,pos, ci::Color(1.0f, 1.0f, 1.0f), *font);
}

void DrawManager::drawText(std::string txt, ci::Vec2f& pos, ci::Font* font, bool UseWhite) {
	if (UseWhite) 
		ci::gl::drawString(txt,pos, *White, *font);
	else 
		ci::gl::drawString(txt,pos, *StdColor, *font);
}

ci::Font* DrawManager::getStdFont() {
	return StdFont;
}

ci::Font* DrawManager::getBigFont() {
	return BigFont;
}

ci::Font* DrawManager::getMenueFont() {
	return MenueFont;
}

ci::Color* DrawManager::getStdColor() {
	return StdColor;
}

ci::Color* DrawManager::getWhite() {
	return White;
}

void DrawManager::stretchViewport() {
	ci::gl::scale(ci::Vec2f(1,2));
}
*/