#include "MiniginPCH.h"
#include "LiveComponent.h"

LiveComponent::LiveComponent(int amountOfLives)
	:m_AmountOfLives{amountOfLives}
{
}

void LiveComponent::LoseLive()
{
	--m_AmountOfLives;
	m_pGameObject->SetPlayerState(dae::PlayerStates::Death);
}

void LiveComponent::Update(float deltaTime)
{
	if (m_AmountOfLives == 0)
	{
		std::cout << "death\n";
	}
}

void LiveComponent::Render()
{
}
