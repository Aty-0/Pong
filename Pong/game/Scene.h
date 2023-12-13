#pragma once
#include "core/common.h"

namespace sbt
{
	class GameObject;
	class SceneManager;
	class Scene
	{
		Scene() = default;
		~Scene();

		// TODO: uuid will be better 
		using Storage = std::vector<std::pair<std::pair<std::string, std::int32_t>, GameObject*>>;
		
		[[nodiscard]] Storage getStorage() const;
		friend SceneManager;
	private:
		Storage m_storage;
	};
}