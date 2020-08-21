#pragma once
#include <Command.h>
class QCommand : public engine::Command
{
public:
    QCommand() = default;
    ~QCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

