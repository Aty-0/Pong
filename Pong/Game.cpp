//===================Game.cpp========================
// Purpose:		Core 
//
//===================================================
#include "Game.h"
#include "MainMenu.h"
#include "SoundLoader.h"
#include "AIMode.h"
#include "Config.h"

CConfig *config = NULL;
CPause *pause = NULL;
CCountText *counttext = NULL;
CBall *ball = NULL;
CLogger *logger = NULL;
CPong_grid *pong_grig = NULL;
CMainMenu *mainmenu = NULL;
CSoundLoader *soundloader = NULL;
CAIMode *aimode = NULL;
//Players
CPlayer *p1 = NULL;
CPlayer *p2 = NULL;

CGame::CGame()
{
	game = this;
	logger = new CLogger();
	config = new CConfig();
	LOOP_UPDATE = true;
	GameActive = false;
	CreateGame();
}


CGame::~CGame()
{

}

void CGame::CreateWindow()
{
	logger->Print("Create Window", logger->Debug);
	//Video Mode
	m_VideoMode.width = m_WindowWidth;
	m_VideoMode.height = m_WindowHeight;
	m_VideoMode.bitsPerPixel = 32;
	//Create Window
	if (m_FullScreen == true)
	{
		m_VideoMode.getFullscreenModes();
		window.create(VideoMode(m_VideoMode), "Pong", Style::None | Style::Fullscreen);
	}
	else
	{
		m_VideoMode.getDesktopMode();
		window.create(VideoMode(m_VideoMode), "Pong", Style::Titlebar | Style::Close);
		window.setPosition(Vector2i(m_WindowPosX, m_WindowPosY));
	}
	//Set window options
	window.setFramerateLimit(m_FrameRateLimit);
	window.setMouseCursorVisible(m_MouseVisible);
	window.setVerticalSyncEnabled(m_VSync);
}

void CGame::LoadMainGameConfigs()
{
	logger->Print("Try load game config", logger->Debug);
	config->LoadConfig("Gamedata/Config/game.xml", "VSync", m_VSync);
	config->LoadConfig("Gamedata/Config/game.xml", "MouseVisible", m_MouseVisible);
	config->LoadConfig("Gamedata/Config/game.xml", "Fullscreen", m_FullScreen);
	config->LoadConfig("Gamedata/Config/game.xml", "WndX", m_WindowPosX);
	config->LoadConfig("Gamedata/Config/game.xml", "WndY", m_WindowPosY);
	config->LoadConfig("Gamedata/Config/game.xml", "FpsLimit", m_FrameRateLimit);
	config->LoadConfig("Gamedata/Config/game.xml", m_Background_Color);
}

void CGame::CreateGame()
{
	LoadMainGameConfigs();
	CreateWindow();
	LoadGame(window);

	logger->Print("Create loop", logger->Debug);
	//Create loop
	while(window.isOpen())
	{
		if (LOOP_UPDATE == false)
		{
			OnExit(window);
			break;
		}
		else
		{
			//Set Engine Time
			m_time = m_clock.getElapsedTime().asMicroseconds();
			m_clock.restart();
			m_time = m_time / 800;
			//Update event
			UpdateEvent(window);
			OnRender(window);
			OnUpdate(window);
		}
	}
}

void CGame::LoadGame(RenderWindow &window)
{
	logger->Print("Load Game...", logger->Debug);
	if (!game && game == NULL)
	{
		logger->Print("game == NULL", logger->FatalError);
	}
	else
	{
		pause = new CPause();
		aimode = new CAIMode();
		soundloader = new CSoundLoader();
		//Start game
		mainmenu = new CMainMenu();	
	}
}

void CGame::OnRender(RenderWindow &window)
{
	window.clear(m_Background_Color);
	if (GameActive == false)
	{
		mainmenu->OnRender(window);
	}
	else 
	{
		ball->OnRender(window);
		pong_grig->OnRender(window);
		p1->OnRender(window);
		p2->OnRender(window);
		counttext->OnRender(window);

		if (pause->GamePaused == true)
			pause->OnRender(window);
		
	}
	window.display();
}

void CGame::OnUpdate(RenderWindow &window)
{
	if (GameActive == false)
	{
		mainmenu->OnUpdate(window);
	}
	else
	{
		if (pause->GamePaused == false)
		{
			ball->OnUpdate();
			p1->OnUpdate();
			p2->OnUpdate();
		}
	}
}

void CGame::OnExit(RenderWindow &window)
{
	logger->Print("Shutdown", logger->Debug);
	logger->CreateLogFile();
	if (LOOP_UPDATE == false)
		logger->ShowErrorMsg();
	SAFE_DELETE(logger);
	LOOP_UPDATE = false;
	window.close();
}

void CGame::UpdateEvent(RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			OnExit(window);

		if(event.type == Event::KeyReleased)
		{
			if (GameActive == true)
			{
				p1->KeyReleased(event);
				p2->KeyReleased(event);
			}
		}

		if (event.type == Event::KeyPressed)
		{
			if (GameActive == false)
				mainmenu->KeyEvents(event, window);

			if (pause->GamePaused == true)
				pause->KeyEvents(event);

			if (GameActive == true)
			{
				p1->KeyPressed(event);
				p2->KeyPressed(event);
			}

			if (event.key.code == Keyboard::F11)
			{
				m_FullScreen = !m_FullScreen;
				window.close();
				CreateWindow();
			}

			if (event.key.code == Keyboard::Escape)
			{
				if (pause->GamePaused == true)
					mainmenu = new CMainMenu();
				else if (GameActive == false)
				{
					if (mainmenu->m_CorrectScene == mainmenu->m_MainMenuScenes::MAIN)
						OnExit(window);
					else
					{
						mainmenu->m_CorrectScene = mainmenu->m_MainMenuScenes::MAIN;
						mainmenu->LoadScene();
					}
				}
				else if (GameActive == true || pause->GamePaused == false)
					pause->GamePaused = true;
			}
		}
	}
}