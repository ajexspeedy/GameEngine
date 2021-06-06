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
		TransformComponent(GameObject* pParent, const float x = 0.f, const float y = 0.f, const float w = -1.f, const float h = -1.f);
		virtual ~TransformComponent() = default;


		virtual void Update() override;

		void SetPosition(const float x, const float y);
		void SetPosition(const glm::vec2& position);
		void SetPosition(const float x, const float y, const float z);
		void Translate(const float x, const float y, const float z);
		void Translate(const float x, const float y);

		glm::vec3 GetPosition() const;
		glm::vec2 GetSize() const;
		glm::vec4 GetRect() const;

		void SetWidth(const float w);
		void SetHeight(const float h);
		void SetSize(const float w, const float h);

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

	protected:
		Transform m_Transform;
		float m_Width, m_Height;

	};
}
