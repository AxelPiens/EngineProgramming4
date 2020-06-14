#include "MiniginPCH.h"
#include "WalkLeftCommand.h"
#include "RigidbodyComponent.h"

void dae::WalkLeftCommand::Execute(GameObject* object)
{
	if (object->GetPlayerState() != dae::PlayerStates::Death)
	{
		if (!object->GetComponent<RigidbodyComponent>()->GetIsJumping())
			object->GetComponent<RigidbodyComponent>()->Walk(-1);
		else
			object->GetComponent<RigidbodyComponent>()->Walk(-0.25f);
		object->SetPlayerState(dae::PlayerStates::WalkLeft);
	}
}

void dae::WalkLeftCommand::Dexecute(GameObject* object)
{
	if (object->GetPlayerState() != dae::PlayerStates::Death)
	{
		object->GetComponent<RigidbodyComponent>()->Walk(0);
		object->SetPlayerState(dae::PlayerStates::Idle);
	}
}
