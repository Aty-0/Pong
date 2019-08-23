//===================Pong_grid.h=========================
// Purpose:			Grid
//
//=======================================================

#pragma once
#include "Game.h"
//Pong grid it's interior lines

class CPong_grid
{
public:
	Vertex line[2];

	CPong_grid();
	virtual ~CPong_grid();
	virtual void OnRender(RenderWindow &window);
};

extern CPong_grid *pong_grig;