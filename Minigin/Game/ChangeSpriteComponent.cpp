#include "MiniginPCH.h"
#include "ChangeSpriteComponent.h"
#include "ShootComponent.h"

ChangeSpriteComponent::ChangeSpriteComponent()
{
	m_LastState = PlayerState::Nothing;
}

void ChangeSpriteComponent::Update(float deltaTime)
{
	if (m_pGameObject->GetName().find("player") != std::string::npos)
	{
		PlayerState currentState = m_pGameObject->GetComponent<StateComponent>()->GetPlayerState();
		if (currentState == PlayerState::Idle && currentState != m_LastState)
		{
			if (m_pGameObject->GetComponent<ShootComponent>()->CanShoot())
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(135);
			else
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(false);
		}
		else if (currentState == PlayerState::WalkDown && currentState != m_LastState)
		{
			if (m_pGameObject->GetComponent<ShootComponent>()->CanShoot())
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(135);
			else
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
		}
		else if (currentState == PlayerState::WalkUp && currentState != m_LastState)
		{
			if (m_pGameObject->GetComponent<ShootComponent>()->CanShoot())
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(162);
			else
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(27);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
		}
		else if (currentState == PlayerState::WalkRight && currentState != m_LastState)
		{
			if (m_pGameObject->GetComponent<ShootComponent>()->CanShoot())
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(189);
			else
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(54);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
		}
		else if (currentState == PlayerState::WalkLeft && currentState != m_LastState)
		{
			if (m_pGameObject->GetComponent<ShootComponent>()->CanShoot())
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(216);
			else
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(81);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
		}
		else if (currentState == PlayerState::Death && currentState != m_LastState)
		{
			if (m_pGameObject->GetComponent<ShootComponent>()->CanShoot())
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(243);
			else
				m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(108);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
			m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
		}

		m_LastState = currentState;
	}
}

void ChangeSpriteComponent::Render()
{
}
