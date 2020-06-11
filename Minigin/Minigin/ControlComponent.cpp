#include "MiniginPCH.h"
#include "ControlComponent.h"
#include "TransformComponent.h"
#include <SDL.h>
#include "InputManager.h"
#include "RigidbodyComponent.h"
ControlComponent::ControlComponent()
{
}

void ControlComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	dae::Vector3 velocity;

	auto& input = dae::InputManager::GetInstance();
	input.ProcessInput(m_pGameObject);

	//if (m_pGameObject->GetComponent<RigidbodyComponent>()->GetOnGround() == false)
	//	velocity.y = 0;
	//else if (velocity.y < 0)
	//{
	//	m_pGameObject->GetComponent<RigidbodyComponent>()->SetIsJumping(true);
	//	velocity.y *= 50;
	//}
	//m_pGameObject->GetComponent<TransformComponent>()->SetVelocity(velocity);
}

void ControlComponent::Render()
{
}
