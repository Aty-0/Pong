//===================Bot.h===========================
// Purpose:		AI
//
//===================================================

#pragma once
#include "Game.h"
#include "Player.h"
#include "Ball.h"

class CBot
{
public:
	//Create bot
	virtual void CreateBot(float x, float y);
	CBot();
	//Delete bot
	virtual ~CBot();

	bool AI_OnSpawnPoint;
	//If player delete or created 
	virtual void UpdateStats();
	//Update
	virtual void OnUpdate();
	//Render
	virtual void OnRender(RenderWindow &window);
	//Check Invisible walls
	virtual void CheckInvisibleWalls();
	//For bot walk
	virtual void Walk();

	//Global bounds
	virtual void UpdateGlobalBounds();
	FloatRect getGlobalBounds;
	//Global bounds

	//That for start ai mode
	bool AIMode_Work;

	//Fault
	bool AIMode_NoFault;
	int AI_Fault;
	int AI_Max_Fault;
	float TimeRegenerateFault = 5.0f;
	virtual void UpdateFault();
	virtual void RegenerateFault();
	//Fault

	//Player stats
	RectangleShape m_Bot;
	//int   m_Bot_Count;
	Color m_Bot_Color;
	float m_Bot_PositionX;
	float m_Bot_PositionY;
	float m_Bot_SizeX;
	float m_Bot_SizeY;
	float m_Bot_ScaleX;
	float m_Bot_ScaleY;
	float m_Bot_Speed;

	//Walk 
	bool m_walk_up;
	bool m_walk_down;
};

extern CBot *bot;

