#include "MiniginPCH.h"
#include "WalkLeftCommand.h"
#include "RigidbodyComponent.h"

void engine::WalkLeftCommand::Execute(GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		if (!object->GetComponent<RigidbodyComponent>()->GetIsJumping())
			object->GetComponent<RigidbodyComponent>()->Walk(-1);
		else
			object->GetComponent<RigidbodyComponent>()->Walk(-0.25f);
		object->SetPlayerState(engine::PlayerStates::WalkLeft);
	}
}

void engine::WalkLeftCommand::Dexecute(GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		object->GetComponent<RigidbodyComponent>()->Walk(0);
		object->SetPlayerState(engine::PlayerStates::Idle);
	}
}
