#include "MiniginPCH.h"
#include "ZCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void ZCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("Z");
}

void ZCommand::Dexecute(engine::GameObject* object)
{
}
