//  @ Project : QPT 1 - pacmet
//  @ File Name : BasisModel.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

#pragma once

// Allgemeine, abstrakte Model-Klasse für das MVC-Pattern

class BasisModel {
public:
	virtual void init() = 0;
	virtual void update() = 0;
};

