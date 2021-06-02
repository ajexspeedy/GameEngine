#pragma once
#include "Observer.h"
#include "Component.h"

namespace dae
{
	class Font;
	class TextComponent;
    class GameObject;
	enum class ColorScore
	{
		change = 25,
		coily = 500,
		discsRemaining = 50,
		slickAndSam = 300
	};
    class PlayerScoreDisplay :
        public Observer, public Component
    {
    public:
        PlayerScoreDisplay(GameObject* pParent, const std::shared_ptr<Font>& font,float x = 0,float y = 0);
        ~PlayerScoreDisplay() = default;

        virtual void onNotify(const Event& event) override;
		virtual void Render() const override;
        void Update() override;
    
    private:
        int m_Score{0};
        bool m_UpdateScore{ false };
        std::unique_ptr<TextComponent> m_pTextComponent;
    };

}