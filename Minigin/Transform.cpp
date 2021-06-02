#include "ImposterPCH.h"
#include "Transform.h"

dae::Transform::Transform(const float x, const float y, const float z):
	m_Position{x,y,z}
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
