#include "MiniginPCH.h"
#include "Minigin.h"
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
#include "TextComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "ControlComponent.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "Parser.h"
#include "ProjectileComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TextureComponent("background.jpg"));
	go->AddComponent(new TransformComponent(5));
	go->GetComponent<TransformComponent>()->Translate(0, 0, 0);
	scene.AddGameobject(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new SpriteComponent("sprites0SMALL.png", 32, 32, 0, 0, 8, 250, true));
	go->AddComponent(new TransformComponent(32, 32, 200));
	go->GetComponent<TransformComponent>()->Translate(200, 180, 0);
	go->AddComponent(new ColliderComponent("player"));
	go->AddComponent(new ControlComponent());
	go->AddComponent(new RigidbodyComponent(1.0f, 50.0f));
	scene.AddGameobject(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>();
	to->AddComponent(new TextComponent());
	to->GetComponent<TextComponent>()->SetFont(font);
	to->GetComponent<TextComponent>()->SetPosition(10, 10);

	scene.AddGameobject(to);


	auto to2 = std::make_shared<GameObject>();
	to2->AddComponent(new TextComponent());
	to2->GetComponent<TextComponent>()->SetFont(font);
	to2->GetComponent<TextComponent>()->SetText("PFF");
	to2->GetComponent<TextComponent>()->SetPosition(300, 10);

	scene.AddGameobject(to2);

	Parser parser{};
	int levelNr = 2;

	parser.ReadFile("../Data/SeperatedLevelData.dat", levelNr);
	std::vector<int> levelData{};
	parser.GetLevelData(levelData);
	int posY = -16;
	int moduloX = 0;
	for (size_t i = 0; i < levelData.size(); i++)
	{
		moduloX = i % 32;
		if (moduloX == 0)
		{
			posY += 16;
		}
		if (levelData[i] == 1)
		{
			auto brick = std::make_shared<GameObject>();
			brick->AddComponent(new TransformComponent(8, 8, 0));
			brick->GetComponent<TransformComponent>()->Translate(16 * moduloX, posY, 0);
			brick->AddComponent(new SpriteComponent("blocks.png", 16, 16, ((levelNr) / 10) * 8, ((levelNr) % 10) * 8, 1, 1, false));
			brick->AddComponent(new ColliderComponent("level"));
			scene.AddGameobject(brick);

		}

	}

	auto projectile = std::make_shared<GameObject>();
	projectile->AddComponent(new TransformComponent(16, 16, 100));
	projectile->GetComponent<TransformComponent>()->Translate(100, 400, 0);
	projectile->AddComponent(new SpriteComponent("sprites1SMALL.png", 32, 32, 16*12, 0, 8, 50, true));
	projectile->AddComponent(new ProjectileComponent(200, 1));
	scene.AddGameobject(projectile);


}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	std::cout << "RUN\n";

	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			doContinue = !input.IsQuitting();
			sceneManager.Update(deltaTime);
			renderer.Render();
		}
	}

	Cleanup();
}

