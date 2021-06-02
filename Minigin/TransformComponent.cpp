#include "ImposterPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pParent, float x, float y, float z) :
	Component{ pParent },
	m_Transform{ x,y,z }
{

}

void dae::TransformComponent::Update()
{

}

void dae::TransformComponent::SetPosition(float x, float y)
{
	SetPosition(x, y, 0.f);
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}

glm::vec3 dae::TransformComponent::GetPosition() const
{
	return m_Transform.GetPosition();
}
