#pragma once
#include <Command.h>
class JCommand : public engine::Command
{
public:
    JCommand() = default;
    ~JCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

