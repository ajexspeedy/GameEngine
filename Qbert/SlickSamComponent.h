#pragma once
#include "Component.h"



namespace dae
{
	class TextComponent;
	class GameObject;
	class SlickSamComponent : public Component
	{
	public:
		SlickSamComponent(GameObject* pParent, const float spawnDuration, const float startPosX = 0.f, const float startPosY = 0.f);
		~SlickSamComponent() = default;


		virtual void Update() override;


		SlickSamComponent(const SlickSamComponent& other) = delete;
		SlickSamComponent(SlickSamComponent&& other) = delete;
		SlickSamComponent& operator=(const SlickSamComponent& other) = delete;
		SlickSamComponent& operator=(SlickSamComponent&& other) = delete;

	protected:

		float m_JumpTimer, m_JumpDuration, m_SpawnTimer, m_SpawnDuration;
		float m_StartPosX, m_StartPosY;
		bool m_SpawnEnabled;

	};

}