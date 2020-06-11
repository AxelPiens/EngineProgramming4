#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Collision.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "..\Game\EnemyAIComponent.h" 
#include <SDL.h>
using namespace dae;

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
		if(object->GetComponent<ColliderComponent>()->GetTag() != "player" && object->GetComponent<ColliderComponent>()->GetTag() != "enemy")
			m_Colliders.push_back(object->GetComponent<ColliderComponent>());
		else
			m_PlayerEnemyColliders.push_back(object);
	}
}

void dae::Scene::RemoveGameObject(const std::string& name)
{
	for (std::shared_ptr<GameObject> obj : m_Objects)
	{
		if (obj)
		{
			if (obj->GetName() == name)
			{
				auto iterator = std::find(m_Objects.begin(), m_Objects.end(), obj);
				m_Objects.erase(iterator);
				obj = nullptr;

			}
		}
	}

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

	//Collision::AABB()
	bool onGround = false;

	for (auto coll : m_Colliders)
	{
		for (auto moveColl : m_PlayerEnemyColliders)
		{
			moveColl->GetComponent<ColliderComponent>()->GetTag();
			if (moveColl->GetComponent<TransformComponent>()->GetVelocity().y >= 0)
			{
				if (Collision::AABB(moveColl->GetComponent<ColliderComponent>()->GetCollider(), coll->GetCollider())) //player colliding with something
				{
					if (!moveColl->GetComponent<RigidbodyComponent>()->GetIsJumping())
					{

						dae::Vector3 pos = moveColl->GetComponent<TransformComponent>()->GetPosition();
						if (coll->GetCollider().y <= int(pos.y) + 2 && coll->GetCollider().y >= int(pos.y) - 2)
						{
							if (coll->GetCollider().x - pos.x < 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x < 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);

							}
							else if (coll->GetCollider().x - pos.x > 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x > 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);
							}
						}
						else
						{
							moveColl->GetComponent<TransformComponent>()->SetVelocityY(0);
						}
					}
					onGround = true;
					moveColl->GetComponent<RigidbodyComponent>()->SetIsJumping(false);
				}
			}
		}
	}
	m_Objects[1]->GetComponent<RigidbodyComponent>()->SetOnGround(onGround);

	if(m_FPSObject)
		m_FPSObject->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));
	for(auto& object : m_Objects)
	{
		if(object)
			object->Update(deltaTime);
	}

}

void Scene::Render() const
{
	for (auto& object : m_Objects)
	{
		object->Render();
	}
}

