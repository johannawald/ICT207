//  @ Project : QPT 1 - pacmet
//  @ File Name : BasisStateController.h
//  @ MultiMediaTechnology / FHS
//  @ Date : SS/2013
//  @ Author : Johanna Wald
//
//

// Ist die ausimplementierte Klasse von IStateController und hält einen KeyBoardEventHandler,
// der die allgemeinen, für alle States gültigen KeyDown-Events behandelt

#pragma once

#include "IStateController.h"
//#include "Basic/KeyBoardEventHandler.h"

class BasisStateController : public IStateController {
protected:
	//KeyBoardEventHandler keyboardeventhandler;
public:							
	//virtual void keyDownEvent(ci::app::KeyEvent event);
};
