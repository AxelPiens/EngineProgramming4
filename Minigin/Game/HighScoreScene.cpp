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
#include "TypeCommands.h"
#include <SDL_mixer.h>

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

	m_BackgroundMusic = Mix_LoadWAV("../Data/Digger/background.wav");
	int channel;

	channel = Mix_PlayChannel(-1, m_BackgroundMusic, -1);

	m_WindowHeight = 330;
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		450,
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
	std::vector<std::string> initials;
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
		size_t find = scores.find(' ');
		std::string score;
		if(find != std::string::npos)
			 score = scores.substr(find+1);
		std::string initial = scores.substr(0, scores.find(' '));
		initials.push_back(initial);
		if(!score.empty())
			highScores.push_back(std::stoi(score));
		createNewFile = false;
	}
	if (createNewFile)
	{
		std::ofstream outFile("../Data/Digger/highscores.txt", std::ios::out);
		for (size_t i = 0; i < 10; i++)
		{
			outFile << "AAA " << 0 << std::endl;
			highScores.push_back(0);
			initials.push_back("AAA ");
		}

		inFile.open("../Data/Digger/highscores.txt");
		if (!inFile.is_open())
		{
			std::cout << "Unable to read file\n";
		}
	}

	auto font = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	int posY = 0;
	for (size_t i = 0; i < highScores.size(); i++)
	{
		auto highScore = std::make_shared<engine::GameObject>("highScore" + std::to_string(i));
		highScore->AddComponent(new TextComponent());
		highScore->GetComponent<TextComponent>()->SetFont(font);
		highScore->GetComponent<TextComponent>()->SetPosition(10, posY);
		highScore->GetComponent<TextComponent>()->SetText(initials[i] + ": " + std::to_string(highScores[i]));
		highScore->GetComponent<TextComponent>()->SetColor({ 255, 0, 0 });

		scene.AddGameobject(highScore);
		posY += 27;

	}


	auto initial = std::make_shared<engine::GameObject>("init");
	initial->AddComponent(new TextComponent());
	initial->GetComponent<TextComponent>()->SetFont(font);
	initial->GetComponent<TextComponent>()->SetPosition(200, 200);
	initial->GetComponent<TextComponent>()->SetText("Initials: ");
	initial->GetComponent<TextComponent>()->SetColor({ 255, 255, 255 });
	scene.AddGameobject(initial);

	auto font2 = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto enterStart = std::make_shared<engine::GameObject>("enterStart");
	enterStart->AddComponent(new TextComponent());
	enterStart->GetComponent<TextComponent>()->SetFont(font2);
	enterStart->GetComponent<TextComponent>()->SetPosition(125, 310);
	enterStart->GetComponent<TextComponent>()->SetText(" ");
	enterStart->GetComponent<TextComponent>()->SetColor({ 255, 255, 255 });
	enterStart->AddComponent(new ControlComponent());
	enterStart->AddComponent(new SwitchingScenesComponent());
	scene.AddGameobject(enterStart);
}

void HighScoreScene::Cleanup()
{
	Renderer::GetInstance().Destroy();
	//Mix_FreeMusic(m_BackgroundMusic);
	Mix_FreeChunk(m_BackgroundMusic);
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
	Inputs();


	auto scene = sceneManager.GetScene("HighScore");
	auto& texts = scene->GetTexts();
	auto& lastText = texts[texts.size() - 1];
	m_InitialsSize = texts[texts.size() - 2]->GetComponent<TextComponent>()->GetText().size();

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
		if(!m_HasEnteredInitials)
			CheckInitials();
	}
	if (lastText->GetComponent<SwitchingScenesComponent>()->GetSwitch())
	{
		Digger engine{false};
		//HighScoreScene engine;
		lastText->GetComponent<SwitchingScenesComponent>()->ChangeSwitch(true);
		scene->RemoveAllGameObjects();
		input.~InputManager();
		engine.Run();

	}
	scene->RemoveAllGameObjects();
	Cleanup();

}

void HighScoreScene::Inputs()
{
	auto& input = engine::InputManager::GetInstance();
	input.SetAKey(new ACommand());
	input.SetBKey(new BCommand());
	input.SetCKey(new CCommand());
	input.SetDKey(new DCommand());
	input.SetEKey(new ECommand());
	input.SetFKey(new FCommand());
	input.SetGKey(new GCommand());
	input.SetHKey(new HCommand());
	input.SetIKey(new ICommand());
	input.SetJKey(new JCommand());
	input.SetKKey(new KCommand());
	input.SetLKey(new LCommand());
	input.SetMKey(new MCommand());
	input.SetNKey(new NCommand());
	input.SetOKey(new OCommand());
	input.SetPKey(new PCommand());
	input.SetQKey(new QCommand());
	input.SetRKey(new RCommand());
	input.SetSKey(new SCommand());
	input.SetTKey(new TCommand());
	input.SetUKey(new UCommand());
	input.SetVKey(new VCommand());
	input.SetWKey(new WCommand());
	input.SetXKey(new XCommand());
	input.SetYKey(new YCommand());
	input.SetZKey(new ZCommand());
}

bool HighScoreScene::CheckInitials()
{
	auto& input = engine::InputManager::GetInstance();
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto& texts = scene->GetTexts();
	if (m_InitialsSize + 3 == texts[texts.size() - 2]->GetComponent<TextComponent>()->GetText().size())
	{
		input.~InputManager();
		texts[texts.size() - 1]->GetComponent<TextComponent>()->SetText("PRESS ENTER TO START");
		input.SetEnterKey(new EnterCommand());


		std::vector<int> highScores;
		std::vector<std::string> initials;
		std::ifstream inFile;
		inFile.open("../Data/Digger/highscores.txt");
		if (!inFile.is_open())
		{
			std::cout << "Unable to read file\n";
		}
		std::string scores;
		while (std::getline(inFile, scores))
		{
			size_t find = scores.find(' ');
			std::string score;
			if (find != std::string::npos)
				score = scores.substr(find + 1);
			std::string initial = scores.substr(0, scores.find(' '));
			initials.push_back(initial);
			if (!score.empty())
				highScores.push_back(std::stoi(score));
		}

		size_t deleting = texts[texts.size() - 2]->GetComponent<TextComponent>()->GetText().find(' ');
		std::string initial = texts[texts.size() - 2]->GetComponent<TextComponent>()->GetText().substr(deleting+1);
		std::ofstream outFile;
		outFile.open("../Data/Digger/highscores.txt");
		for (size_t i = 0; i < highScores.size(); i++)
		{
			outFile << initials[i] << " " << highScores[i] << std::endl;
		}
		outFile << initial << std::endl;
		m_HasEnteredInitials = true;
		return true;
	}
	return false;
}
