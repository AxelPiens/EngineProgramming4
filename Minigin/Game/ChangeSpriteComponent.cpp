#include "MiniginPCH.h"
#include "ChangeSpriteComponent.h"
#include "SpriteComponent.h"

ChangeSpriteComponent::ChangeSpriteComponent()
{
	m_LastState = PlayerState::Nothing;
}

void ChangeSpriteComponent::Update(float deltaTime)
{
	PlayerState currentState = m_pGameObject->GetComponent<StateComponent>()->GetState();
	if (currentState == PlayerState::Idle && currentState != m_LastState)
	{
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(false);
	}
	else if (currentState == PlayerState::WalkDown && currentState != m_LastState)
	{
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
	}
	else if (currentState == PlayerState::WalkUp && currentState != m_LastState)
	{
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(27);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
	}
	else if (currentState == PlayerState::WalkRight && currentState != m_LastState)
	{
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(54);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
	}
	else if (currentState == PlayerState::WalkLeft && currentState != m_LastState)
	{
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(81);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeXPos(0);
		m_pGameObject->GetComponent<SpriteComponent>()->ChangeAnimated(true);
	}
	m_LastState = currentState;
}

void ChangeSpriteComponent::Render()
{
}
