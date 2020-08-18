#include "MiniginPCH.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collision.h"
ProjectileComponent::ProjectileComponent(float range, float speed, float liveTime, int direction, bool goingUp)
	:m_Range{range*1000}
	, m_Speed{speed}
	, m_DistanceTraveled{0}
	, m_DeathTime{liveTime}
	, m_Direction{direction}
	, m_ElapsedTime{0.0f}
	, m_Number{0}
	, m_IsGoingUp{goingUp}
{
}

void ProjectileComponent::Update(float deltaTime)
{
	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed * m_Direction);
	m_DistanceTraveled += m_Speed;
	if (m_DistanceTraveled > m_Range)
	{
		//go up
		if (m_IsGoingUp)
		{
			m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
			m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed / 3);
			m_ElapsedTime += deltaTime;
			if (m_ElapsedTime > m_DeathTime)
			{
				auto scene = engine::SceneManager::GetInstance().GetScene("Game");
				scene->RemoveGameObject("projectile" + std::to_string(m_Number));
			}
		}
		else
		{
			auto scene = engine::SceneManager::GetInstance().GetScene("Game");
			scene->RemoveGameObject("boulder" + std::to_string(m_Number));
		}
	}
	CheckForBlock();
}

void ProjectileComponent::Render()
{
}

void ProjectileComponent::CheckForBlock()
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();
	for (auto trigger : triggers)
	{
		if (trigger->GetName().find("level") != std::string::npos)
		{
			if (engine::Collision::AABB(*trigger->GetComponent<ColliderComponent>(), *m_pGameObject->GetComponent<ColliderComponent>()))
			{
				scene->RemoveGameObject(m_pGameObject->GetName());
				break;
			}
		}
	}
	for (auto col : colliders)
	{
		if (col->GetGameObject()->GetName().find("level") != std::string::npos)
		{
			if (engine::Collision::AABB(*col, *m_pGameObject->GetComponent<ColliderComponent>()))
			{
				scene->RemoveGameObject(m_pGameObject->GetName());
				break;
			}
		}
	}
}