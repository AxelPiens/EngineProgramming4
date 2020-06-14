#pragma once
#include "Command.h"
namespace engine
{
	class WalkLeftCommand : public Command
	{
	public:
		WalkLeftCommand() = default;
		~WalkLeftCommand() = default;
		virtual void Execute(GameObject* object);
		virtual void Dexecute(GameObject* object);
	};
}

