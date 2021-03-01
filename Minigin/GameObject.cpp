#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "InputManager.h"
#include "PlayerComponent.h"




dae::GameObject::GameObject(Component* component, const std::string& objectName)
{
	AddComponent(component);
	SetObjectName(objectName);
}


void dae::GameObject::Update()
{

	UpdateComponents();
}

void dae::GameObject::Render() const
{
	//if(GetRenderComponent())
	//	GetRenderComponent()->Render();
	//if (GetTextComponent())
	//	GetTextComponent()->Render();
	//if (GetPlayerComponent())
	//	GetPlayerComponent()->Render();
	for(auto component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	if (GetRenderComponent() != nullptr)
		GetRenderComponent()->SetTexture(filename);

}

void dae::GameObject::SetPosition(float x, float y)
{
	if (GetRenderComponent() != nullptr)
		GetRenderComponent()->SetPosition(x, y);
	if (GetTextComponent() != nullptr)
		GetTextComponent()->SetPosition(x, y);

}

void dae::GameObject::SetObjectName(const std::string& name)
{
	m_ObjectName = name;
}

bool dae::GameObject::AddComponent(Component* component)
{

	m_pComponents.push_back(component);
	return true;
}

void dae::GameObject::UpdateComponents()
{
	for (auto& component : m_pComponents)
	{
		

		component->Update();
	}
}

std::string dae::GameObject::GetObjectName() const
{
	return m_ObjectName;
}



std::vector<dae::Component*> dae::GameObject::GetComponents() const
{
	return m_pComponents;
}


dae::GameObject::~GameObject()
{
	for (auto& component : m_pComponents)
	{
		if (component)
		{
			delete component;
			component = nullptr;
		}
	}
}


dae::RenderComponent* dae::GameObject::GetRenderComponent() const
{
	for (auto& component : m_pComponents)
	{
		if (dynamic_cast<RenderComponent*>(component))
			return dynamic_cast<RenderComponent*>(component);
	}
	return nullptr;
}

dae::TextComponent* dae::GameObject::GetTextComponent() const
{
	for (auto& component : m_pComponents)
	{
		if (dynamic_cast<TextComponent*>(component))
			return dynamic_cast<TextComponent*>(component);
	}
	return nullptr;
}

dae::PlayerComponent* dae::GameObject::GetPlayerComponent() const
{
	for (auto& component : m_pComponents)
	{
		if (dynamic_cast<PlayerComponent*>(component))
			return dynamic_cast<PlayerComponent*>(component);
	}
	return nullptr;
}
