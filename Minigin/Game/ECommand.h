#pragma once
#include <Command.h>
class ECommand : public engine::Command
{
public:
    ECommand() = default;
    ~ECommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

