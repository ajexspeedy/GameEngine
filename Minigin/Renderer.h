#pragma once
#include "Singleton.h"
#include <SDL.h>
struct SDL_Window;
struct SDL_Renderer;

class SDL;
namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, float x, float y) const;



		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		int GetOpenGLDriverIndex() const;
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		bool m_ShowDemo{ false }, m_ShowControls{ false };

		void ShowControls();
	};
}

