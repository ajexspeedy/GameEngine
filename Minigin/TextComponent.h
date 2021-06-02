#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextComponent : public Component
	{
	public:
		explicit TextComponent(GameObject* pParent,const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;
	

		virtual void Update() override;
		virtual void Render() const override;
		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
		
	protected:
	
		std::shared_ptr<Texture2D> m_Texture{};
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		void UpdateTexture();
	};
}
