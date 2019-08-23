//===================Player.h========================
// Purpose:		Simple class of player
//
//===================================================

#pragma once
#include "Game.h"

class CPlayer
{
public:
	//Creating player
	CPlayer(float x, float y, float sizex, float sizey, float speed);
	//Delete player
	virtual ~CPlayer();
	virtual void OnUpdate();
	//If player delete or created 
	virtual void UpdateStats();
	virtual void UpdateGlobalBounds();
	virtual void OnRender(RenderWindow &window);
	//Keys Events
	virtual void KeyPressed(Event event);
	virtual void KeyReleased(Event event);
	//Invisible Walls _-_
	virtual void CheckInvisibleWalls();
	//For walk
	virtual void CheckControl();
	//Player stats
	RectangleShape m_Player;
	int   m_Player_Count;
	Color m_Player_Color;
	float m_Player_PositionX;
	float m_Player_PositionY;
	float m_Player_SizeX;
	float m_Player_SizeY;
	float m_Player_ScaleX;
	float m_Player_ScaleY;
	float m_Player_Speed;

	FloatRect getGlobalBounds;

	//Walk 
	bool m_walk_up;
	bool m_walk_down;
	bool DEBUG_Walk_All_Players;
	//Player stats
};
//extern 2 players
extern CPlayer *p1;
extern CPlayer *p2;