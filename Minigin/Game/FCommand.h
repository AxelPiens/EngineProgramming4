#pragma once
#include <Command.h>
class FCommand : public engine::Command
{
public:
    FCommand() = default;
    ~FCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

