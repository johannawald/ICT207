//  @ File Name : BasisModel.h
//  @ Unit : ICT207
//  @ Author : Johanna Wald
//
// not used yet


#pragma once

// general, abstract model-class for the MVC-Pattern

class BasisModel {
public:
	virtual void init() = 0;
	virtual void update() = 0;
};

