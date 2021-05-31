#pragma once

struct SDL_Window;
class Game;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		Game* m_pGame;
	private:
		const float m_MsPerFrame = 0.016f; //16 for 60 fps, 33 for 30 fps
		
		SDL_Window* m_Window{};
	};
}