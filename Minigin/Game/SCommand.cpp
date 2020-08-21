#include "MiniginPCH.h"
#include "SCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void SCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("S");
}

void SCommand::Dexecute(engine::GameObject* object)
{
}
