//  @ Unit : ICT207
//  @ File Name : IAssetManager.h
//  @ Author : Johanna Wald
//
//

//Interface for all the AssertManager (Audio, Images ...)

#pragma once

class IAssetManager {
public:			
	virtual void init() = 0;
	virtual void reload() = 0;
};
