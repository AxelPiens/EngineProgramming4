#pragma once
#include <Command.h>
class TCommand : public engine::Command
{
public:
    TCommand() = default;
    ~TCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

