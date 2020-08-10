#pragma once
#include "Command.h"
	class WalkLeftCommand : public engine::Command
	{
	public:
		WalkLeftCommand() = default;
		~WalkLeftCommand() = default;
		virtual void Execute(engine::GameObject* object);
		virtual void Dexecute(engine::GameObject* object);
	};

