#pragma once
#include <Command.h>
class WCommand : public engine::Command
{
public:
    WCommand() = default;
    ~WCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

