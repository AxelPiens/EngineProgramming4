#include "MiniginPCH.h"
#include "BCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void BCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("B");
}

void BCommand::Dexecute(engine::GameObject* object)
{
}
