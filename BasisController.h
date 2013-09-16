//  @ File Name : BasisController.h
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet



// general, abstract Controller-class for the MVC
// provides virtual functions to set the model and the view
// all derived classes have to implement these (have their own view (derived from BasisView) and model (derived from BasisModel)) 

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
