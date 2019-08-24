//===================Ball.cpp========================
// Purpose:		Logic, Check on collision and adding player points
//
//===================================================

#include "Ball.h"
#include "Player.h"
#include "SoundLoader.h"
#include "Config.h"

CBall::CBall()
{
	logger->Print("Ball created", logger->Debug);
	//Default stats ball, if configs not read 
	m_Ball_PositionX = 400.0f;
	m_Ball_PositionY = 250.0f;
	m_Ball_ScaleX = 1.0f;
	m_Ball_ScaleY = 1.0f;
	m_Ball_SizeX = 10.0f;
	m_Ball_SizeY = 10.0f;
	m_Ball_Angle = 0.0f;
	m_Ball_Speed = 0.2f;
	m_Ball_Color = Color::White;
	m_Ball_Stop_All_Logic = false;
	m_Pass_Pause_Default_Time = 10.0f;
	//Load configs
	config->LoadConfig("Gamedata/Config/ball.xml", "Speed", m_Ball_Speed);
	config->LoadConfig("Gamedata/Config/ball.xml", "SizeX", m_Ball_SizeX);
	config->LoadConfig("Gamedata/Config/ball.xml", "SizeY", m_Ball_SizeY);
	config->LoadConfig("Gamedata/Config/ball.xml", "Angle", m_Ball_Angle);
	config->LoadConfig("Gamedata/Config/ball.xml", "PassTime", m_Pass_Pause_Default_Time);
	//Update Stats
	UpdateBallStats();
	//Random pass to player
	RandomPassBall();
}

CBall::~CBall()
{
	m_Ball_PositionX = 0.0f;
	m_Ball_PositionY = 0.0f;
	m_Ball_ScaleX = 0.0f;
	m_Ball_ScaleY = 0.0f;
	m_Ball_Angle = 0.0f;
	m_Ball_Speed = 0.0f;
	m_Ball_SizeX = 0.0f;
	m_Ball_SizeY = 0.0f;
	m_Pass_Pause_Time = 0.0f;
	m_Pass_Pause_Default_Time = 0.0f;
	m_Ball_Color = Color::White;
	m_Ball_Stop_All_Logic = true;
	m_Ball_Draw = false;
	UpdateBallStats();
}

void CBall::UpdateBallStats()
{
	m_Ball.setSize(Vector2f(m_Ball_SizeX, m_Ball_SizeY));
	m_Ball.setPosition(m_Ball_PositionX, m_Ball_PositionY);
	m_Ball.setScale(m_Ball_ScaleX, m_Ball_ScaleY);
	m_Ball.setRotation(m_Ball_Angle);
	m_Ball.setFillColor(m_Ball_Color);
	//Ball size
	getGlobalBounds.width = m_Ball_SizeX;
	getGlobalBounds.height = m_Ball_SizeY;
}

void CBall::UpdateGlobalBounds()
{
	getGlobalBounds.top = m_Ball_PositionY;
	getGlobalBounds.left = m_Ball_PositionX;
	getGlobalBounds.width = m_Ball_SizeX;
	getGlobalBounds.height = m_Ball_SizeY;
}

void CBall::Reset()
{
	m_Ball_PositionX = 400.0f;
	m_Pass_Pause_Time = m_Pass_Pause_Default_Time;
	m_Pass_Pause = true;
	m_Ball_Draw = false;
	PassBall();
}

void CBall::RandomPassBall()
{
	//Set random pass and y pos
	m_Pass_Player = std::rand() % 2;
	m_Pass_PosY = std::rand() % game->m_WindowHeight;


	m_Ball_PositionY = m_Pass_PosY;
	//Check if ball out of screen and return it 
	if (m_Ball_PositionY <= 0)
	{
		m_Ball_PositionY = 50;
		logger->Print("m_Ball_PositionY <= 0, ball returned! m_Pass_PosY = " + to_string(m_Pass_PosY), logger->Warning);
	}

	if (m_Ball_PositionY >= 300)
		m_Push = m_Push_Status::Put_Down;
	else if (m_Ball_PositionY <= 300)
		m_Push = m_Push_Status::Lift_Up;

	//Pause
	m_Pass_Pause_Time = m_Pass_Pause_Default_Time;
	m_Pass_Pause = true;
	m_Ball_Draw = false;

	m_Pass_PosY = 0;
}

