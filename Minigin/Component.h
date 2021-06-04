#pragma once
#include "Subject.h"


namespace dae
{
	class GameObject;
	class Component :public Subject
	{
	public:



		Component(GameObject* pParent);
		virtual void Update() = 0;
		virtual void Render() const {}

		GameObject* GetParent() const;

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	private:
		GameObject* m_pParent;
	};
}
