#include "MiniginPCH.h"
#include "MCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void MCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("M");
}

void MCommand::Dexecute(engine::GameObject* object)
{
}
