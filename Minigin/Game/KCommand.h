#pragma once
#include <Command.h>
class KCommand : public engine::Command
{
public:
    KCommand() = default;
    ~KCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

