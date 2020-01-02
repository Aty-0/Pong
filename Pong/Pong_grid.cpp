//===================Pong_grid.cpp=======================
// Purpose:			Grid
//
//=======================================================

#include "Pong_grid.h"

CPong_grid::CPong_grid()
{
	logger->Print("Load Pong Grid", logger->Debug);
	line[0].position = sf::Vector2f(400.0f, 0.0f);
	line[0].color = sf::Color::White;
	line[1].position = sf::Vector2f(400.0f, float(game->m_WindowWidth));
	line[1].color = sf::Color::White;
}

CPong_grid::~CPong_grid()
{
	logger->Print("Pong Grid unloaded", logger->Debug);
}

void CPong_grid::OnRender(RenderWindow &window)
{
	window.draw(line, 2, LinesStrip);
}