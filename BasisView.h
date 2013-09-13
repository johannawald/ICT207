//  @ Project : QPT 1 - pacmet
//  @ File Name : BasisView.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#pragma once

// Allgemeine, abstrakte View-Klasse f�r das MVC-Pattern, hat einen Verwei� auf die Model des Controllers,
// Au�erdem wurd die Composition des DrawManager verwendet um allgemeine Funktionen zum Zeichnen von Grafiken und Text bereitzustellen

#include "DrawManager.h"

class BasisModel;
class BasisView {
protected:
	BasisModel* model;
	DrawManager drawmanager;
public:	
	virtual ~BasisView() = 0 {};	
	virtual void init() {};
	virtual void draw() = 0;
};

