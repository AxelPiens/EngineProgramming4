#include "MiniginPCH.h"
#include "OCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void OCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("O");
}

void OCommand::Dexecute(engine::GameObject* object)
{
}
