#include "MiniginPCH.h"
#include "JumpCommand.h"
#include "GameObject.h"
#include "Components.h"
#include "RigidbodyComponent.h"
#include <SDL_mixer.h>

engine::JumpCommand::JumpCommand()
	:m_pSound{}
{
	m_pSound = Mix_LoadWAV("../Data/Audio/Jump.wav");
}


void engine::JumpCommand::Execute(engine::GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		if (object->GetComponent<RigidbodyComponent>()->Jump())
			Mix_PlayChannel(-1, m_pSound, 0);
	}
}

void engine::JumpCommand::Dexecute(GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
}
