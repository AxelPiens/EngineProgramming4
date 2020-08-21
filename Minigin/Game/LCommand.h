#pragma once
#include <Command.h>
class LCommand : public engine::Command
{
public:
    LCommand() = default;
    ~LCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

