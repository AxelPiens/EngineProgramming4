#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
RigidbodyComponent::RigidbodyComponent(float accelGrav, float maxGrav, float jumpForce, float moveSpeed)
	: m_AccelGrav{accelGrav}
	,m_MaxGrav{maxGrav}
	,m_JumpForce{jumpForce}
	, m_MoveSpeed{moveSpeed}
{
}

void RigidbodyComponent::Jump()
{
	if (!m_IsJumping)
	{
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_JumpForce);
		m_IsJumping = true;
	}
}

void RigidbodyComponent::Walk(float velX)
{
	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_MoveSpeed*velX);
}

void RigidbodyComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	
	if (!m_OnGround)
	{
		dae::Vector3 vel = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity();
		vel.y += m_AccelGrav;
		if (vel.y > m_MaxGrav)
			vel.y = m_MaxGrav ;
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocity(vel);
	}
}

void RigidbodyComponent::Render()
{
}
