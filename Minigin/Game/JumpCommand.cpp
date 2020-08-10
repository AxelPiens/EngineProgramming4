#include "MiniginPCH.h"
#include "JumpCommand.h"
#include "GameObject.h"
#include "Components.h"
#include "RigidbodyComponent.h"
#include <SDL_mixer.h>

JumpCommand::JumpCommand()
	:m_pSound{}
{
	m_pSound = Mix_LoadWAV("../Data/Audio/Jump.wav");
}


void JumpCommand::Execute(engine::GameObject* object)
{
	if (object->GetComponent<RigidbodyComponent>()->Jump())
		Mix_PlayChannel(-1, m_pSound, 0);
}

void JumpCommand::Dexecute(engine::GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
}
