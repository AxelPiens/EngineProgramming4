#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Collision.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::AddGameobject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	if (object->HasComponent<ColliderComponent>())
	{
		if(object->GetComponent<ColliderComponent>()->GetTag() != "player")
			m_Colliders.push_back(object->GetComponent<ColliderComponent>());
	}
}


void Scene::Update(float deltaTime)
{
	m_FpsTimer += deltaTime;
	++m_FPSCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FpsTimer -= 1.0f;
	}
	m_Objects[2]->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	//Collision::AABB()
	bool onGround = false;

	for (auto coll : m_Colliders)
	{
		m_Objects[1]->GetComponent<ColliderComponent>()->GetTag();
		if (Collision::AABB(m_Objects[1]->GetComponent<ColliderComponent>()->GetCollider(), coll->GetCollider())) //player colliding with something
		{
			m_Objects[3]->GetComponent<TextComponent>()->SetText("HIT");
			if(!m_Objects[1]->GetComponent<RigidbodyComponent>()->GetIsJumping())
				m_Objects[1]->GetComponent<TransformComponent>()->SetVelocityY(0);
			onGround = true;
			m_Objects[1]->GetComponent<RigidbodyComponent>()->SetIsJumping(false);
		}
		else
		{
			m_Objects[3]->GetComponent<TextComponent>()->SetText("pff");
		}
	}
	m_Objects[1]->GetComponent<RigidbodyComponent>()->SetOnGround(onGround);

}

void Scene::Render() const
{
	for (auto& object : m_Objects)
	{
		object->Render();
	}
}

