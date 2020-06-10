#include "MiniginPCH.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"
ProjectileComponent::ProjectileComponent(float range, float speed)
	:m_Range{range}
	, m_Speed{speed}
	, m_DistanceTraveled{0}
{
}

void ProjectileComponent::Update(float deltaTime)
{
	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
	m_DistanceTraveled += m_Speed;
	if (m_DistanceTraveled > m_Range)
	{
		//go up
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed/3);

	}
}

void ProjectileComponent::Render()
{
}
