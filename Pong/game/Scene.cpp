#include "Scene.h"
#include "game/GameObject.h"

namespace sbt
{
	Scene::~Scene()
	{
		m_storage.clear();
		m_storage.shrink_to_fit();
	}

	Scene::Storage Scene::getStorage() const
	{
		return m_storage;
	}
}