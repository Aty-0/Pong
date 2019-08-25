//===================Game.h========================
// Purpose:		Core 
//
//=================================================

#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "macros.h"
#include "Logger.h"
#include <iostream>

using namespace sf;

class CGame
{
public:
	CGame();
	virtual ~CGame();

	//Time 
	Clock m_clock;
	Int64 m_time;
	//engine
    const double GAME_VERSION = 1.00000;

	virtual void CreateGame();
	virtual void LoadGame(RenderWindow &window);
	virtual void OnRender(RenderWindow &window);
	virtual void OnUpdate(RenderWindow &window);
	virtual void UpdateEvent(RenderWindow &window);
	virtual void OnExit(RenderWindow &window);
	virtual void CreateWindow();

	//Options
	RenderWindow window;
	VideoMode m_VideoMode;
    //Width Height of Window
	int m_WindowWidth = 800;
	int m_WindowHeight = 600;
	int m_WindowPosX = 300;
	int m_WindowPosY = 300;
	Color m_Background_Color = Color::Black;
	bool m_FullScreen = false;
	bool m_MouseVisible = false;
	int  m_FrameRateLimit = 60;
	int  m_VSync = 0;
	//Options

	//GameActive
	bool GameActive;
	//If app exit or get error all app update stopped
	bool LOOP_UPDATE;
};

extern CGame *game;
