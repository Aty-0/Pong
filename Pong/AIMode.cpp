//===================AIMode.cpp======================
// Purpose:		AI
//
//===================================================

#include "AIMode.h"

void AIMode::Update()
{
	if (ball->m_Pass_Pause == false)
	{
		if (p2->m_Player_PositionY >= game->m_WindowHeight - 40)
		{
			p2->m_Player_PositionY = game->m_WindowHeight - 55.0f;
		}
		else if (p2->m_Player_PositionY <= 0)
		{
			p2->m_Player_PositionY = 5;
		}
		else
		{
			p2->m_Player_PositionY = ball->m_Ball_PositionY - AI_Fault;
		}

		if (AIMode_NoFault == false)
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
	}
	else
	{
		if (p2->m_Player_PositionY == ball->m_Ball_PositionY)
			AI_OnSpawnPoint = true;
		else
			AI_OnSpawnPoint = false;

		if (AI_OnSpawnPoint == false)
		{
			//Walk to spawn ball
			if (p2->m_Player_PositionY >= ball->m_Ball_PositionY)
				p2->m_Player_PositionY -= p2->m_Player_Speed * game->m_time;
			else if (p2->m_Player_PositionY <= ball->m_Ball_PositionY)
				p2->m_Player_PositionY += p2->m_Player_Speed * game->m_time;
		}
	}
}

void AIMode::RegenerateFault()
{
	TimeRegenerateFault = 5.0f;
	AI_Max_Fault = std::rand() % 100;
}