void CBall::PassBall()
{
	//Whom pass the ball
	if (m_Pass_Scored == 0)
		m_Pass_Scored = 1;
	else if (m_Pass_Scored == 1)
		m_Pass_Scored = 0;

	//Random y position
	m_Pass_PosY = std::rand() % game->m_WindowHeight - 50.0f;
	//Set y position
	m_Ball_PositionY = m_Pass_PosY;


	if (m_Ball_PositionY <= 0)
	{
		m_Ball_PositionY = 50;
		logger->Print("m_Ball_PositionY <= 0, ball returned! m_Pass_PosY = " + to_string(m_Pass_PosY), logger->Warning);
	}

	if (m_Ball_PositionY >= 300)
		m_Push = m_Push_Status::Put_Down;
	else if (m_Ball_PositionY <= 300)
		m_Push = m_Push_Status::Lift_Up;

	m_Pass_PosY = 0;
	m_Pass_Player = m_Pass_Scored;
}

void CBall::OnUpdate()
{
	if (!m_Ball_Stop_All_Logic)
	{
		m_Ball.setPosition(m_Ball_PositionX, m_Ball_PositionY);
		if (m_Pass_Pause == false)
		{
			//Collision
			UpdateGlobalBounds();
			DetectCollision();

			if (m_Pass_Player == 0)
			{
				m_Ball_PositionX += m_Ball_Speed * game->m_time;
			}
			else if (m_Pass_Player == 1)
			{
				m_Ball_PositionX -= m_Ball_Speed * game->m_time;
			}

			if (m_Push == m_Push_Status::Lift_Up)
			{
				m_Ball_PositionY += m_Ball_Speed * game->m_time;
			}
			else if (m_Push == m_Push_Status::Put_Down)
			{
				m_Ball_PositionY -= m_Ball_Speed * game->m_time;
			}
		}
		else
		{
			m_Pass_Pause_Time -= 0.01f * game->m_time;

			if (m_Pass_Pause_Time <= 0.0f)
			{
				soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Created.wav", 10.0f, 1.0f, false);
				m_Pass_Pause = false;
				m_Ball_Draw = true;
			}
		}
	}
}

void CBall::DetectCollision()
{
	//Check collision with player
	if (ball->getGlobalBounds.intersects(p1->getGlobalBounds))
	{
		//logger->Print("Player one touch ball", logger->Debug);
		soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Hitted.wav", 5.0f, 1.0f, false);
		m_Pass_Player = 0;
	}

	if (ball->getGlobalBounds.intersects(p2->getGlobalBounds))
	{
		//logger->Print("Player two touch ball", logger->Debug);
		soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Hitted.wav", 5.0f, 1.0f, false);
		m_Pass_Player = 1;
	}

	//Check collision with screen bounds
	if (m_Ball_PositionY <= 0)
	{
		soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Hitted.wav", 5.0f, 1.0f, false);
		//Up
		m_Push = m_Push_Status::Lift_Up;
	}
	else if (m_Ball_PositionY >= game->m_WindowHeight)
	{
		soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Hitted.wav", 5.0f, 1.0f, false);
		//Down
		m_Push = m_Push_Status::Put_Down;
	}

	//Check if ball out of screen
	if (m_Ball_PositionY <= -10)
	{
		logger->Print("m_Ball out of screen!", logger->Warning);
		m_Ball_PositionY = 10;
	}
	else if (m_Ball_PositionY >= game->m_WindowHeight + 10)
	{
		logger->Print("m_Ball out of screen!", logger->Warning);
		m_Ball_PositionY = game->m_WindowHeight - 10;
	}

	//It's reset trigger, if ball ont needed position then he reset
	if (m_Ball_PositionX >= game->m_WindowWidth)
	{
		soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Scored.wav", 10.0f, 1.0f, false);
		p1->m_Player_Count++;
		m_Pass_Scored = 0;
		Reset();
	}
	else if (m_Ball_PositionX <= 0.0f)
	{
		soundloader->PlaySoundFromFile("Gamedata/Sounds/Ball_Scored.wav", 10.0f, 1.0f, false);
		p2->m_Player_Count++;
		m_Pass_Scored = 1;
		Reset();
	}
}

void CBall::OnRender(RenderWindow &window)
{
	if (m_Ball_Draw)
		window.draw(m_Ball);
}