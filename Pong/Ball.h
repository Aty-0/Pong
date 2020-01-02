//===================Ball.h========================
// Purpose:		Logic, Check on collision and adding player points
//
//=================================================

#pragma once
#include "Game.h"
//Class of ball
//Logic

class CBall
{
public:
	CBall();
	virtual ~CBall();
	virtual void UpdateBallStats();
	virtual void DetectCollision();
	virtual void Reset();
	virtual void OnUpdate();
	virtual void OnRender(RenderWindow &window);
	//Ball stats
	RectangleShape m_Ball;
	float m_Ball_PositionX;
	float m_Ball_PositionY;
	float m_Ball_ScaleX;
	float m_Ball_ScaleY;
	float m_Ball_Speed;
	float m_Ball_Angle;
	float m_Ball_SizeX;
	float m_Ball_SizeY;
	Color m_Ball_Color;
	bool m_Ball_Draw;

	//Ball stats

	virtual void UpdateGlobalBounds();
	FloatRect m_Ball_Rect;

	//Pass Logic
	float m_Pass_PosY;
	//Push| Push need for push ball to up or down
	enum m_Push_Status
	{
		Lift_Up,
		Put_Down,
	};
	m_Push_Status m_Push;
	//Push
	//Pause
	float m_Pass_Pause_Time;
	float m_Pass_Pause_Default_Time;
	bool m_Pass_Pause;

	//to whom pass ball
	int m_Pass_Player;
	int m_Pass_Scored;
	virtual void RandomPassBall();
	virtual void PassBall();
	//Pass Logic
};

extern CBall *ball;