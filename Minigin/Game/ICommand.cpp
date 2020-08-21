#include "MiniginPCH.h"
#include "ICommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void ICommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("I");
}

void ICommand::Dexecute(engine::GameObject* object)
{
}
