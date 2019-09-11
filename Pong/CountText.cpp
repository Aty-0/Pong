//===================CountText.cpp=====================
// Purpose:			Count Text
//
//=====================================================


#include "CountText.h"
#include "Player.h"
#include "Ball.h"

CCountText::CCountText()
{
	logger->Print("Load count text", logger->Debug);
	CREATE_TEXT(CountText, 16, Default_Font, Color::White, 5, 10, "");
}

void CCountText::OnRender(RenderWindow &window)
{
	CountText.setString(std::to_string(p1->m_Player_Count) + " : " + std::to_string(p2->m_Player_Count));
	window.draw(CountText);
}