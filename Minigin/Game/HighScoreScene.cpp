#include "HighScoreScene.h"
#include "MiniginPCH.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Components.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ControlComponent.h"
#include <fstream>
#include "SwitchingScenesComponent.h"
#include "EnterCommand.h"
#include "Digger.h"

HighScoreScene::HighScoreScene(bool firstLoad)
	:m_IsFirstLoad{firstLoad}
{
}

void HighScoreScene::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error(std::string("SDL_Audio Error: ") + Mix_GetError());

	//m_BackgroundMusic = Mix_LoadMUS("../Data/Audio/BackgroundMusic.mp3");
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

void HighScoreScene::LoadGame() const
{

	auto& scene = engine::SceneManager::GetInstance().CreateScene("HighScore");


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
		std::ofstream outFile("../Data/Digger/highscores.txt", std::ios::out);
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

	auto font = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	int posY = 0;
	for (size_t i = 0; i < highScores.size(); i++)
	{
		auto highScore = std::make_shared<engine::GameObject>("highScore" + std::to_string(i));
		highScore->AddComponent(new TextComponent());
		highScore->GetComponent<TextComponent>()->SetFont(font);
		highScore->GetComponent<TextComponent>()->SetPosition(50, posY);
		highScore->GetComponent<TextComponent>()->SetText(std::to_string(highScores[i]));

		scene.AddGameobject(highScore);
		posY += 36;

	}


	auto font2 = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto enterStart = std::make_shared<engine::GameObject>("enterStart");
	enterStart->AddComponent(new TextComponent());
	enterStart->GetComponent<TextComponent>()->SetFont(font2);
	enterStart->GetComponent<TextComponent>()->SetPosition(150, 375);
	enterStart->GetComponent<TextComponent>()->SetText("PRESS ENTER TO START");
	enterStart->AddComponent(new ControlComponent());
	enterStart->AddComponent(new SwitchingScenesComponent());
	scene.AddGameobject(enterStart);
}

void HighScoreScene::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void HighScoreScene::Run()
{


	if(m_IsFirstLoad)
		Initialize();
	engine::ResourceManager::GetInstance().Init("../Data/");
	LoadGame();
	if (engine::SceneManager::GetInstance().GetScene("Game"))
		engine::SceneManager::GetInstance().RemoveScene("Game");
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = engine::SceneManager::GetInstance();
	auto& input = engine::InputManager::GetInstance();
	auto lastTime = std::chrono::high_resolution_clock::now();
	input.SetEnterKey(new EnterCommand());
	auto scene = sceneManager.GetScene("HighScore");
	auto& texts = scene->GetTexts();
	auto& lastText = texts[texts.size() - 1];
	while (m_Continue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		m_Continue = !input.IsQuitting();
		if(m_Continue)
			m_Continue  = !lastText->GetComponent<SwitchingScenesComponent>()->GetSwitch();
		sceneManager.Update(deltaTime);
		renderer.Render();
	}
	if (lastText->GetComponent<SwitchingScenesComponent>()->GetSwitch())
	{
		Digger engine{false};
		//HighScoreScene engine;
		lastText->GetComponent<SwitchingScenesComponent>()->ChangeSwitch(true);
		scene->RemoveAllGameObjects();
		engine.Run();

	}
	scene->RemoveAllGameObjects();
	Cleanup();

}
