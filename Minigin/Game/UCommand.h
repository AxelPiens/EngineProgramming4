#pragma once
#include <Command.h>
class UCommand : public engine::Command
{
public:
    UCommand() = default;
    ~UCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

