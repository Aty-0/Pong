//===================Player.cpp======================
// Purpose:		Simple class of player 
//
//===================================================

#include "Player.h"
#include "AIMode.h"


//Create player
CPlayer::CPlayer(float x, float y, float sizex, float sizey, float speed)
{
	logger->Print("Player created", logger->Debug);
	//Position X and Y
	m_Player_PositionX = x;
	m_Player_PositionY = y;
	//Scale X and Y
	m_Player_SizeX = sizex;
	m_Player_SizeY = sizey;
	m_Player_ScaleX = 1;
	m_Player_ScaleY = 1;
	//Count
	m_Player_Count = 0;
	//Speed
	m_Player_Speed = speed;
	//For debug
	m_Player_Color = Color::White;
	UpdateStats();
}

//Delete 
CPlayer::~CPlayer()
{
	logger->Print("Player unloaded", logger->Debug);
	m_Player_PositionX = 0;
	m_Player_PositionY = 0;
	m_Player_SizeX = 0;
	m_Player_SizeY = 0;
	m_Player_ScaleX = 0;
	m_Player_ScaleY = 0;
	m_Player_Count = 0;
	m_Player_Speed = 0;

	UpdateStats();
}


//Update scale,position of player
void CPlayer::UpdateStats()
{
	m_Player.setSize(Vector2f(m_Player_SizeX, m_Player_SizeY));
	m_Player.setScale(Vector2f(m_Player_ScaleX, m_Player_ScaleY));
	m_Player.setPosition(m_Player_PositionX, m_Player_PositionY);
	m_Player.setOutlineColor(Color::Transparent);
	m_Player.setFillColor(m_Player_Color);
	m_Player.setOutlineThickness(5);
}

//For walk
void CPlayer::CheckControl()
{
	if (m_walk_up == true)
	{
		m_Player_PositionY -= m_Player_Speed * game->m_time;
	}
	else if (m_walk_down == true)
	{
		m_Player_PositionY += m_Player_Speed * game->m_time;
	}
}

//Check collision of invisible walls
void CPlayer::CheckInvisibleWalls()
{
	if (m_Player_PositionY >= game->m_WindowHeight - 40)
	{
		m_Player_PositionY = game->m_WindowHeight - 55.0f;
		m_walk_up = false;
		m_walk_down = false;
	}
	else if (m_Player_PositionY <= 0)
	{
		m_Player_PositionY = 5;
		m_walk_up = false;
		m_walk_down = false;
	}
}

//Key
void CPlayer::KeyPressed(Event event)
{
	if (this == p1)
	{
		if (event.key.code == Keyboard::W)
		{
			m_walk_up = true;
		}

		if (event.key.code == Keyboard::S)
		{
			m_walk_down = true;
		}
	}
	if (aimode->AIMode_Work == false)
	{
		if (this == p2)
		{
			if (event.key.code == Keyboard::I)
			{
				m_walk_up = true;
			}

			if (event.key.code == Keyboard::K)
			{
				m_walk_down = true;
			}
		}
	}
}

void CPlayer::KeyReleased(Event event)
{
	if (this == p1)
	{
		if (event.key.code == Keyboard::W)
		{
			m_walk_up = false;
		}

		if (event.key.code == Keyboard::S)
		{
			m_walk_down = false;
		}
	}
	if (aimode->AIMode_Work == false)
	{
		if (this == p2)
		{
			if (event.key.code == Keyboard::I)
			{
				m_walk_up = false;
			}

			if (event.key.code == Keyboard::K)
			{
				m_walk_down = false;
			}
		}
	}
}
//Key

void CPlayer::UpdateGlobalBounds()
{
	m_Player_Rect.top = m_Player_PositionY;
	m_Player_Rect.left = m_Player_PositionX;
	m_Player_Rect.width = m_Player_SizeX;
	m_Player_Rect.height = m_Player_SizeY;
}

//Update Func
void CPlayer::OnUpdate()
{
	m_Player.setPosition(m_Player_PositionX, m_Player_PositionY);
	UpdateGlobalBounds();
	CheckControl();
	CheckInvisibleWalls();
	if (aimode->AIMode_Work == true)
		aimode->Update();
}

//Render player
void CPlayer::OnRender(RenderWindow &window)
{
	window.draw(m_Player, BlendAlpha);
}