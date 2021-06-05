#pragma once
#include "Component.h"
#include "Subject.h"
#include "PlayerLivesDisplay.h"
#include "Observer.h"


namespace dae
{
	class TextComponent;
	class GameObject;
	class UggWrongwayComponent : public Component
	{
	public:
		enum class UggWrongwayForm
		{
			ugg,
			wrongway
		};
		UggWrongwayComponent(GameObject* pParent, UggWrongwayForm form, const float startPosX = 0.f, const float startPosY = 0.f);
		~UggWrongwayComponent() = default;


		virtual void Update() override;



		UggWrongwayComponent(const UggWrongwayComponent& other) = delete;
		UggWrongwayComponent(UggWrongwayComponent&& other) = delete;
		UggWrongwayComponent& operator=(const UggWrongwayComponent& other) = delete;
		UggWrongwayComponent& operator=(UggWrongwayComponent&& other) = delete;

	protected:


		bool m_SpawnEnabled;

		float m_StartPosX, m_StartPosY, m_JumpTimer,m_JumpDuration;

	

		UggWrongwayForm m_Form;
	};

}