#include "MiniginPCH.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collision.h"
#include "ScoreComponent.h"

ProjectileComponent::ProjectileComponent(float range, float speed, float liveTime, engine::Vector3 direction, bool goingUp)
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



	m_pGameObject->GetComponent<TransformComponent>()->SetVelocity(engine::Vector3( m_Direction * m_Speed));

	std::cout << m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().x << " " << m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().y << std::endl;
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
	auto players = scene->GetPlayers();

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
		else if (trigger->GetName().find("spider") != std::string::npos)
		{
			if (engine::Collision::AABB(*trigger->GetComponent<ColliderComponent>(), *m_pGameObject->GetComponent<ColliderComponent>()))
			{
				players[0]->GetComponent<ScoreComponent>()->AddScore(trigger);
				scene->RemoveGameObject(trigger->GetName());
				scene->RemoveGameObject(m_pGameObject->GetName());
				break;
			}
		}
	}
	for (auto col : colliders)
	{
		if (col)
		{
			if (!col->GetIsTrigger())
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
	}
}