#pragma once
#include "Command.h"
class WalkRightCommand : public engine::Command
{
public:
	WalkRightCommand() = default;
	~WalkRightCommand() = default;
	virtual void Execute(engine::GameObject* object);
	virtual void Dexecute(engine::GameObject* object);
};

