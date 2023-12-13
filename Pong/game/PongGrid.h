#pragma once
#include "game/GameObject.h"

namespace sbt
{
	class PongGrid : public GameObject
	{
	public:
		PongGrid();
		~PongGrid();

		virtual void onRender(sf::RenderWindow& window) override;

	private:
		sf::Vertex m_line[2];
	};
}