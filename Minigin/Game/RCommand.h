#pragma once
#include <Command.h>
class RCommand : public engine::Command
{
public:
    RCommand() = default;
    ~RCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

