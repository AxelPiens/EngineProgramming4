#include "MiniginPCH.h"
#include "WCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void WCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("W");
}

void WCommand::Dexecute(engine::GameObject* object)
{
}
