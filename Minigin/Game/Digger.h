#pragma once
#include <SDL_mixer.h>
struct SDL_Window;
class TextObject;
class TextComponent;
namespace engine
{
	class GameObject;
	struct Vector3;
}
class Digger
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
	Mix_Music* m_BackgroundMusic = nullptr;
	int m_BubbleAmount = 0;
	int m_LevelNumber = 0;
	int m_FoodNumber = 0;
	int m_Lives = 4;
	int m_EnemyCounter = 3;
	float m_ElapsedTime = 0.0f;
	float m_NextLevelTime = 7.0f;
	int m_MaxLevel = 2;
	int m_Score = 0;
	bool m_Continue = true;
	void CollisionCheck();
};
