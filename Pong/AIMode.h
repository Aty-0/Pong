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
	//For debug
	bool AIMode_NoFault;
	//Correct ai fault
	int AI_Fault;
	int AI_Max_Fault;
	//For regenerate fault 
	float TimeRegenerateFault = 5.0f;
	virtual void RegenerateFault();
	//Fault

	//If ai on spawn point
	bool AI_OnSpawnPoint;

	virtual void Update();
};

extern CAIMode *aimode;

