#include "ImposterPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "InputManager.h"
#include "PlayerComponent.h"


using namespace dae;

GameObject::GameObject(Component* component, const std::string& objectName)
{
	AddComponent(component);
	SetObjectName(objectName);
}



GameObject::~GameObject()
{
	for (Component* pComponent : m_pComponents)
	{
		if (pComponent)
		{
			delete pComponent;
			pComponent = nullptr;
		}
	}
}


void GameObject::Update()
{

	UpdateComponents();
}

void GameObject::Render() const
{

	for(auto* component : m_pComponents)
	{
		component->Render();
	}
}

void GameObject::SetTexture(const std::string& filename)
{
	if (GetComponent<RenderComponent>() != nullptr)
		GetComponent<RenderComponent>()->SetTexture(filename);

}

void GameObject::SetPosition(float x, float y)
{
	if (GetComponent<RenderComponent>() != nullptr)
		GetComponent<RenderComponent>()->SetPosition(x, y);
	if (GetComponent<TextComponent>() != nullptr)
		GetComponent<TextComponent>()->SetPosition(x, y);

}

void GameObject::SetObjectName(const std::string& name)
{
	m_ObjectName = name;
}

bool GameObject::AddComponent(Component* component)
{

	m_pComponents.push_back(component);
	return true;
}

void GameObject::UpdateComponents()
{
	for (auto& component : m_pComponents)
	{
		

		component->Update();
	}
}

std::string GameObject::GetObjectName() const
{
	return m_ObjectName;
}



std::vector <Component*> GameObject::GetComponents() const
{
	return m_pComponents;
}




//
//dae::RenderComponent* dae::GameObject::GetRenderComponent() const
//{
//	for (auto& component : m_pComponents)
//	{
//		if (dynamic_cast<RenderComponent*>(component.get()))
//			return dynamic_cast<RenderComponent*>(component.get());
//	}
//	return nullptr;
//}
//
//dae::TextComponent* dae::GameObject::GetTextComponent() const
//{
//	for (auto& component : m_pComponents)
//	{
//		if (dynamic_cast<TextComponent*>(component.get()))
//			return dynamic_cast<TextComponent*>(component.get());
//	}
//	return nullptr;
//}
//
//dae::PlayerComponent* dae::GameObject::GetPlayerComponent() const
//{
//	for (auto& component : m_pComponents)
//	{
//		if (dynamic_cast<PlayerComponent*>(component.get()))
//			return dynamic_cast<PlayerComponent*>(component.get());
//	}
//	return nullptr;
//}
