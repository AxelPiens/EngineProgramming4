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
#include <fstream>
#include "MovementSpiderComponent.h"
#include "LiveComponent.h"
#include "ScoreComponent.h"
#include "ShootComponent.h"
#include "TurnHobbinComponent.h"

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
		500,
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
	std::string numbers;
	std::ifstream myfile;
	myfile.open("../Data/Digger/LevelData" + std::to_string(m_LevelNumber) + ".txt");

	int posX = 0.f;
	int posY = 27;
	int number = 0;
	int size = 27;

	if (myfile.is_open())
	{
		while (std::getline(myfile, numbers))
		{
			for (size_t i = 0; i < numbers.size(); i++)
			{

				if (numbers[i] == '0') //nothing
				{

				}
				else if(numbers[i] == '1') //ground
				{
					auto level2 = std::make_shared<engine::GameObject>("level" + std::to_string(number));
					level2->AddComponent(new SpriteComponent(("/Digger/ground0.png"), size, size, 0, 0, 1, 150, false));
					level2->AddComponent(new TransformComponent(size, size, 200));
					level2->GetComponent<TransformComponent>()->Translate(posX, posY, 0);
					level2->AddComponent(new ColliderComponent("level" + number, true, 0, 0));
					scene.AddGameobject(level2);

				}
				else if (numbers[i] == '2') //diamonds
				{
					auto level2 = std::make_shared<engine::GameObject>("level" + std::to_string(number));
					level2->AddComponent(new SpriteComponent(("/Digger/ground0.png"), size, size, 0, 0, 1, 150, false));
					level2->AddComponent(new TransformComponent(size, size, 200));
					level2->GetComponent<TransformComponent>()->Translate(posX, posY, 0);
					level2->AddComponent(new ColliderComponent("level" + number, true, 0, 0));
					scene.AddGameobject(level2);
				}
				else if (numbers[i] == '3') //money
				{
					auto level2 = std::make_shared<engine::GameObject>("level" + std::to_string(number));
					level2->AddComponent(new SpriteComponent(("/Digger/ground0.png"), size, size, 0, 0, 1, 150, false));
					level2->AddComponent(new TransformComponent(size, size, 200));
					level2->GetComponent<TransformComponent>()->Translate(posX, posY, 0);
					level2->AddComponent(new ColliderComponent("level" + number, true, 0, 0));
					scene.AddGameobject(level2);


				}
				else if (numbers[i] == '4')
				{
					auto level2 = std::make_shared<engine::GameObject>("level" + std::to_string(number));
					level2->AddComponent(new SpriteComponent(("/Digger/ground0.png"), size, size, 0, 0, 1, 150, false));
					level2->AddComponent(new TransformComponent(size, size, 200));
					level2->GetComponent<TransformComponent>()->Translate(posX, posY, 0);
					level2->AddComponent(new ColliderComponent("level" + number, false, 0, 0));
					scene.AddGameobject(level2);
				}
				++number;
				posX += size;
			}
			posY += size;
			posX = 0.f;
		}
		posY = 27;
		posX = 0.f;
		myfile.clear();
		myfile.seekg(0);
		while (std::getline(myfile, numbers))
		{
			for (size_t i = 0; i < numbers.size(); i++)
			{
				if (numbers[i] == '2') //diamonds
				{
					auto diamond = std::make_shared<engine::GameObject>("diamond" + std::to_string(number));
					diamond->AddComponent(new SpriteComponent(("/Digger/emerald.png"), 26, 21, 0, 0, 1, 150, false));
					diamond->AddComponent(new TransformComponent(26, 21, 200));
					diamond->GetComponent<TransformComponent>()->Translate(posX, posY + 5, 0);
					diamond->AddComponent(new ColliderComponent("diamond", true, 0, 0));
					diamond->AddComponent(new StateComponent());
					scene.AddGameobject(diamond);
					diamond->GetComponent<StateComponent>()->ChangeScoresState(Scores::Emeralds);
				}
				else if (numbers[i] == '3') //money
				{

					auto money = std::make_shared<engine::GameObject>("money" + std::to_string(number));
					money->AddComponent(new SpriteComponent(("/Digger/moneybag.png"), 26, 26, 0, 0, 1, 150, false));
					money->AddComponent(new TransformComponent(27, 28, 200));
					money->GetComponent<TransformComponent>()->Translate(posX, posY, 0);
					money->AddComponent(new ColliderComponent("money", false, 0, 0));
					money->AddComponent(new RigidbodyComponent(0.0f, 50.0f, -155.f, 75.0f));
					money->AddComponent(new MovingBagComponent());
					scene.AddGameobject(money);

					money->GetComponent<MovingBagComponent>()->SetOldPosY(posY);
				}
				++number;
				posX += size;
			}
			posY += size;
			posX = 0.f;
		}

	}
	myfile.close();

	//spidertest
	auto spider = std::make_shared<engine::GameObject>("spider");
	spider->AddComponent(new SpriteComponent(("/Digger/spiders.png"), 27, 27, 0, 0, 6, 150, true));
	spider->AddComponent(new TransformComponent(27, 28, 200));
	//spider->GetComponent<TransformComponent>()->Translate(400,27, 0);
	spider->GetComponent<TransformComponent>()->Translate(200, 297, 0);
	spider->GetComponent<TransformComponent>()->SetVelocityX(65);
	spider->AddComponent(new MovementSpiderComponent(65));
	spider->AddComponent(new ColliderComponent("spider", true, 0, 0));
	spider->AddComponent(new ChangeSpriteComponent());
	spider->AddComponent(new TurnHobbinComponent(4.0f, 3.0f));
	spider->AddComponent(new StateComponent());
	scene.AddGameobject(spider);
	spider->GetComponent<StateComponent>()->ChangeScoresState(Scores::Nobbins);




	//player
	auto player = std::make_shared<engine::GameObject>("player");
	player->AddComponent(new SpriteComponent("/Digger/miner.png", 21, 27, 0, 0, 3, 150, true));
	player->AddComponent(new TransformComponent(15.f, 17.5f, 0));
	player->GetComponent<TransformComponent>()->Translate(27, 27 + 1.5f * 27, 0);
	//go->GetComponent<TransformComponent>()->Translate(270, 216, 0);
	player->AddComponent(new ColliderComponent("player", false, 2, 2));
	player->AddComponent(new ControlComponent());
	player->AddComponent(new RigidbodyComponent(0.0f, 50.0f, -155.f, 75.0f));
	player->AddComponent(new ChangeSpriteComponent());
	player->AddComponent(new StateComponent());
	player->AddComponent(new LiveComponent(3, 3.0f));
	player->AddComponent(new ScoreComponent());
	player->AddComponent(new ShootComponent(4.0f));
	scene.AddGameobject(player);
	player->GetComponent<LiveComponent>()->Init();
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
		input.SetAKey(new WalkLeftCommand());
		input.SetSKey(new WalkDownCommand());
		input.SetDKey(new WalkRightCommand());
		input.SetWKey(new WalkUpCommand());
		input.SetSpaceBarKey(new ShootCommand());



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
	HighScoreCheck();
	Cleanup();
}

