#include "SceneManager.h"
#include "game/GameObject.h"

namespace sbt
{
	SceneManager::SceneManager() : 
		m_FIXME_id(0),
		m_scene(nullptr)
	{
		createNewScene();
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE(m_scene);
	}

	void SceneManager::keyPressed(sf::Event event)
	{
		if (m_scene)
		{
			for (const auto it : m_scene->m_storage)
			{
				it.second->keyPressed(event);
			}
		}
	}

	void SceneManager::keyReleased(sf::Event event)
	{
		if (m_scene)
		{
			for (const auto it : m_scene->m_storage)
			{
				it.second->keyReleased(event);
			}
		}
	}

	void SceneManager::render(sf::RenderWindow& window)
	{
		if (m_scene)
		{
			for (const auto it : m_scene->m_storage)
			{
				it.second->render(window);
			}
		}
	}

	void SceneManager::update(float deltaTime)
	{
		if (m_scene)
		{
	
			for (const auto it : m_scene->m_storage)
			{
				it.second->update(deltaTime);

				for (const auto it2 : m_scene->m_storage)
					it.second->detectCollision(it2.second);
	
			}
		}
	}

	Scene* SceneManager::getScene() const
	{
		return m_scene;
	}

	void SceneManager::createNewScene()
	{
		VERB("SceneManager::createNewScene");

		m_scene = new Scene();
	}

	void SceneManager::setScene(Scene* scene)
	{
		VERB("SceneManager::setScene");

		m_scene = scene;
	}
}