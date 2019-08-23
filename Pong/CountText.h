//===================CountText.h=======================
// Purpose:			Count Text
//
//=====================================================

#pragma once
#include "Game.h"
#include "Fonts.h"

class CCountText : public Fonts
{
public:
	CCountText();
	Text CountText;

	virtual void OnRender(RenderWindow &window);
};

extern CCountText *counttext;