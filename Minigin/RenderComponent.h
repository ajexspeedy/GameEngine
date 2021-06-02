#pragma once
#include "Component.h"
#include "Transform.h"
#include <SDL.h>

namespace dae
{
	class Texture2D;
	class GameObject;
	class RenderComponent : public Component
	{

	public:
		RenderComponent() = default;
		~RenderComponent() = default;
		RenderComponent(GameObject* pParent, const std::string& filename);
		RenderComponent(GameObject* pParent, const std::string& filename, const float width, const float height);

		void Render() const override;
		void Update() override;
		void SetTexture(const std::string& filename);
		
		void SetPosition(float x, float y);
		void Translate(float x,float y);

		void SetSrcRect(float x, float y, float width, float height);
		void SetSrcRect(const SDL_Rect& srcRect);
		void SetSrcRectPosition(int x, int y);
		void MoveSrcRectPosition(int x, int y);

	
	protected:

		std::shared_ptr<Texture2D> m_Texture{};
		SDL_Rect m_SrcRect;
		bool m_UseSrcRect;
		float m_Width, m_Height;
	};
}