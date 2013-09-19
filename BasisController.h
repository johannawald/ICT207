//  @ File Name : BasisController.h
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet -> later every state should have a view and maybe a model



// general, abstract Controller-class for the MVC
// provides virtual functions to set the model and the view
// all derived classes have to implement these (have their own view (derived from BasisView) and model (derived from BasisModel)) 

#pragma once

class DrawManager;
class AudioManager;
//class BasisView;
//class BasisModel;
class BasisController {
private:
	
protected:
	DrawManager* drawmanager;
	AudioManager* audio;


	/*BasisModel* model;
	BasisView* view;
	
	virtual void setModel() = 0;
	virtual void setView() = 0;
	virtual void initModel();	
	virtual void initView(BasisModel* model);*/
public:	
	BasisController();
	/*virtual void init();
	virtual void draw() = 0;
	virtual void update() = 0;*/
};
