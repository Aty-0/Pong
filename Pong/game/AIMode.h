#pragma once
#include "core/common.h"

namespace sbt
{
	class AIMode
	{
	public:
		void regenerateFault();
		void onUpdate(float deltaTime);

	private:
		bool m_AIMode_Work;
		bool m_AIMode_NoFault;
		int m_AI_Fault;
		int m_AI_Max_Fault;
		float m_TimeRegenerateFault = 5.0f;
		bool m_AI_OnSpawnPoint;

	};
}