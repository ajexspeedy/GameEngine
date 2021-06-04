#include "ImposterPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"


using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (auto& object : m_pObjects)
	{

		delete object;
		object = nullptr;
	}
}




void dae::Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}

void Scene::Update()
{
	for (auto& object : m_pObjects)
	{
		if (object->IsPushToFront())
		{
			PushObjectFront(object);
			continue;
		}
		if (object->IsPushToBack())
		{
			PushObjectBack(object);
			continue;
		}
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Scene::PushObjectFront(GameObject* pObject)
{
	auto iterator = std::find(m_pObjects.begin(), m_pObjects.end(), pObject);
	if (iterator != m_pObjects.end())
	{
		m_pObjects.erase(iterator);
		m_pObjects.push_front(pObject);
		pObject->SetPushToFront(false);

	}

}

void dae::Scene::PushObjectBack(GameObject* pObject)
{
	auto iterator = std::find(m_pObjects.begin(), m_pObjects.end(), pObject);
	if (iterator != m_pObjects.end())
	{
		m_pObjects.erase(iterator);
		m_pObjects.push_back(pObject);
		pObject->SetPushToBack(false);

	}

}
