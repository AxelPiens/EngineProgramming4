#include "MiniginPCH.h"
#include "WalkRightCommand.h"
#include "RigidbodyComponent.h"

void engine::WalkRightCommand::Execute(engine::GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		if (!object->GetComponent<RigidbodyComponent>()->GetIsJumping())
			object->GetComponent<RigidbodyComponent>()->Walk(1);
		else
			object->GetComponent<RigidbodyComponent>()->Walk(0.25f);
		object->SetPlayerState(engine::PlayerStates::WalkRight);
	}

}

void engine::WalkRightCommand::Dexecute(engine::GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		object->GetComponent<RigidbodyComponent>()->Walk(0);
		object->SetPlayerState(engine::PlayerStates::Idle);
	}

}
