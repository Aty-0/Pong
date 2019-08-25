//===================Pause.cpp=======================
// Purpose:		Game Pause
//
//===================================================

#include "Pause.h"
#include "MainMenu.h"

CPause::CPause()
{
	CREATE_TEXT(PauseText, 20, Default_Font, Color::White, 20, 50, "Paused!\nEsc - Main Menu\nEnter - Resume");
}

void CPause::OnRender(RenderWindow &window)
{
	window.draw(PauseText);
}

void CPause::KeyEvents(Event event)
{
	if (event.key.code == Keyboard::Enter)
	{
		pause->GamePaused = false;
	}
}