#pragma once
#include <Command.h>
class DCommand : public engine::Command
{
public:
    DCommand() = default;
    ~DCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};
