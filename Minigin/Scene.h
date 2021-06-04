#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include <deque>
namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:

		void Add(GameObject* object);
		
		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void PushObjectFront(GameObject* pObject);
		void PushObjectBack(GameObject* pObject);

		std::string GetName() const;
		unsigned int GetSceneNumber() const;

	private: 
		explicit Scene(const std::string& name, const unsigned int sceneNumber);

		std::string m_Name;
		std::deque<GameObject*> m_pObjects;

		unsigned int m_SceneNumber;

		static unsigned int m_IdCounter; 
	};

}
