//  @ Project : QPT 1 - pacmet
//  @ File Name : BasisView.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#pragma once

// Allgemeine, abstrakte View-Klasse für das MVC-Pattern, hat einen Verweiß auf die Model des Controllers,
// Außerdem wurd die Composition des DrawManager verwendet um allgemeine Funktionen zum Zeichnen von Grafiken und Text bereitzustellen

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

