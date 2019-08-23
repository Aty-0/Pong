//===================Font.h===========================
// Purpose:			Initialization Fonts
//
//=====================================================

#pragma once
#include "Game.h"

//All fonts here
class Fonts
{
public:
	Font Default_Font;

	Fonts()
	{
		logger->Print("Init Fonts", logger->Debug);
		LOAD_FONT(Default_Font, "Gamedata/Fonts/immortal.ttf");
	}
};
