#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void engine::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void engine::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}
std::shared_ptr<engine::Scene> engine::SceneManager::GetScene(const std::string& name)
{
	for (auto scene : m_Scenes)
	{
		if (scene->GetName() == name)
			return scene;
	}
	return nullptr;
}

engine::Scene& engine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void engine::SceneManager::RemoveScene(const std::string& name)
{
	for (auto scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			auto iterator = std::find(m_Scenes.begin(), m_Scenes.end(), scene);
			if (iterator != m_Scenes.end())
				m_Scenes.erase(iterator);
		}
	}
}
