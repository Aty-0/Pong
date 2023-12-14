#pragma once
#include "common.h"

#define GAME_VERSION "2.0.1 (aka small refactoring upd =3=)"


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
		void calculateFps();

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
		std::int32_t			m_WindowPosX = 0;
		std::int32_t			m_WindowPosY = 0;
		std::int32_t  m_FrameRateLimit = 0;
		std::int32_t  m_VSync = 0;
		bool m_FullScreen = false;
		bool m_MouseVisible = false;

		sf::Color m_Background_Color = sf::Color::Black;

		sf::Clock	m_clock;
		sf::Clock	m_clockFps;
		float		m_delta_time;
		std::uint32_t m_frames;
		std::uint32_t m_fps;

		bool m_isPaused;
	};
}