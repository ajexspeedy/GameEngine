#pragma once
#include "SceneObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include <memory>
#include <vector>

namespace dae
{
	

	class PlayerComponent;
	class Texture2D;
	class Component;
	class GameObject final
	{
	public:
		GameObject(const std::string& objectName,int activeScene);
		~GameObject();
		
		void Update();
		void Render()const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void SetObjectName(const std::string& name);

		bool AddComponent(Component* component);
		void UpdateComponents();
		std::string GetObjectName() const;

		
		std::vector<Component*> GetComponents() const;
		
		template <typename ComponentType>
		inline ComponentType* GetComponent() const
		{
			for (Component* component : m_pComponents)
			{
				if (typeid(*component) == typeid(ComponentType))
				{
					return static_cast<ComponentType*>(component);
				}
			}
			return nullptr;
		}

		template <typename ComponentType>
		inline bool HasComponent() const
		{
			for (Component* component : m_pComponents)
			{
				if (typeid(*component) == typeid(ComponentType))
				{
					return true;
				}
			}
			return false;
		}

		GameObject() = default;
	
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		bool IsPushToFront() const;
		void SetPushToFront(bool pushToFront);

		bool IsPushToBack() const;
		void SetPushToBack(bool pushToBack);

		bool GetIsActive() const;
		int GetActiveLevel() const;
		void SwapIfActive(int active);

		std::string GetName() const;
	private:
		std::vector<Component*> m_pComponents = {};
		std::string m_ObjectName{"Default"};
		float m_FPSCooldown = 0.f;
		bool m_PushToFront, m_PushToBack, m_IsActive;
		int m_ActiveLevel;
	};
	
}
