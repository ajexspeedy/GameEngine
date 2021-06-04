#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);

		void Update();
		void Render();

		void SetCurrentScene(unsigned int currentScene);
		unsigned int GetCurrentSceneIndex() const;

		Scene* GetSceneByIndex(unsigned int scene);
		Scene* GetSceneByName(const std::string& name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		unsigned int m_CurrentScene{};
	};
}
