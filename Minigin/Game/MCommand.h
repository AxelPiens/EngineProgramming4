#pragma once
#include <Command.h>
class MCommand : public engine::Command
{
public:
    MCommand() = default;
    ~MCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

