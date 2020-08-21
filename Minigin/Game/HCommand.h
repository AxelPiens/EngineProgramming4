#pragma once
#include <Command.h>
class HCommand : public engine::Command
{
public:
    HCommand() = default;
    ~HCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

