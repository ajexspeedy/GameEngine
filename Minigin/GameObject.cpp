#include "ImposterPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"


using namespace dae;

GameObject::GameObject(const std::string& objectName, int activeLevel) :
	m_ActiveLevel{ activeLevel }
{
	if (m_ActiveLevel == -1)
		m_IsActive = true;
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

	for (auto* component : m_pComponents)
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

bool dae::GameObject::IsPushToFront() const
{
	return m_PushToFront;
}

void dae::GameObject::SetPushToFront(bool pushToFront)
{
	m_PushToFront = pushToFront;
}

bool dae::GameObject::IsPushToBack() const
{
	return m_PushToBack;
}

void dae::GameObject::SetPushToBack(bool pushToBack)
{
	m_PushToBack = pushToBack;
}

bool dae::GameObject::GetIsActive() const
{

	return m_IsActive;
}

void dae::GameObject::SetActive(bool active)
{
	m_IsActive = active;
}
int dae::GameObject::GetActiveLevel() const
{
	return m_ActiveLevel;
}

void dae::GameObject::SwapIfActive(int active)
{
	std::cout << active << std::endl;
 	if (m_ActiveLevel == active || m_ActiveLevel == -1)
	{
		m_IsActive = true;
	}
	else
	{
		m_IsActive = false;
	}
}



std::string dae::GameObject::GetName() const
{
	return m_ObjectName;
}




