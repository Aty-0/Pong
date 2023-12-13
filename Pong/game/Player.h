#pragma once
#include "core/common.h"
#include "game/GameObject.h"

namespace sbt
{
	class Player : public GameObject
	{
	public:
		Player();
		
		explicit Player(sf::Vector2<float> pos, sf::Vector2<float> size, float speed, 
			sf::Keyboard::Key up, sf::Keyboard::Key down);

		~Player();

		virtual void onUpdate(float deltaTime) override;
		virtual void onRender(sf::RenderWindow& window) override;
		virtual void onKeyPressed(sf::Event event) override;
		virtual void onKeyReleased(sf::Event event) override;
		
		void setAutoMode(bool autoMode);
		void checkInvisibleWallsCollision();
		void updateMovement(float deltaTime);

		void addScore();
		[[nodiscard]] std::int32_t getScore() const;
	private:
		sf::RectangleShape  m_body;
		std::int32_t		m_score;
	
		bool m_walk_up;
		bool m_walk_down;
		bool m_auto;

		sf::Keyboard::Key* m_keys;
	
	};
}