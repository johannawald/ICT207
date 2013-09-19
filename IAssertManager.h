//  @ Unit : ICT207
//  @ File Name : IAssertManager.h
//  @ Author : Johanna Wald
//
//

//Interface for all the AssertManager (Audio, Images ...)

#pragma once

class IAssertManager {
public:			
	virtual void init() = 0;
	virtual void reaload() = 0;
};
