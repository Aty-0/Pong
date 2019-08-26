//===================AIMode.h========================
// Purpose:		AI
//
//===================================================

#pragma once
#include "Game.h"
#include "Player.h"
#include "Ball.h"

class CAIMode
{
public:
	//That for start ai mode
	bool AIMode_Work;
	//Fault
	bool AIMode_NoFault;
	int AI_Fault;
	int AI_Max_Fault;
	float TimeRegenerateFault = 5.0f;
	virtual void RegenerateFault();
	//Fault

	bool AI_OnSpawnPoint;

	virtual void Update();
};

extern CAIMode *aimode;

