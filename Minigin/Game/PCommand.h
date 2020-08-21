#pragma once
#include <Command.h>
class PCommand : public engine::Command
{
public:
    PCommand() = default;
    ~PCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

