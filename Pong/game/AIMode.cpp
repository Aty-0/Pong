#include "AIMode.h"
#include "game/Ball.h"
#include "game/Player.h"
#include "core/Game.h"
#include "core/Logger.h"
#include "game/SceneManager.h"

namespace sbt
{
	AIMode::AIMode() : m_maxTime(15.0f)
	{
		regenerateFault();
	}
	
	AIMode::~AIMode()
	{

	}
	
	void AIMode::onUpdate(float deltaTime)
	{
		SBT_ASSERT(m_player);
		SBT_ASSERT(m_ball);

		if (!m_noFault)
		{
			m_time -= 4.0f * deltaTime;
			if (m_time <= 0.0f)
			{
				m_time = m_maxTime;
				regenerateFault();
			}
		}

		auto player_pos = m_player->getPosition();
		if (m_ball->m_passPause)
		{
			static const auto game = Game::getInstance();
			const auto height = game->getHeight();
			if (player_pos.y >= height / 2)
			{
				m_player->m_walk_up = true;
				m_player->m_walk_down = false;
			}
			else if (player_pos.y <= height / 2)
			{
				m_player->m_walk_up = false;
				m_player->m_walk_down = true;
			}
		}
		else
		{
			// Try to search Y ball position, if bot on player position his stop search
			auto ballYpos = m_ball->getPosition().y;
			if (player_pos.y == ballYpos)
				m_onSpawnPoint = true;
			else
				m_onSpawnPoint = false;
		
			if (m_onSpawnPoint == false)
			{
				if (player_pos.y >= ballYpos - m_fault)
				{
					m_player->m_walk_up = true;
					m_player->m_walk_down = false;

					//player_pos.y -= speed * deltaTime;
				}
				else if (player_pos.y <= ballYpos + m_fault)
				{
					m_player->m_walk_up = false;
					m_player->m_walk_down = true;

					//player_pos.y += speed * deltaTime;
				}
			}
		}

		m_player->setPosition(player_pos);
	}

	void AIMode::setPlayer(Player* player)
	{
		m_player = player;

		// FIX ME: Wierd
		//         And need to create ball first then player 
		//		   For this 
		m_ball = SceneManager::getInstance()->getGameObjectByName<Ball>("ball");
	}

	void AIMode::regenerateFault()
	{
		//VERB("AIMode::regenerateFault");

		m_fault = std::rand() % 200;
	}
}