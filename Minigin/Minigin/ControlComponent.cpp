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
	engine::Vector3 velocity;

	auto& input = engine::InputManager::GetInstance();
	bool isReleased = false;
	engine::Command* command = input.ProcessInput(isReleased);
	if (!isReleased)
	{
		if (command)
		{
			command->Execute(m_pGameObject);
		}
	}
	else
	{
		if (command)
		{
			command->Dexecute(m_pGameObject);
		}

	}
}

void ControlComponent::Render()
{
}
