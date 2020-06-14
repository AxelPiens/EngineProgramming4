#include "MiniginPCH.h"
#include "WalkRightCommand.h"
#include "RigidbodyComponent.h"

void dae::WalkRightCommand::Execute(dae::GameObject* object)
{
	if (object->GetPlayerState() != dae::PlayerStates::Death)
	{
		if (!object->GetComponent<RigidbodyComponent>()->GetIsJumping())
			object->GetComponent<RigidbodyComponent>()->Walk(1);
		else
			object->GetComponent<RigidbodyComponent>()->Walk(0.25f);
		object->SetPlayerState(dae::PlayerStates::WalkRight);
	}

}

void dae::WalkRightCommand::Dexecute(dae::GameObject* object)
{
	if (object->GetPlayerState() != dae::PlayerStates::Death)
	{
		object->GetComponent<RigidbodyComponent>()->Walk(0);
		object->SetPlayerState(dae::PlayerStates::Idle);
	}

}
