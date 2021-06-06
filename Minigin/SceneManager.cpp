#include "ImposterPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_Scenes[m_CurrentScene]->Update();
	//for(auto& scene : m_Scenes)
	//{

	//	scene->Update();
	//}
}

void dae::SceneManager::Render()
{
	m_Scenes[m_CurrentScene]->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

void dae::SceneManager::SetCurrentScene(unsigned int currentScene)
{
	if (static_cast<size_t>(m_CurrentScene) < m_Scenes.size())
	{
		m_CurrentScene = currentScene;
	}
}

unsigned int dae::SceneManager::GetCurrentSceneIndex() const
{
	return m_CurrentScene;
}

dae::Scene* dae::SceneManager::GetSceneByIndex(unsigned int scene)
{
	return m_Scenes[scene].get();
}

unsigned int dae::SceneManager::GetSceneByName(const std::string& name)
{
	for (size_t i{ 0 };i<m_Scenes.size();i++)
	{
		if (m_Scenes[i]->GetName() == name)
		{
			return static_cast<unsigned int>(i);
		}
	}
	std::cout << "Error GetSceneByName: name invalid" << std::endl;

	return 0;
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	m_CurrentScene = static_cast<int>(m_Scenes.size());
	auto scene = std::shared_ptr<Scene>(new Scene(name,m_CurrentScene));

	m_Scenes.push_back(scene);
	return scene.get();
	
}
