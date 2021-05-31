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
	class GameObject final
	{
	public:
		GameObject(Component* component,const std::string& objectName);
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

		GameObject() = default;
	
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<Component*> m_pComponents = {};
		std::string m_ObjectName{"Default"};
	/*	RenderComponent* GetRenderComponent() const;
		TextComponent* GetTextComponent() const;
		PlayerComponent* GetPlayerComponent() const;*/
		float m_FPSCooldown = 0.f;
	};
	
}
