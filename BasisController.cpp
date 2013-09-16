//  @ File Name : BasisController.cpp
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet


#include "BasisController.h"

#include "BasisView.h"
#include "BasisModel.h"

void BasisController::init() {
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
