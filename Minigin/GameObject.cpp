#include "ImposterPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "InputManager.h"
#include "PlayerComponent.h"




dae::GameObject::GameObject(std::shared_ptr<Component>component, const std::string& objectName)
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

	for(std::shared_ptr<Component> component : m_pComponents)
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

bool dae::GameObject::AddComponent(std::shared_ptr<Component> component)
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



std::vector < std::shared_ptr<dae::Component> > dae::GameObject::GetComponents() const
{
	return m_pComponents;
}





dae::RenderComponent* dae::GameObject::GetRenderComponent() const
{
	for (auto& component : m_pComponents)
	{
		if (dynamic_cast<RenderComponent*>(component.get()))
			return dynamic_cast<RenderComponent*>(component.get());
	}
	return nullptr;
}

dae::TextComponent* dae::GameObject::GetTextComponent() const
{
	for (auto& component : m_pComponents)
	{
		if (dynamic_cast<TextComponent*>(component.get()))
			return dynamic_cast<TextComponent*>(component.get());
	}
	return nullptr;
}

dae::PlayerComponent* dae::GameObject::GetPlayerComponent() const
{
	for (auto& component : m_pComponents)
	{
		if (dynamic_cast<PlayerComponent*>(component.get()))
			return dynamic_cast<PlayerComponent*>(component.get());
	}
	return nullptr;
}
