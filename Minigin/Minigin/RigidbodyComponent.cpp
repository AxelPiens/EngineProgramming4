#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
RigidbodyComponent::RigidbodyComponent(float accelGrav, float maxGrav)
	: m_AccelGrav{accelGrav}
	,m_MaxGrav{maxGrav}
{
}

void RigidbodyComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	
	if (!m_OnGround)
	{
		dae::Vector3 vel = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity();
		vel.y += m_AccelGrav * deltaTime;
		if (vel.y > m_MaxGrav)
			vel.y = m_MaxGrav * deltaTime;
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocity(vel);
	}
}

void RigidbodyComponent::Render()
{
}
