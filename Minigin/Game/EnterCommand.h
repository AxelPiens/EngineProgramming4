#pragma once
#include <Command.h>
class EnterCommand : public engine::Command
{
public:
    EnterCommand() = default;
    ~EnterCommand() = default;
    virtual void Execute(engine::GameObject * object);
    virtual void Dexecute(engine::GameObject * object);
};

