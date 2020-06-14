#pragma once
#include <SDL_mixer.h>
struct SDL_Window;
namespace dae
{
	class TextObject;
	class TextComponent;
	class GameObject;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame(int level) const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		const float m_MsPerUpdate = 0.1f;
		int m_WindowHeight = 0;
		void LevelBoundaries(std::vector<std::shared_ptr<GameObject>> players);
		void CollisionChecks();
		void CheckForNextLevel(float deltaTime);
		Mix_Music* bgm;
		int m_BubbleAmount;
		int m_LevelNumber = 0;
		int m_Lives = 3;
		int m_EnemyCounter = 3;
		float m_ElapsedTime = 0.0f;
		float m_NextLevelTime = 5.0f;
	};
}