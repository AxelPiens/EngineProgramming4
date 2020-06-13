#include "MiniginPCH.h"
#include "EnemyAIComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"

EnemyAIComponent::EnemyAIComponent(float speed)
	:m_Speed{speed},
	m_OldPos{0,0,0}
{
}

void EnemyAIComponent::Update(float deltaTime)
{
	if(m_pGameObject->GetComponent<RigidbodyComponent>()->GetOnGround())
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
	else
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed/6);

}

void EnemyAIComponent::Render()
{
}
