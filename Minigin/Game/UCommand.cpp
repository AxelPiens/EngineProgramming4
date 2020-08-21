#include "MiniginPCH.h"
#include "UCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void UCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("U");
}

void UCommand::Dexecute(engine::GameObject* object)
{
}
