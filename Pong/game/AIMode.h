#pragma once
#include "core/common.h"

namespace sbt
{
	class Player;
	class Ball;

	class AIMode
	{
	public:
		AIMode();
		~AIMode();
		void regenerateFault();
		void onUpdate(float deltaTime);
		
		void setPlayer(Player* player);

	private:

		float	 m_fault;
		float	 m_time;
		const float	 m_maxTime;
		bool	 m_onSpawnPoint;
		bool	 m_noFault;
		Player*  m_player;	
		Ball*    m_ball;
	};
}