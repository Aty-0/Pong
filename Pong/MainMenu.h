//===================MainMenu.h========================
// Purpose:		Main Menu
//
//=====================================================

#pragma once
#include "Game.h"
#include "Fonts.h"
#include "Pong_grid.h"
#include "CountText.h"
#include "Ball.h"
#include "Player.h"
#include "Pause.h"

class CMainMenu : public Fonts
{
public:
	CMainMenu();
	virtual ~CMainMenu();
	virtual void LaunchGame();
	virtual void LaunchMenu();
	virtual void KeyEvents(Event event, RenderWindow &window);
	virtual void OnUpdate(RenderWindow &window);
	virtual void OnRender(RenderWindow &window);
	virtual void LoadScene();

	//!!!SCENE!!!

	//List of main menu scenes
	enum m_MainMenuScenes
	{
		MAIN,
		MODE_SELECTION
	};
	//Correct scene
	m_MainMenuScenes m_CorrectScene;

	//Main scene
	Text Scene_Menu_Text;
	Text Scene_Menu_Ver_Text;
	Text Scene_Menu_Logo_Text;
	//Mode selection scene
	Text Scene_Menu_Selection_Text;
	Text Scene_Menu_List_Selection_Text;
	//For all scene except Main
	Text Scene_Menu_Back_Text;
	//!!!SCENE!!!

	//Game Mods
	enum m_GameMods
	{
		DEFAULT,
		AI_MODE
	};
	m_GameMods m_GameMode;
};

extern CMainMenu *mainmenu;