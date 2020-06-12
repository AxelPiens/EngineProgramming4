#pragma once
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
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		const float m_MsPerUpdate = 0.1f;
		int m_WindowHeight = 0.0f;
		void LevelBoundaries(std::vector<std::shared_ptr<GameObject>> players);
		void CollisionChecks();
	};
}