void Digger::CollisionCheck()
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();
	auto players = scene->GetPlayers();

	int number = 1;
	for (auto trigger : triggers)
	{
		if (engine::Collision::AABB(*trigger->GetComponent<ColliderComponent>(), *players[number]->GetComponent<ColliderComponent>()))
		{
			if (trigger->GetName().find("spider") != std::string::npos && players[number]->GetComponent<StateComponent>()->GetPlayerState() != PlayerState::Death)
			{
				
				players[number]->GetComponent<LiveComponent>()->LoseLive();
				players[number]->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Death);
				players[number]->GetComponent<TransformComponent>()->SetVelocity(engine::Vector3(0, 0, 0));
				break;
			}
			else if(players[number]->GetComponent<StateComponent>()->GetPlayerState() != PlayerState::Death
				&& players[number]->GetComponent<StateComponent>()->GetPlayerState() != PlayerState::Idle)
			{
				if(trigger->GetComponent<StateComponent>())
					players[number]->GetComponent<ScoreComponent>()->AddScore(trigger);
				if(trigger->GetName().find("projectile") == std::string::npos)
					scene->RemoveGameObject(trigger->GetName());
				std::cout << trigger->GetName() << std::endl;
				break;
			}
		}

	}

	for (auto collider : colliders)
	{
		if (engine::Collision::AABB(*collider, *players[number]->GetComponent<ColliderComponent>()))
		{
			if (collider->GetGameObject()->GetComponent<MovingBagComponent>())
			{
				if (collider->GetGameObject()->GetComponent<MovingBagComponent>()->GetIsFalling())
				{
					players[number]->GetComponent<LiveComponent>()->LoseLive();
					players[number]->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Death);
					players[number]->GetComponent<TransformComponent>()->SetVelocity(engine::Vector3(0, 0, 0));
				}
			}
		}
	}

	
}

void Digger::HighScoreCheck()
{
	//initials
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto players = scene->GetPlayers();
	
	int score = players[1]->GetComponent<ScoreComponent>()->GetScore();

	std::vector<int> highScores;
	std::ifstream inFile;
	bool createNewFile = true;
	inFile.open("../Data/Digger/highscores.txt");
	if (!inFile.is_open())
	{
		std::cout << "Unable to read file\n";
	}
	std::string scores;
	while (std::getline(inFile, scores))
	{
		highScores.push_back(std::stoi(scores));
		createNewFile = false;
	}
	if (createNewFile)
	{
		std::ofstream outFile("../Data/Digger/highscores.txt", ios::out);
		for (size_t i = 0; i < 10; i++)
		{
			outFile << 0 << std::endl;
			highScores.push_back(0);
		}

		inFile.open("../Data/Digger/highscores.txt");
		if (!inFile.is_open())
		{
			std::cout << "Unable to read file\n";
		}
	}

	for (size_t i = 0; i < highScores.size(); i++)
	{
		if (highScores[i] < score)
		{
			highScores.insert(highScores.begin() + i, score);
			highScores.pop_back();
			break;
		}
	}
	std::ofstream outFile;
	outFile.open("../Data/Digger/highscores.txt");
	for (size_t i = 0; i < highScores.size(); i++)
	{
		outFile << highScores[i] << std::endl;

	}

}
