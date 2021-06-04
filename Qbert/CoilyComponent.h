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
		CoilyComponent(GameObject* pParent, GameObject* pPlayer, const float spawnDuration);
		~CoilyComponent() = default;


		virtual void Update() override;

		void SetSpawnEnabled(bool enable);
		bool GetSpawnEnabled() const;


		CoilyComponent(const CoilyComponent& other) = delete;
		CoilyComponent(CoilyComponent&& other) = delete;
		CoilyComponent& operator=(const CoilyComponent& other) = delete;
		CoilyComponent& operator=(CoilyComponent&& other) = delete;

	protected:
		void SpawnEgg();

		float m_SpawnTimer, m_SpawnDuration;
		float m_FallTimer, m_FallDuration, m_FallVelocity, m_StartPositionY;

		CoilyForm m_Form;
		bool m_SpawnEnabled, m_IsSpawned, m_IsFalling, m_IsActive;

		GameObject* m_pPlayer;
	};

}