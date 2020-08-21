#pragma once
#include <Command.h>
class GCommand : public engine::Command
{
public:
    GCommand() = default;
    ~GCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

