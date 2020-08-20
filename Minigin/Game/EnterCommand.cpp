#include "MiniginPCH.h"
#include "EnterCommand.h"
#include "SwitchingScenesComponent.h"
void EnterCommand::Execute(engine::GameObject* object)
{
	if(object->HasComponent<SwitchingScenesComponent>())
		object->GetComponent<SwitchingScenesComponent>()->ChangeSwitch(true);
}

void EnterCommand::Dexecute(engine::GameObject* object)
{
}
