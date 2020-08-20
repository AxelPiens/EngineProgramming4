#pragma once
#include "SceneManager.h"
class ColliderComponent;
class TransformComponent;
namespace engine
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void AddGameobject(const std::shared_ptr<GameObject>& object);
		void RemoveGameObject(const std::string& name);
		void RemoveAllGameObjects();
		void Update(float deltaTime);
		std::vector < std::shared_ptr<GameObject>>& GetTriggers() { return m_Triggers; };
		std::vector < ColliderComponent*>& GetColliders() { return m_Colliders; };
		std::vector < std::shared_ptr<GameObject>>& GetPlayerEnemyColliders() { return m_PlayerEnemyColliders; };
		std::vector < std::shared_ptr<GameObject>>& GetTexts() { return m_Texts; };

		void Render() const;
		const std::string& GetName() const { return m_Name; };

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		std::vector<std::shared_ptr<GameObject>> GetPlayers() { return m_Players; };
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Players;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_PlayerEnemyColliders;
		std::vector < std::shared_ptr<GameObject>> m_Triggers{};
		std::vector < std::shared_ptr<GameObject>> m_Texts{};

		std::vector < ColliderComponent*> m_Colliders;
		static unsigned int m_IdCounter;
		float m_FpsTimer = 0.0f;
		float m_ElapsedGameTIme = 0.0f;
		int m_FPSCount = 0;
		int m_FPS = 0;
		std::shared_ptr<GameObject> m_FPSObject;
	};

}
