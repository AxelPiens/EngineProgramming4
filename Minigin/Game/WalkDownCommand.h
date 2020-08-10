#pragma once
#include <Command.h>
class WalkDownCommand : public engine::Command
{
public:
	WalkDownCommand() = default;
	~WalkDownCommand() = default;
	virtual void Execute(engine::GameObject* object);
	virtual void Dexecute(engine::GameObject* object);
};

