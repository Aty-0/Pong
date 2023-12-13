#include "Ball.h"
#include "game/Player.h"
#include "core/Game.h"
#include "core/SoundLoader.h"
#include "core/Logger.h"

namespace sbt
{
	Ball::Ball() :
		m_passPlayer(false),
		m_movement(),
		m_passTime(0.0f),
		m_passPause(true),
		m_passStartTime(5.0f)
	{
		createDrawableWithType<sf::RectangleShape>();

		setPosition({ 0,0 });
		setScale({ 1,1 });
		setSize({ 10.0f, 10.0f });
		setSpeed(200.0f);

		randomPassBall();

	}

	Ball::~Ball()
	{

	}
	void Ball::addPlayer(Player* p)
	{
		static auto arr_size = 0;
		if (arr_size == 2 
			|| p == nullptr)
			return;
		
		m_players[arr_size] = p;
		arr_size++;
	}

	void Ball::reset()
	{
		VERB("Ball::reset");
		m_passTime = m_passStartTime;
		m_passPause = true;

		setDraw(false);
		passBall();
	}

	void Ball::randomPassBall()
	{
		VERB("Ball::randomPassBall");
		m_passPlayer = static_cast<bool>(std::rand() % 1);
		passBall();
	}

	void Ball::passBall()
	{
		VERB("Ball::passBall");
		m_passPlayer = m_passPlayer == 1 ? 0 : 1;

		static const auto game = sbt::Game::getInstance();
		
		// Generate random Y coord
		const auto y = std::rand() % game->getHeight() - 50.0f;
		// Set new movement 
		m_movement  = y >= game->getHeight() / 2 ? Ball::MovementDirection::Down : Ball::MovementDirection::Up;
		// Set ball position
		setPosition({ game->getWidth() / 2.0f,  y});		
	}

	void Ball::onDetectCollision()
	{
		auto position = getPosition();
		if (m_passPlayer == 0)
			setPosition({ position.x - 10.0f , position.y });
		else if (m_passPlayer == 1)
			setPosition({ position.x + 10.0f , position.y });

		m_passPlayer = m_passPlayer == 0 ? 1 : 0;
		
		VERB("m_passPlayer%i", m_passPlayer);
		static const auto sl = SoundLoader::getInstance();
		sl->playSound("Ball_Hitted", 5.0f, 1.0f, false);
	}

	void Ball::onUpdate(float deltaTime)
	{
		static const auto sl = SoundLoader::getInstance();
		// FIX ME: 
		static const auto game = sbt::Game::getInstance();
		if (game->isPaused())
			return;

		if (!m_passPause)
		{
			auto position = getPosition();
			const auto speed = getSpeed();

			// Movement by Y coord
			if (m_movement == Ball::MovementDirection::Up)
				position.y += speed * deltaTime;
			else if (m_movement == Ball::MovementDirection::Down)
				position.y -= speed * deltaTime;				
			
			// Movement by X coord
			if (m_passPlayer == 0)
				position.x += speed * deltaTime;
			else if (m_passPlayer == 1)
				position.x -= speed * deltaTime;

			// Set our position 
			setPosition({ position.x, position.y});
			
			// Check collision with screen bounds
			if (position.y <= 0)
			{
				sl->playSound("Ball_Hitted", 5.0f, 1.0f, false);
				m_movement = Ball::MovementDirection::Up;

				// Needed for protect ball for doesn't go out of screen 
				setPosition({ position.x,  1.0f });
			}
			else if (position.y >= game->getHeight())
			{
				sl->playSound("Ball_Hitted", 5.0f, 1.0f, false);
				m_movement = Ball::MovementDirection::Down;

				// Needed for protect ball for doesn't go out of screen 
				setPosition({ position.x,  game->getHeight() - 1.0f});
			}

			// If ball position by x is out of bounds we are check 
			// What's a part of screen is it.
			if (position.x >= game->getWidth())
			{
				sl->playSound("Ball_Scored", 10.0f, 1.0f, false);
				m_players[0]->addScore();
				m_passPlayer = 0;
				reset();
			}
			else if (position.x <= 0)
			{
				sl->playSound("Ball_Scored", 10.0f, 1.0f, false);
				m_players[1]->addScore();
				m_passPlayer = 1;
				reset();
			}
		}
		else
		{
			m_passTime -= 7.0f * deltaTime;

			if (m_passTime <= 0.0f)
			{
				sl->playSound("Ball_Created", 5.0f, 1.0f, false);

				m_passPause = false;
				setDraw(true);
				m_passTime = m_passStartTime;
			}
		}
	}

}
