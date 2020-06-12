#include "MiniginPCH.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
ProjectileComponent::ProjectileComponent(float range, float speed, float liveTime, int direction)
	:m_Range{range*1000}
	, m_Speed{speed}
	, m_DistanceTraveled{0}
	, m_DeathTime{liveTime}
	, m_Direction{direction}
{
}

void ProjectileComponent::Update(float deltaTime)
{
	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed * m_Direction);
	m_DistanceTraveled += m_Speed;
	if (m_DistanceTraveled > m_Range)
	{
		//go up
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed/3);
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_DeathTime)
		{
			auto scene = dae::SceneManager::GetInstance().GetScene("Game");
			scene->RemoveGameObject("projectile" + std::to_string(m_Number));
		}
	}
}

void ProjectileComponent::Render()
{
}
