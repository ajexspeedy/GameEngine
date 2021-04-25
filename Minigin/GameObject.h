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
		GameObject(std::shared_ptr<Component> component,const std::string& objectName);
		
		
		void Update();
		void Render()const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void SetObjectName(const std::string& name);

		bool AddComponent(std::shared_ptr<Component> component);
		void UpdateComponents();
		std::string GetObjectName() const;

		
		std::vector<std::shared_ptr<Component>> GetComponents() const;
		

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<Component>> m_pComponents = {};
		std::string m_ObjectName{"Default"};
		RenderComponent* GetRenderComponent() const;
		TextComponent* GetTextComponent() const;
		PlayerComponent* GetPlayerComponent() const;
		float m_FPSCooldown = 0.f;
	};
}
