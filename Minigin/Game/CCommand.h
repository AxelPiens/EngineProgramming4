#pragma once
#include <Command.h>
class CCommand : public engine::Command
{
public:
    CCommand() = default;
    ~CCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

