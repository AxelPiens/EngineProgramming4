#include "MiniginPCH.h"
#include "ControlComponent.h"
#include "TransformComponent.h"
#include <SDL.h>
#include "InputManager.h"
#include "RigidbodyComponent.h"
#include "Command.h"
ControlComponent::ControlComponent()
{
}

void ControlComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	dae::Vector3 velocity;

	auto& input = dae::InputManager::GetInstance();
	//input.ProcessInput(m_pGameObject);
	bool isReleased = false;
	dae::Command* pCommand = input.ProcessInput(isReleased);
	if (!isReleased)
	{
		if (pCommand)
			pCommand->Execute(m_pGameObject);
	}
	else
		if (pCommand)
			pCommand->Dexecute(m_pGameObject);
}

void ControlComponent::Render()
{
}
