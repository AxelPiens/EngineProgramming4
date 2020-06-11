#include "MiniginPCH.h"
#include "EnemyAIComponent.h"
#include "TransformComponent.h"

EnemyAIComponent::EnemyAIComponent(float speed)
	:m_Speed{speed},
	m_OldPos{0,0,0}
{


}

void EnemyAIComponent::Update(float deltaTime)
{
	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
}

void EnemyAIComponent::Render()
{
}
