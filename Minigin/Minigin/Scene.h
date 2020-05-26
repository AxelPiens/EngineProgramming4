#pragma once
#include "SceneManager.h"
class ColliderComponent;
class TransformComponent;
namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void AddGameobject(const std::shared_ptr<GameObject>& object);

		void Update(float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < ColliderComponent*> m_Colliders;
		static unsigned int m_IdCounter;
		float m_FpsTimer = 0.0f;
		float m_ElapsedGameTIme = 0.0f;
		int m_FPSCount = 0;
		int m_FPS = 0;
	};

}
