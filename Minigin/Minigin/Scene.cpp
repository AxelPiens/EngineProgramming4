#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collision.h"
#include "Components.h"
#include "..\Game\EnemyAIComponent.h" 
#include "..\Game\ProjectileComponent.h"
#include <SDL.h>
using namespace engine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::AddGameobject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	if(object->GetName() == "FPS")
		m_FPSObject = object;
	if (object->HasComponent<ColliderComponent>())
	{
		if (object->GetComponent<ColliderComponent>()->GetTag() == "player")
		{
			m_Players.push_back(object);
			return;
		}
		if (object->GetComponent<ColliderComponent>()->GetIsTrigger())
			m_Triggers.push_back(object);
		else
			m_Colliders.push_back(object->GetComponent<ColliderComponent>());

	}
	if (object->HasComponent<TextComponent>())
	{
		m_Texts.push_back(object);
	}
}


void engine::Scene::RemoveGameObject(const std::string& name)
{
	for (std::shared_ptr<GameObject> obj : m_Objects)
	{
		if (obj)
		{
			if (obj->GetName() == name)
			{
				auto iterator = std::find(m_Objects.begin(), m_Objects.end(), obj);
				if (iterator != m_Objects.end())
					m_Objects.erase(iterator);
				iterator = std::find(m_Triggers.begin(), m_Triggers.end(), obj);
				if (iterator != m_Triggers.end())
					m_Triggers.erase(iterator);
				for (size_t i = 0; i < m_Colliders.size(); i++)
				{
					if (m_Colliders[i]->GetGameObject()->GetName() == name)
					{
						m_Colliders.erase(m_Colliders.begin() + i);
					}
				}
				iterator = std::find(m_PlayerEnemyColliders.begin(), m_PlayerEnemyColliders.end(), obj);
				if (iterator != m_PlayerEnemyColliders.end())
					m_PlayerEnemyColliders.erase(iterator);
				obj = nullptr;
			}
		}
	}
}
void engine::Scene::RemoveAllGameObjects()
{
	m_Objects.clear();
	m_Texts.clear();
}


void Scene::Update(float deltaTime)
{
	m_FpsTimer += deltaTime;
	++m_FPSCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FpsTimer -= 1.0f;
	}

	if(m_FPSObject)
		m_FPSObject->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));

	for (size_t i = 0; i < m_Objects.size(); i++)
	{	
		if(m_Objects[i])
			m_Objects[i]->Update(deltaTime);
	}

}

void Scene::Render() const
{
	for (auto& object : m_Objects)
	{
		object->Render();
	}
}

