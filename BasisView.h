//  @ File Name : BasisView.h
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet

//implement the stair class and some other "help"-functions here

#pragma once

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

