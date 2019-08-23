//===================Game.cpp========================
// Purpose:		Core 
//
//===================================================
#include "Game.h"
#include "MainMenu.h"
#include "SoundLoader.h"
#include "AIMode.h"

CCountText *counttext = NULL;
CBall *ball = NULL;
CLogger *logger = NULL;
CPong_grid *pong_grig = NULL;
CMainMenu *mainmenu = NULL;
CSoundLoader *soundloader = NULL;
AIMode *aimode = NULL;
//Players
CPlayer *p1 = NULL;
CPlayer *p2 = NULL;

CGame::CGame()
{
	game = this;
	logger = new CLogger();
	LOOP_UPDATE = true;
	GamePaused = false;
	CreateGame();
}


CGame::~CGame()
{

}

void CGame::CreateWindow()
{
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

void CGame::CreateGame()
{
	logger->Print("Create Window", logger->Debug);
	CreateWindow();

	LoadGame(window);

	logger->Print("Create loop", logger->Debug);
	//Create loop
	while(window.isOpen() || LOOP_UPDATE == true)
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

void CGame::LoadGame(RenderWindow &window)
{
	logger->Print("Load Game...", logger->Debug);
	if (!game && game == NULL)
	{
		logger->Print("game == NULL", logger->FatalError);
	}
	else
	{
		mainmenu = new CMainMenu();
		aimode = new AIMode();
		soundloader = new CSoundLoader();
	}

}

void CGame::OnRender(RenderWindow &window)
{
	window.clear();
	if (GamePaused == true)
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
	}
	window.display();
}

void CGame::OnUpdate(RenderWindow &window)
{
	if (GamePaused == true)
	{
		mainmenu->OnUpdate(window);
	}
	else
	{
		ball->OnUpdate();
		p1->OnUpdate();
		p2->OnUpdate();		
	}
}

void CGame::OnExit(RenderWindow &window)
{
	logger->Print("Shutdown", logger->Debug);
	LOOP_UPDATE = false;
	logger->CreateLogFile();
	SAFE_DELETE(logger);
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
			if (GamePaused == false)
			{
				p1->KeyReleased(event);
				p2->KeyReleased(event);
			}
		}

		if (event.type == Event::KeyPressed)
		{
			if (GamePaused == true)
				mainmenu->KeyEvents(event, window);

			if (GamePaused == false)
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
				if (GamePaused == false)
					mainmenu = new CMainMenu();
				else
				{
					if (mainmenu->m_CorrectScene == mainmenu->m_MainMenuScenes::MAIN)
						OnExit(window);
					else
					{
						mainmenu->m_CorrectScene = mainmenu->m_MainMenuScenes::MAIN;
						mainmenu->LoadScene();
					}
				}
			}
		}
	}
}