#pragma once
#include <Command.h>
class WalkUpCommand : public engine::Command
{
public:
	WalkUpCommand() = default;
	~WalkUpCommand() = default;
	virtual void Execute(engine::GameObject * object);
	virtual void Dexecute(engine::GameObject * object);

};

