#include "MiniginPCH.h"
#include "KCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void KCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("K");
}

void KCommand::Dexecute(engine::GameObject* object)
{
}
