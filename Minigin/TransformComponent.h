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
		TransformComponent(GameObject* pParent,const float x = 0.f,const float y = 0.f,const float z = 0.f);
		virtual ~TransformComponent() = default;
	

		virtual void Update() override;
	
		void SetPosition(const float x, const float y);
		void SetPosition(const float x, const float y, const float z);
		void Translate(const float x, const float y, const float z);
		void Translate(const float x, const float y);

		glm::vec3 GetPosition() const;
		
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;
		
	protected:
		Transform m_Transform;
		
	};
}
