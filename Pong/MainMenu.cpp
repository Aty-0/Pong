//===================MainMenu.cpp========================
// Purpose:		Main Menu
//
//=======================================================

#include "MainMenu.h"
#include "Cursor.h"
#include "AIMode.h"
#include "SoundLoader.h"

CCursor *cursor = NULL;

CMainMenu::CMainMenu()
{
	logger->Print("MainMenu loaded", logger->Debug);
	LaunchMenu();
}


CMainMenu::~CMainMenu()
{
	logger->Print("Menu unloaded", logger->Debug);
}

void CMainMenu::LaunchMenu()
{
	soundloader->StopAllSounds();
	//Stop active game
	game->GameActive = false;
	pause->GamePaused = false;
	//Create Cursor
	cursor = new CCursor();
	//Set Main scene
	m_CorrectScene = m_MainMenuScenes::MAIN;
	//discharge to default mode
	m_GameMode = m_GameMods::DEFAULT;
	//Load scene
	LoadScene();

	//Delete all game elements
	logger->Print("delete game classes", logger->Debug);
	SAFE_DELETE(p1);
	SAFE_DELETE(p2);
	SAFE_DELETE(counttext);
	SAFE_DELETE(ball);
	SAFE_DELETE(pong_grig);
}

void CMainMenu::LoadScene()
{
	switch (m_CorrectScene)
	{
	case CMainMenu::MAIN:
		//Create text's
		CREATE_TEXT(Scene_Menu_Ver_Text, 12, Default_Font, Color::White, 0, game->m_WindowHeight - 30.0f, "v" + string(game->GAME_VERSION) +"\nGame by Antd23rus");
		CREATE_TEXT(Scene_Menu_Logo_Text, 35, Default_Font, Color::White, game->m_WindowWidth - 450.0f, 30, "Pong");
		CREATE_TEXT(Scene_Menu_Text, 15, Default_Font, Color::White, game->m_WindowWidth - 450.0f, 100, "Enter - Launch game\nE - Exit");
		break;
	case CMainMenu::MODE_SELECTION:
		CREATE_TEXT(Scene_Menu_Selection_Text, 25, Default_Font, Color::White, 0.0f, 30, "Mode selections");
		CREATE_TEXT(Scene_Menu_List_Selection_Text, 15, Default_Font, Color::White, 0, 100, "D - Default \nA - Play with bot");
		CREATE_TEXT(Scene_Menu_Back_Text, 15, Default_Font, Color::White, game->m_WindowWidth - 200, game->m_WindowHeight, "Esc - Back to Menu");
		break;

	default:
		logger->Print("Unknown scene", logger->FatalError);
		break;
	}
}

void CMainMenu::LaunchGame()
{
	logger->Print("Load all game classes", logger->Debug);
	soundloader->StopAllSounds();

	//Game 
	if (m_GameMode == CMainMenu::AI_MODE)
		aimode->AIMode_Work = true;
	else
		aimode->AIMode_Work = false;
	
	//Create a players
	p1 = new CPlayer(50.0f, 300.0f, 7.0f, 50.0f, 0.5f);
	p2 = new CPlayer(750.0f, 300.0f, 7.0f, 50.0f, 0.5f);
	//Create other game elements
	counttext = new CCountText();
	ball = new CBall();
	pong_grig = new CPong_grid();
	//Game 
	
	game->GameActive = true;

	//Delete menu
	logger->Print("Delete menu class!", logger->Debug);
	SAFE_DELETE(mainmenu);
}

void CMainMenu::KeyEvents(Event event, RenderWindow &window)
{
	switch (m_CorrectScene)
	{
	case CMainMenu::MAIN:
		if (event.key.code == Keyboard::Enter)
		{
			m_CorrectScene = m_MainMenuScenes::MODE_SELECTION;
			LoadScene();
		}
		//Exit
		if (event.key.code == Keyboard::E)
		{
			game->OnExit(window);
		}
		break;

	case CMainMenu::MODE_SELECTION:
		if (event.key.code == Keyboard::D)
		{
			m_GameMode = CMainMenu::DEFAULT;
			LaunchGame();
		}
		if (event.key.code == Keyboard::A)
		{
			m_GameMode = CMainMenu::AI_MODE;
			LaunchGame();
		}
		break;
	}
}

void CMainMenu::OnUpdate(RenderWindow &window)
{
	//Update Cursor
	cursor->Update(window);
}

void CMainMenu::OnRender(RenderWindow &window)
{
	//Draw correct scene
	switch (m_CorrectScene)
	{
	case CMainMenu::MAIN:
		//Draw text's
		window.draw(Scene_Menu_Text);
		window.draw(Scene_Menu_Ver_Text);
		window.draw(Scene_Menu_Logo_Text);
		break;
	case CMainMenu::MODE_SELECTION:
		window.draw(Scene_Menu_Selection_Text);
		window.draw(Scene_Menu_List_Selection_Text);
		window.draw(Scene_Menu_Back_Text);
		break;
	}
	//Draw 
	cursor->Draw(window);
}
