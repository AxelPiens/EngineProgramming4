#include "MiniginPCH.h"
#include "ECommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void ECommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("E");
}

void ECommand::Dexecute(engine::GameObject* object)
{
}
