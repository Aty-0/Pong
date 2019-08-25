//===================Bot.cpp=========================
// Purpose:		AI
//
//===================================================

#include "Bot.h"

CBot::CBot()
{

}

CBot::~CBot()
{
	m_Bot_PositionX = 0;
	m_Bot_PositionY = 0;
	m_Bot_SizeX = 0.0f;
	m_Bot_SizeY = 0.0f;
	m_Bot_ScaleX = 0;
	m_Bot_ScaleY = 0;
	m_Bot_Speed = 0.0f;

	UpdateStats();
}

void CBot::CreateBot(float x, float y)
{
	//Position X and Y
	m_Bot_PositionX = x;
	m_Bot_PositionY = y;
	//Scale X and Y
	m_Bot_SizeX = 7.0f;
	m_Bot_SizeY = 50.0f;
	m_Bot_ScaleX = 1;
	m_Bot_ScaleY = 1;
	//Speed
	m_Bot_Speed = 0.5f;
	//For debug
	m_Bot_Color = Color::White;
	UpdateStats();
}

//Update scale,position of player
void CBot::UpdateStats()
{
	m_Bot.setSize(Vector2f(m_Bot_SizeX, m_Bot_SizeY));
	m_Bot.setScale(Vector2f(m_Bot_ScaleX, m_Bot_ScaleY));
	m_Bot.setPosition(m_Bot_PositionX, m_Bot_PositionY);
	m_Bot.setOutlineColor(Color::Transparent);
	m_Bot.setFillColor(m_Bot_Color);
	m_Bot.setOutlineThickness(5);
}

void CBot::UpdateGlobalBounds()
{
	getGlobalBounds.top = m_Bot_PositionY;
	getGlobalBounds.left = m_Bot_PositionX;
	getGlobalBounds.width = m_Bot_SizeX;
	getGlobalBounds.height = m_Bot_SizeY;
}

void CBot::UpdateFault()
{
	if (AI_Fault >= AI_Max_Fault)
		AI_Fault--;
	else if (AI_Fault <= AI_Max_Fault)
		AI_Fault++;

	if (TimeRegenerateFault <= 0.0f)
		RegenerateFault();
	else
		TimeRegenerateFault -= 0.05f;
}

void CBot::OnUpdate()
{
	m_Bot.setPosition(m_Bot_PositionX, m_Bot_PositionY);
	UpdateGlobalBounds();
	CheckInvisibleWalls();
	Walk();
	UpdateFault();
}

void CBot::Walk()
{
	//Walk to ball
	if (m_Bot_PositionY >= ball->m_Ball_PositionY)
	{
		m_walk_down = true;
		m_walk_up = false;
	}
	else if (m_Bot_PositionY <= ball->m_Ball_PositionY)
	{
		m_walk_up = true;
		m_walk_down = false;
	}

	if (m_walk_up == true)
		m_Bot_PositionY += m_Bot_Speed * game->m_time - AI_Fault;
	else if(m_walk_down)
		m_Bot_PositionY -= m_Bot_Speed * game->m_time - AI_Fault;
}

//Check collision of invisible walls
void CBot::CheckInvisibleWalls()
{
	if (m_Bot_PositionY >= game->m_WindowHeight - 40)
	{
		m_Bot_PositionY = game->m_WindowHeight - 55.0f;
		m_walk_up = false;
		m_walk_down = false;
	}
	else if (m_Bot_PositionY <= 0)
	{
		m_Bot_PositionY = 5;
		m_walk_up = false;
		m_walk_down = false;
	}
}

void CBot::RegenerateFault()
{
	TimeRegenerateFault = 5.0f;
	AI_Max_Fault = std::rand() % 100;
}

void CBot::OnRender(RenderWindow &window)
{
	window.draw(m_Bot, BlendAlpha);
}
