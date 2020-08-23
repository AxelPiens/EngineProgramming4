#pragma once
#include <SDL_mixer.h>
struct SDL_Window;
class TextObject;
class TextComponent;
class HighScoreScene
{
public:
	HighScoreScene(bool firstLoad);
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();
private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};
	const float m_MsPerUpdate = 0.1f;
	int m_WindowHeight = 0;
	bool m_Continue = true;
	bool m_IsFirstLoad = false;
	size_t m_InitialsSize = 0;
	bool m_HasEnteredInitials = false;
	Mix_Chunk* m_BackgroundMusic = nullptr;
	void Inputs();
	bool CheckInitials();

};

