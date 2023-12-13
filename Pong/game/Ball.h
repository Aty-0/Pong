#pragma once
#include "GameObject.h"

namespace sbt
{
	class Player;
	class Ball : public GameObject
	{
	private:
		enum MovementDirection
		{
			Up,
			Down,
		};
	public:
		Ball();
		~Ball();
		
		// Note:
		// Can be added only two players
		// Needed for updating them scores
		void addPlayer(Player* p);

		virtual void onDetectCollision() override;
		virtual void onUpdate(float deltaTime) override;

	private:
		void reset();
		void randomPassBall();
		void passBall();
		
		MovementDirection m_movement;
		float m_passTime;
		const float m_passStartTime;
		bool  m_passPause;
		bool  m_passPlayer;
		Player* m_players[2];
		
	};
}
