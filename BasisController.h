//  @ Project : QPT 1 - pacmet
//  @ File Name : BasisController.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

// Allgemeine, abstrakte Controller-Klasse f�r das MVC-Pattern
// bietet die allgemeine / virtuelle Funktionen f�r das Setzten der Model und der View
// alle abgeleiteten Klassen m�ssen diese implementieren und eine eigene view, 
// sowie eine eigene model besitzen, die von BasisModel und BasisView abgeleitet ist

#pragma once

class BasisView;
class BasisModel;
class BasisController {
private:
protected:
	BasisModel* model;
	BasisView* view;
	
	virtual void setModel() = 0;
	virtual void setView() = 0;
	virtual void initModel();	
	virtual void initView(BasisModel* model);
public:	
	virtual void init();
	virtual void draw() = 0;
	virtual void update() = 0;
};
