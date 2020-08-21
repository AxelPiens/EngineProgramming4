#pragma once
#include <Command.h>
class SCommand : public engine::Command
{
public:
    SCommand() = default;
    ~SCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

