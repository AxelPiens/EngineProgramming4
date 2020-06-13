#include "MiniginPCH.h"
#include "JumpCommand.h"
#include "GameObject.h"
#include "Components.h"
#include "RigidbodyComponent.h"
#include <SDL_mixer.h>

dae::JumpCommand::JumpCommand()
	:m_pSound{}
{
	m_pSound = Mix_LoadWAV("../Data/Audio/Jump.wav");
}


void dae::JumpCommand::Execute(dae::GameObject* object)
{
	
	if(object->GetComponent<RigidbodyComponent>()->Jump())
		Mix_PlayChannel(-1, m_pSound, 0);
}

void dae::JumpCommand::Dexecute(GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
}