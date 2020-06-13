#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}
std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name)
{
	for (auto scene : m_Scenes)
	{
		if (scene->GetName() == name)
			return scene;
	}
	return nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::RemoveScene(const std::string& name)
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
