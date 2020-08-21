#pragma once
#include <Command.h>
class OCommand : public engine::Command
{
public:
    OCommand() = default;
    ~OCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

