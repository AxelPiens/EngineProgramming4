#include "MiniginPCH.h"
#include "FCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void FCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("F");
}

void FCommand::Dexecute(engine::GameObject* object)
{
}
