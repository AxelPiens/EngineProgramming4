#include "MiniginPCH.h"
#include "LiveComponent.h"
#include "TransformComponent.h"
LiveComponent::LiveComponent(int amountOfLives, float deathTime)
	:m_AmountOfLives{amountOfLives}
	, m_DeathTime{deathTime}
	, m_ElapsedTime{0.0f}
{

}

void LiveComponent::LoseLive()
{
	--m_AmountOfLives;
	m_pGameObject->SetPlayerState(engine::PlayerStates::Death);
}

void LiveComponent::Init()
{
	m_SpawnPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
}

void LiveComponent::Update(float deltaTime)
{
	if (m_pGameObject->GetPlayerState() == engine::PlayerStates::Death)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_DeathTime)
		{
			m_ElapsedTime = 0.0f;
			m_pGameObject->GetComponent<TransformComponent>()->Translate(m_SpawnPos);
			m_pGameObject->SetPlayerState(engine::PlayerStates::Idle);
		}

	}
	if (m_AmountOfLives == 0)
		m_IsDeath = true;
}

void LiveComponent::Render()
{
}
