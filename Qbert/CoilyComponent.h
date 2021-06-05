#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerLivesDisplay.h"
#include "Observer.h"


namespace dae
{
	class TextComponent;
	class GameObject;
	class CoilyComponent : public Component
	{
	public:
		enum class CoilyForm
		{
			egg,
			snake
		};
		CoilyComponent(GameObject* pParent,GameObject* pPlayer, const float spawnDuration, const float startPosX = 0.f, const float startPosY = 0.f);
		~CoilyComponent() = default;


		virtual void Update() override;

		void SetSpawnEnabled(bool enable);
		bool GetSpawnEnabled() const;


		CoilyComponent(const CoilyComponent& other) = delete;
		CoilyComponent(CoilyComponent&& other) = delete;
		CoilyComponent& operator=(const CoilyComponent& other) = delete;
		CoilyComponent& operator=(CoilyComponent&& other) = delete;

	protected:
		void CheckSpawnEgg();
		void CheckEggFalling();
		void CheckCoilyMovement();

		void SpawnEgg();
		void JumpEgg();
		void JumpSnake();

		float m_SpawnTimer, m_SpawnDuration, m_JumpTimer, m_JumpDuration;
		float m_FallVelocity,m_StartPositionX, m_StartPositionY;
		unsigned int m_SnakeWidth, m_SnakeHeight;

		CoilyForm m_Form;
		bool m_SpawnEnabled, m_IsSpawned, m_IsFalling, m_IsActive;

		unsigned int m_EggJumpCounter, m_MaxEggJumps;

		GameObject* m_pPlayer;
	};

}