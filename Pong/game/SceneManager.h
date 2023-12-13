#pragma once
#include "Scene.h"
#include "core/Logger.h"

namespace sbt
{
	class SceneManager : public sbt::Singleton<SceneManager>
	{
	public:
		SceneManager();
		~SceneManager();

		void createNewScene();
		void setScene(Scene* scene);
		void render(sf::RenderWindow& window);
		void update(float deltaTime);
		void keyPressed(sf::Event event);
		void keyReleased(sf::Event event);

		template<typename T>
		void createGameObject(std::string name);

		template<typename T>
		void addGameObject(T* go, std::string name);

		template<typename T>
		T* getGameObjectByName(std::string name);

		Scene* getScene() const;
	private:
		Scene* m_scene;
		std::int32_t m_FIXME_id;
	};

	template<typename T>
	inline void SceneManager::createGameObject(std::string name)
	{
		SBT_ASSERT(m_scene);
		VERB("SceneManager::createGameObject %s", name.c_str());
		m_FIXME_id++;
	}

	template<typename T>
	inline void SceneManager::addGameObject(T* go, std::string name)
	{
		SBT_ASSERT(m_scene);
		SBT_ASSERT(go != nullptr);
		VERB("SceneManager::addGameObject %s", name.c_str());

		m_FIXME_id++;
		m_scene->m_storage.push_back(std::make_pair(std::make_pair(name,m_FIXME_id), go));
	}

	template<typename T>
	inline T* SceneManager::getGameObjectByName(std::string name)
	{
		SBT_ASSERT(m_scene);
		try
		{
			auto storage = m_scene->m_storage;
			for (auto it = storage.begin(); it != storage.end(); it++)
			{
				if (it->first.first == name)
				{
					return dynamic_cast<T*>(it->second);
				}

			}

			// We are check all objects...
			throw std::out_of_range("No object found");
		}
		catch (std::out_of_range)
		{
			VERB("scene_manager::get_game_object_name Error: Trying to get object %s but it is not exist", name.c_str());
		}

		return nullptr;
	}
}