//  @ Project : QPT 1 - pacmet
//  @ File Name : BasisController.cpp
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

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
