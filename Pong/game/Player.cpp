#include "Player.h"
#include "AIMode.h"
#include "core/Game.h"

namespace sbt
{
	Player::Player()
	{
		// Template player example 
		createDrawableWithType<sf::RectangleShape>();
		
		setPosition({0,0});
		setScale({ 1,1 });
		setSize({1,1});
		setSpeed(1);

		m_score = 0;

		m_keys = new sf::Keyboard::Key[2];

		m_keys[0] = sf::Keyboard::Key::W;
		m_keys[1] = sf::Keyboard::Key::A;
	}

	Player::Player(sf::Vector2<float> pos, sf::Vector2<float> size, float speed, sf::Keyboard::Key up, sf::Keyboard::Key down)
	{		
		createDrawableWithType<sf::RectangleShape>();
		
		setPosition(pos);
		setScale({1,1});
		setSize(size);
		setSpeed(speed);
		m_score = 0;
		
		m_keys = new sf::Keyboard::Key[2];

		m_keys[0] = up;
		m_keys[1] = down;

		m_ai = new AIMode();
		m_ai->setPlayer(this);
	}

	Player::~Player()
	{

	}

	void Player::updateMovement(float deltaTime)
	{
		auto position = getPosition();
		auto speed = getSpeed();

		if (m_walk_up == true)
		{
			setPosition({ position.x, position.y - speed * deltaTime });
		}
		else if (m_walk_down == true)
		{
			setPosition({ position.x, position.y + speed * deltaTime });
		}
	}

	void Player::checkInvisibleWallsCollision()
	{
		static const auto game = sbt::Game::getInstance();

		// TODO: Fullscreen rect will be better 
		auto position = getPosition();
		if (position.y >= game->getHeight() - 100.0f)
		{
			setPosition({ position.x, game->getHeight() - 100.0f });
			m_walk_up = false;
			m_walk_down = false;
		}
		if (position.y <= 0.0f)
		{
			setPosition({ position.x, 5.0f });
		
			m_walk_up = false;
			m_walk_down = false;
		}
	}

	void Player::onKeyPressed(sf::Event event)
	{
		static const auto game = sbt::Game::getInstance();
		if (game->isPaused())
			return;

		if (!m_auto)
		{
			if(event.key.code == m_keys[0])
				m_walk_up = true;
			else if(event.key.code == m_keys[1])
				m_walk_down = true;
		}
	}

	void Player::onKeyReleased(sf::Event event)
	{
		static const auto game = sbt::Game::getInstance();
		if (game->isPaused())
			return;

		if (!m_auto)
		{
			if (event.key.code == m_keys[0])
				m_walk_up = false;
			else if (event.key.code == m_keys[1])
				m_walk_down = false;
		}
	}

	void Player::setAutoMode(bool autoMode)
	{
		m_auto = autoMode;
	}

	void Player::onUpdate(float deltaTime)
	{
		static const auto game = Game::getInstance();
		if (game->isPaused())
			return;

		updateMovement(deltaTime);
		checkInvisibleWallsCollision();
		if (m_auto)
		{
			m_ai->onUpdate(deltaTime);
		}
	}

	void Player::onRender(sf::RenderWindow& window)
	{
		// lol, nothing...
	}

	void Player::addScore()
	{
		m_score++;
	}

	bool Player::getAutoMode() const
	{
		return m_auto;
	}

	std::int32_t Player::getScore() const
	{
		return m_score;
	}
}