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
	Digger(bool firstLoad);
	void Initialize();
	void LoadGame(int level) const;
	void Cleanup();
	void Run();
private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};
	const float m_MsPerUpdate = 0.1f;
	int m_WindowHeight = 0;
	Mix_Chunk* m_PickUpSound = nullptr;
	int m_LevelNumber = 1;
	float m_ElapsedTime = 0.0f;
	int m_MaxLevel = 3;
	int m_HighScore = 0;
	int m_Lives = 3;
	bool m_Continue = true;
	bool m_IsFirstLoad = false;
	void CollisionCheck();
	void HighScoreCheck();
	bool LevelCheck();
	void Inputs();
};
