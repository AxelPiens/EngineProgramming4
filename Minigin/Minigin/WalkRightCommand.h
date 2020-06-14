#pragma once
#include "Command.h"
namespace engine
{
	class WalkRightCommand : public Command
	{
	public:
		WalkRightCommand() = default;
		~WalkRightCommand() = default;
		virtual void Execute(GameObject * object);
		virtual void Dexecute(GameObject * object);
	};
}

