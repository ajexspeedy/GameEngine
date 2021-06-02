#include "ImposterPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "InputManager.h"



using namespace dae;

GameObject::GameObject(const std::string& objectName)
{
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




