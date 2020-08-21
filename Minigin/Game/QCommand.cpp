#include "MiniginPCH.h"
#include "QCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void QCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("Q");
}

void QCommand::Dexecute(engine::GameObject* object)
{
}
