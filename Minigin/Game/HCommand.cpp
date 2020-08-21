#include "MiniginPCH.h"
#include "HCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void HCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("H");
}

void HCommand::Dexecute(engine::GameObject* object)
{
}
