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
#include "KillCommand.h"
#include "PlayerScoreDisplay.h"
#include "ScoreCommand.h"
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
	
	Locator::Provide(new Audio_SDL{});

	Renderer::GetInstance().Init(m_Window);
}


void dae::Minigin::LoadGame() const
{
	if (m_pGame != nullptr)
	{
		m_pGame->LoadGame();
	}
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//RenderComponent render_component{ "background.jpg" };

	//auto game_object1 = new GameObject(std::make_shared<RenderComponent>("background.jpg"), "Background");
	//scene.Add(game_object1);

	//auto game_object2 = new GameObject(std::make_shared<RenderComponent>("logo.png", 216.f, 180.f), "Logo");
	//scene.Add(game_object2);

	//const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto text_object = new GameObject(std::make_shared<TextComponent>("Programming 4 Assignment", font), "Text");
	//text_object->SetPosition(80, 50);
	//scene.Add(text_object);

	//const auto sansFont = ResourceManager::GetInstance().LoadFont("Comic_Sans.otf", 18);
	//auto fps_counter = new GameObject(std::make_shared<FPSComponent>("FPS: 0", sansFont), "FPS_Counter");
	//scene.Add(fps_counter);


	//{
	//	// Player 1 
	//	int lives = 3;
	//	auto qbert = new GameObject(std::make_shared<RenderComponent>("Qbert.png"), "Qbert");
	//	std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(1, lives);
	//	std::shared_ptr<PlayerLivesDisplay> healthDisplay = std::make_shared<PlayerLivesDisplay>(sansFont, lives, 180.f);
	//	std::shared_ptr<PlayerScoreDisplay> scoreDisplay = std::make_shared<PlayerScoreDisplay>(sansFont, 350.f, 0.f);
	//	playerComponent->AddObserver(healthDisplay);
	//	playerComponent->AddObserver(scoreDisplay);

	//	qbert->AddComponent(playerComponent);
	//	qbert->AddComponent(healthDisplay);
	//	qbert->AddComponent(scoreDisplay);
	//	qbert->SetPosition(20, 20);

	//	// Commands player 1 
	//	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonA, new KillCommand(playerComponent));
	//	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonB, new ScoreCommand(playerComponent));

	//	scene.Add(qbert);

	//	auto qbert2 = new GameObject(std::make_shared<RenderComponent>("Qbert.png", 50.f), "Qbert2");
	//	std::shared_ptr<PlayerComponent> playerComponent2 = std::make_shared<PlayerComponent>(1, lives);
	//	std::shared_ptr<PlayerLivesDisplay> healthDisplay2 = std::make_shared<PlayerLivesDisplay>(sansFont, lives, 180.f, 20.f);
	//	std::shared_ptr<PlayerScoreDisplay> scoreDisplay2 = std::make_shared<PlayerScoreDisplay>(sansFont, 350.f, 20.f);
	//	playerComponent2->AddObserver(healthDisplay2);
	//	playerComponent2->AddObserver(scoreDisplay2);

	//	qbert2->AddComponent(playerComponent2);
	//	qbert2->AddComponent(healthDisplay2);
	//	qbert2->AddComponent(scoreDisplay2);
	//	qbert2->SetPosition(180, 40);


	//	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonX, new KillCommand(playerComponent2));
	//	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonY, new ScoreCommand(playerComponent2));

	//	scene.Add(qbert2);

	//}
	//// Sound 
	//{
	//	Locator::Provide(new AudioLogger(Locator::GetAudio()));
	//	AudioManager::GetInstance().AddSound("../Data/menu3.wav",1);
	//	
	//	
	//}
}



void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	AudioManager::GetInstance().CleanUp();
	Locator::CleanUp();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
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
