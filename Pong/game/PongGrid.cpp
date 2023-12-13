#include "PongGrid.h"
#include "core/Game.h"

namespace sbt
{
	PongGrid::PongGrid()
	{
		const auto game = Game::getInstance();
		const auto middleScreen = static_cast<float>(game->getWidth()) / 2;

		m_line[0].position = sf::Vector2f(middleScreen, 0.0f);
		m_line[0].color = sf::Color::White;
		m_line[1].position = sf::Vector2f(middleScreen, static_cast<float>(game->getHeight()));
		m_line[1].color = sf::Color::White;
	}

	PongGrid::~PongGrid()
	{

	}

	void PongGrid::onRender(sf::RenderWindow& window)
	{
		window.draw(m_line, 2, sf::LinesStrip);
	}
}