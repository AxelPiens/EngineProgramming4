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
		void RemoveGameObject(const std::string& name);
		void Update(float deltaTime);
		void Render() const;
		const std::string& GetName() const { return m_Name; };
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_PlayerEnemyColliders;
		std::vector < ColliderComponent*> m_Colliders;
		static unsigned int m_IdCounter;
		float m_FpsTimer = 0.0f;
		float m_ElapsedGameTIme = 0.0f;
		int m_FPSCount = 0;
		int m_FPS = 0;
		std::shared_ptr<GameObject> m_FPSObject;
	};

}
