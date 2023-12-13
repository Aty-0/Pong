#pragma once
#include "common.h"

#define GAME_VERSION "2.0 (aka small refactoring)"


namespace sbt
{
	class SceneManager;

	class Game : public sbt::Singleton<Game>
	{
	public:
		Game();
		~Game();

		void destroy();
		void createGame();
		void loadGame(sf::RenderWindow& window);
		void onRender(sf::RenderWindow& window);
		void onUpdate(sf::RenderWindow& window);
		void updateEvent(sf::RenderWindow& window);
		void onExit(sf::RenderWindow& window);
		void createWindow();
		void calculateDeltaTime();
		[[nodiscard]] std::int32_t getWidth() const;
		[[nodiscard]] std::int32_t getHeight() const;
		[[nodiscard]] float	getDeltaTime() const;
		[[nodiscard]] bool isPaused() const;

	private:
		SceneManager* m_sc;

		sf::RenderWindow m_window;
		sf::VideoMode	m_VideoMode;
		std::int32_t			m_WindowWidth = 1280;
		std::int32_t			m_WindowHeight = 768;
		std::int32_t			m_WindowPosX = 300;
		std::int32_t			m_WindowPosY = 300;
		std::int32_t  m_FrameRateLimit = 60;
		std::int32_t  m_VSync = 0;
		bool m_FullScreen = false;
		bool m_MouseVisible = false;

		sf::Color m_Background_Color = sf::Color::Black;

		sf::Clock	m_clock;
		float		m_delta_time;

		bool m_isPaused;
	};
}