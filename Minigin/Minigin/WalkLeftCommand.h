#pragma once
#include "Command.h"
namespace dae
{
	class WalkLeftCommand : public dae::Command
	{
	public:
		WalkLeftCommand() = default;
		~WalkLeftCommand() = default;
		virtual void Execute(GameObject* object);
		virtual void Dexecute(GameObject* object);
	};
}

