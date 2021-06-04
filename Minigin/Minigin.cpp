#include "ImposterPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Component.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PlayerScoreDisplay.h"
#include "SDL_mixer.h"
#include "AudioManager.h"
#include "Audio_SDL.h"
#include "Locator.h"
#include "AudioQueue.h"
#include <thread>
#include <future>
#include "AudioLogger.h"
#include "EnableAudioLogging.h"
#include "Game.h"

std::atomic<bool> g_IsLooping = true;

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 4, 2048) > 0)
	{
		throw std::runtime_error(std::string("SDL_mixer could not initialize! SDL Error") + SDL_GetError());

	}
	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
	{
		throw std::runtime_error(std::string("SDL_mixer could not initialize! SDL Error") + SDL_GetError());
	}
	



	Renderer::GetInstance().Init(m_Window);
}


void dae::Minigin::LoadGame()
{
	if (m_pGame != nullptr)
	{
		m_pGame->LoadGame();
	}
	
}



void dae::Minigin::Cleanup()
{
	m_pGame->CleanUp();
	Renderer::GetInstance().Destroy();
	AudioManager::GetInstance().CleanUp();
	Locator::CleanUp();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	delete m_pGame;
	m_pGame = nullptr;
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{ 
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& timer = TimeManager::GetInstance();
		auto& audio = AudioQueue::GetInstance();
		
		g_IsLooping = true;
		auto soundThread = std::async(std::launch::async,[&audio]()
			{
				while(g_IsLooping.load())
					audio.Update();
			});

		float lag = 0.0f;
		while (g_IsLooping.load())
		{

			timer.CalculateDeltaTime();
			lag += timer.GetDeltaTime();
			g_IsLooping.store(input.ProcessInput());
			input.HandleInput();
			while (lag >= m_MsPerFrame)
			{

				sceneManager.Update();
				lag -= m_MsPerFrame;
			}
			renderer.Render();


		}
	}

	Cleanup();
}
