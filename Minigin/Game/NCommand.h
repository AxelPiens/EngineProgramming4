#pragma once
#include <Command.h>
class NCommand : public engine::Command
{
public:
    NCommand() = default;
    ~NCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

