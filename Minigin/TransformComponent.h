#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* pParent, float x = 0.f, float y = 0.f, float z = 0.f);
		virtual ~TransformComponent() = default;
	

		virtual void Update() override;
	
		void SetPosition(float x, float y);
		void SetPosition(float x, float y, float z);

		glm::vec3 GetPosition() const;
		
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;
		
	protected:
		Transform m_Transform;
		
	};
}
