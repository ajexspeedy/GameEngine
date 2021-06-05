#include "ImposterPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pParent, const float x, const float y, const float w, const float h) :
	Component{ pParent },
	m_Transform{ x,y,0.f },
	m_Width{ w },
	m_Height{ h }
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

glm::vec2 dae::TransformComponent::GetSize() const
{
	return glm::vec2{ m_Width,m_Height };
}

glm::vec4 dae::TransformComponent::GetRect() const
{
	return glm::vec4{ m_Transform.GetPosition().x,m_Transform.GetPosition().y ,m_Width,m_Height };
}

void dae::TransformComponent::SetWidth(const float w)
{
	m_Width = w;
}

void dae::TransformComponent::SetHeight(const float h)
{
	m_Height = h;
}

void dae::TransformComponent::SetSize(const float w, const float h)
{
	m_Width = w;
	m_Height = h;
}
