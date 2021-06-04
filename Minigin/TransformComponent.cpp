#include "ImposterPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pParent, const float x, const float y, const float z) :
	Component{ pParent },
	m_Transform{ x,y,z }
{

}

void dae::TransformComponent::Update()
{

}

void dae::TransformComponent::SetPosition(const float x, const float y)
{

	SetPosition(x, y, 0.f);
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{

	m_Transform.SetPosition(x, y, z);
}

void dae::TransformComponent::Translate(const float x, const float y)
{
	Translate(x, y, 0.f);
}

void dae::TransformComponent::Translate(const float x, const float y, const float z)
{
	auto curPos = m_Transform.GetPosition();
	float newX = curPos.x + x;
	float newY = curPos.y + y;
	float newZ = curPos.z + z;

	m_Transform.SetPosition(newX, newY, newZ);
}

glm::vec3 dae::TransformComponent::GetPosition() const
{
	return m_Transform.GetPosition();
}
