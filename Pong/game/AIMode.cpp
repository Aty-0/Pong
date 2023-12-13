//===================AIMode.cpp======================
// Purpose:		AI
//
//===================================================

#include "AIMode.h"

namespace sbt
{
	void AIMode::onUpdate(float deltaTime)
	{
		//if (ball->m_Pass_Pause == false)
		//{
		//	//Move Logic
		//	if (p2->m_Player_PositionY >= game->m_WindowHeight - 40)
		//	{
		//		p2->m_Player_PositionY = game->m_WindowHeight - 55.0f;
		//	}
		//	else if (p2->m_Player_PositionY <= 0)
		//	{
		//		p2->m_Player_PositionY = 5;
		//	}
		//	else
		//	{
		//		p2->m_Player_PositionY = ball->m_Ball_PositionY - AI_Fault;
		//	}
		//
		//
		//	//Fault Logic
		//	if (AIMode_NoFault == false)
		//	{
		//		//Dynamicly change fault
		//		if (AI_Fault >= AI_Max_Fault)
		//			AI_Fault--;
		//		else if (AI_Fault <= AI_Max_Fault)
		//			AI_Fault++;
		//
		//		//Time Regenerate
		//		if (TimeRegenerateFault <= 0.0f)
		//			RegenerateFault();
		//		else
		//			TimeRegenerateFault -= 0.05f;
		//	}
		//}
		//else
		//{
		//	//Try search Y ball position, if bot on player possition his stop search
		//	if (p2->m_Player_PositionY == ball->m_Ball_PositionY)
		//		AI_OnSpawnPoint = true;
		//	else
		//		AI_OnSpawnPoint = false;
		//
		//	//Search
		//	if (AI_OnSpawnPoint == false)
		//	{
		//		//Walk to spawn ball
		//		if (p2->m_Player_PositionY >= ball->m_Ball_PositionY)
		//			p2->m_Player_PositionY -= p2->m_Player_Speed * game->m_time;
		//		else if (p2->m_Player_PositionY <= ball->m_Ball_PositionY)
		//			p2->m_Player_PositionY += p2->m_Player_Speed * game->m_time;
		//	}
		//}
	}

	void AIMode::regenerateFault()
	{
		//TimeRegenerateFault = 5.0f;
		//AI_Max_Fault = std::rand() % 100;
	}
}