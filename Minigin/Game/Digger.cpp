#include "Digger.h"
#include "MiniginPCH.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Components.h"
#include "ChangeSpriteComponent.h"
#include "StateComponent.h"
#include "ShootCommand.h"
#include "WalkRightCommand.h"
#include "WalkLeftCommand.h"
#include "JumpCommand.h"
#include "WalkDownCommand.h"
#include "WalkUpCommand.h"
#include "Collision.h"
#include "MovingBagComponent.h"
	
using namespace std;
using namespace std::chrono;

void Digger::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error(std::string("SDL_Audio Error: ") + Mix_GetError());

	m_BackgroundMusic = Mix_LoadMUS("../Data/Audio/BackgroundMusic.mp3");
	//Mix_PlayMusic(m_BackgroundMusic, -1);


	m_WindowHeight = 400;
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		600,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

}

void Digger::LoadGame(int level) const
{

	auto& scene = engine::SceneManager::GetInstance().CreateScene("Game");


	//level 
	int posX = 0;
	int posY = 0;
	int random = 0;
	int number = 0;
	int size = 27;
	for (size_t i = 0; i < 49; i++)
	{
		for (size_t j = 0; j < 74; j++)
		{
			auto level2 = std::make_shared<engine::GameObject>("level" + std::to_string(number));
			std::string start = "/Digger/ground0";
			random = rand()%3;
			level2->AddComponent(new SpriteComponent(( start + ".png"), size, size, 0, 0, 1, 150, false));
			level2->AddComponent(new TransformComponent(size, size, 200));
			level2->GetComponent<TransformComponent>()->Translate(posX, posY, 0);
			level2->AddComponent(new ColliderComponent("level" + number, true, 0,0));
			scene.AddGameobject(level2);
			posX += size;
			++number;
		}
		posY += size;
		posX = 0;
	}


	////diamond test 
	//auto diamond = std::make_shared<engine::GameObject>("diamond");
	//std::string start = "/Digger/emerald";
	//diamond->AddComponent(new SpriteComponent((start + ".png"), 26, 21, 0, 0, 1, 150, false));
	//diamond->AddComponent(new TransformComponent(26, 21, 200));
	//diamond->GetComponent<TransformComponent>()->Translate(0, 200, 0);
	//diamond->AddComponent(new ColliderComponent("diamond", true, 0, 0));
	//scene.AddGameobject(diamond);

	//money test
	auto money = std::make_shared<engine::GameObject>("money");
	std::string start = "/Digger/moneybag";
	money->AddComponent(new SpriteComponent((start + ".png"), 26, 26, 0, 0, 1, 150, false));
	money->AddComponent(new TransformComponent(27, 28, 200));
	money->GetComponent<TransformComponent>()->Translate(190, 0, 0);
	money->AddComponent(new ColliderComponent("money", false, 0, 0));
	money->AddComponent(new RigidbodyComponent(0.0f, 50.0f, -155.f, 75.0f));
	money->AddComponent(new MovingBagComponent());
	scene.AddGameobject(money);



	//player
	auto go = std::make_shared<engine::GameObject>("player");
	go->AddComponent(new SpriteComponent("/Digger/miner.png", 21, 27, 0, 0, 3, 150, true));
	go->AddComponent(new TransformComponent(15.f, 17.5f, 0));
	go->GetComponent<TransformComponent>()->Translate(0, 0, 0);
	//go->GetComponent<TransformComponent>()->Translate(270, 216, 0);
	go->AddComponent(new ColliderComponent("player", false, 2, 2));
	go->AddComponent(new ControlComponent());
	go->AddComponent(new RigidbodyComponent(0.0f, 50.0f, -155.f, 75.0f));
	go->AddComponent(new ChangeSpriteComponent());
	go->AddComponent(new StateComponent());
	scene.AddGameobject(go);
}


void Digger::Cleanup()
{
	Renderer::GetInstance().Destroy();
	Mix_FreeMusic(m_BackgroundMusic);
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}


void Digger::Run()
{

	Initialize();

	// tell the resource manager where he can find the game data
	engine::ResourceManager::GetInstance().Init("../Data/");

	LoadGame(m_LevelNumber);
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = engine::SceneManager::GetInstance();
		auto& input = engine::InputManager::GetInstance();
		input.SetKeyBoardCommands(new WalkLeftCommand(), new WalkRightCommand(), new WalkUpCommand(), new WalkDownCommand());
		input.SetControllerCommands(new WalkDownCommand(), new WalkLeftCommand(), new WalkUpCommand(), new WalkRightCommand());

		auto lastTime = std::chrono::high_resolution_clock::now();
		while (m_Continue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			m_Continue = !input.IsQuitting();
			sceneManager.Update(deltaTime);
			CollisionCheck();
			renderer.Render();
		}
	}

	Cleanup();
}

void Digger::CollisionCheck()
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();
	auto players = scene->GetPlayers();
	for (auto trigger : triggers)
	{
		if (engine::Collision::AABB(*trigger->GetComponent<ColliderComponent>(), *players[1]->GetComponent<ColliderComponent>()))
		{
			scene->RemoveGameObject(trigger->GetName());
			std::cout << trigger->GetName();
		}
	}

	for (auto collider : colliders)
	{
		if (engine::Collision::AABB(*collider, *players[1]->GetComponent<ColliderComponent>()))
		{
			if (players[1]->GetComponent<StateComponent>()->GetState() == PlayerState::WalkUp)
				players[1]->GetComponent<TransformComponent>()->SetVelocityY(0);
		}
	}
}
