#include "MiniginPCH.h"
#include "ACommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void ACommand::Execute(engine::GameObject* object)
{
	
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("A");
}

void ACommand::Dexecute(engine::GameObject* object)
{
}
