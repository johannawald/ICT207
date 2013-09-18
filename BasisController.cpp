//  @ File Name : BasisController.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// provides the basic functions a controller needs (game controller as well as shay's wourld)
// drawmanager is a composition 

#include "BasisController.h"
#include "DrawManager.h"
//#include "BasisView.h"
//#include "BasisModel.h"

BasisController::BasisController() {	
	drawmanager = new DrawManager();
}

/*void BasisController::init() {
	setModel();
	initModel();
	setView();
}

void BasisController::initModel() {	
	model->init();
}

void BasisController::initView(BasisModel* model) {	
	view->init();
}
*/