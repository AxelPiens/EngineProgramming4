#pragma once
#include <Command.h>
class BCommand : public engine::Command
{
public:
    BCommand() = default;
    ~BCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

