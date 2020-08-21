#include "MiniginPCH.h"
#include "TCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void TCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("T");
}

void TCommand::Dexecute(engine::GameObject* object)
{
}
