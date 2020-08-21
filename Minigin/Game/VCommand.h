#pragma once
#include <Command.h>
class VCommand : public engine::Command
{
public:
    VCommand() = default;
    ~VCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

