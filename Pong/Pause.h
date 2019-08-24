//===================Pause.h=========================
// Purpose:		Game Pause
//
//===================================================

#pragma once
#include "Game.h"
#include "Fonts.h"

class CPause : public Fonts
{
public:
	CPause();
	Text PauseText;
	bool GamePaused;
	virtual void KeyEvents(Event event);
	virtual void OnRender(RenderWindow &window);
};

extern CPause *pause;