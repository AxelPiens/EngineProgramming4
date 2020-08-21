#pragma once
#include <Command.h>
class ACommand : public engine::Command
{
public:
    ACommand() = default;
    ~ACommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

