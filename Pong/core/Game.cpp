#include "Game.h"
#include "core/Logger.h"
#include "core/SoundLoader.h"
#include "game/SceneManager.h"



#include "game/Ball.h"
#include "game/PongGrid.h"
#include "game/UIText.h"
#include "game/Player.h"

#include "game/Fonts.h"
#include "game/AIMode.h"

namespace sbt
{
	Game::Game() : m_isPaused(false)
	{

	}


	Game::~Game()
	{

	}

	void Game::destroy()
	{

	}

	void Game::createWindow()
	{
		INFO("Create Window...");
		// Set video mode for window
		m_VideoMode.width = m_WindowWidth;
		m_VideoMode.height = m_WindowHeight;
		m_VideoMode.bitsPerPixel = 32;
		
		if (m_FullScreen == true)
		{
			m_VideoMode.getFullscreenModes();
			m_window.create(m_VideoMode, "Pong", sf::Style::None | sf::Style::Fullscreen);
		}
		else
		{
			m_VideoMode.getDesktopMode();
			m_window.create(m_VideoMode, "Pong", sf::Style::Titlebar | sf::Style::Close);
			m_window.setPosition(sf::Vector2i(m_WindowPosX, m_WindowPosY));
		}

		m_window.setFramerateLimit(m_FrameRateLimit);
		m_window.setMouseCursorVisible(m_MouseVisible);
		m_window.setVerticalSyncEnabled(m_VSync);
	}

	void Game::calculateDeltaTime()
	{
		m_delta_time = m_clock.getElapsedTime().asMicroseconds() / 1000000.0f;
		m_clock.restart();
	}

	void Game::createGame()
	{
		createWindow();
		loadGame(m_window);
		
		while (m_window.isOpen())
		{
			calculateDeltaTime();
			updateEvent(m_window);
			onUpdate(m_window);
			onRender(m_window);
		}
	}

	void Game::loadGame(sf::RenderWindow& window)
	{
		INFO("Load game...");
		
		const auto fonts = Fonts::getInstance();
		fonts->loadFontFromFile("Gamedata/Fonts/immortal.ttf", "default");
		const auto sl = SoundLoader::getInstance();

		sl->loadSound("Ball_Hitted", "Gamedata/Sounds/Ball_Hitted.wav");
		sl->loadSound("Ball_Scored", "Gamedata/Sounds/Ball_Scored.wav");
		sl->loadSound("Ball_Created", "Gamedata/Sounds/Ball_Created.wav");
		sl->loadSound("Pause", "Gamedata/Sounds/Pause.wav");

		m_sc = SceneManager::getInstance();

		auto p1 = new Player({ 50.0f, m_WindowHeight / 2.0f }, { 15.0f, 100.0f, }, 460.0f, sf::Keyboard::W, sf::Keyboard::S);
		m_sc->addGameObject(p1, "p1");

		auto p2 = new Player({ m_WindowWidth - 50.0f , m_WindowHeight / 2.0f },
			{ 15.0f, 100.0f, }, 460.0f, sf::Keyboard::I, sf::Keyboard::K);
		m_sc->addGameObject(p2, "p2");
		
		auto score = new UIText();
		m_sc->addGameObject(score, "score_text");

		auto pauseText = new UIText();
		pauseText->setText("Paused");
		pauseText->setPosition({ (m_WindowWidth / 2.0f) - 50.0f, (m_WindowHeight / 2.0f) - 30.0f });
		pauseText->setFontSize(30.0f);
		pauseText->setDraw(false);

		m_sc->addGameObject(pauseText, "pause_text");

		auto ver_text = new UIText();
		ver_text->setText("Game version: " GAME_VERSION);
		ver_text->setPosition({ 20.0f, m_WindowHeight - 20.0f });
		ver_text->setFontSize(14.0f);
		ver_text->setColor({255, 255, 255, 100});
		ver_text->setDraw(false);

		m_sc->addGameObject(ver_text, "ver_text");

		auto grid = new PongGrid();
		m_sc->addGameObject(grid, "PongGrid");
		
		auto ball = new Ball();

		// Add players to update them scores
		ball->addPlayer(p1);
		ball->addPlayer(p2);
		
		m_sc->addGameObject(ball, "ball");
	}

	void Game::onRender(sf::RenderWindow& window)
	{
		window.clear(m_Background_Color);
		m_sc->render(window);
		window.display();
	}

	void Game::onUpdate(sf::RenderWindow& window)
	{
		m_sc->update(m_delta_time);


		// fix me:  lol 
		//		    bro use callbacks pls 
		const static auto scoreText = m_sc->getGameObjectByName<UIText>("score_text");
		const static auto p1 = m_sc->getGameObjectByName<Player>("p1");
		const static auto p2 = m_sc->getGameObjectByName<Player>("p2");

		if (scoreText)
			scoreText->setText(std::to_string(p1->getScore()) + ":" + std::to_string(p2->getScore()));
	}

	void Game::onExit(sf::RenderWindow& window)
	{
		window.close();
		destroy();
	}

	void Game::updateEvent(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				onExit(window);

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_isPaused = !m_isPaused;

					const static auto ver_text = m_sc->getGameObjectByName<UIText>("ver_text");
					const static auto pauseText = m_sc->getGameObjectByName<UIText>("pause_text");
					const static auto grid = m_sc->getGameObjectByName<PongGrid>("PongGrid");
					
					if(grid)
						grid->setDraw(!m_isPaused);

					if(ver_text)
						ver_text->setDraw(m_isPaused);

					if(pauseText)
						pauseText->setDraw(m_isPaused);
				}

				if (event.key.code == sf::Keyboard::Q)
				{
					if(m_isPaused)
						onExit(window);
				}

				m_sc->keyReleased(event);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				m_sc->keyPressed(event);
			}
		}
	}

	std::int32_t Game::getWidth() const
	{
		return m_WindowWidth;
	}

	std::int32_t Game::getHeight() const
	{
		return m_WindowHeight;
	}

	float Game::getDeltaTime() const
	{
		return m_delta_time;
	}

	bool Game::isPaused() const
	{
		return m_isPaused;
	}
}
