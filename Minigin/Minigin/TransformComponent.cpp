#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(float speed)
	:m_Position{0,0,0},
	m_Rotation{0,0,0},
	m_Forward{0,1,0},
	m_Up{0,0,1},
	m_Right{1,0,0},
	m_Scale{1,1,1},
	m_Velocity{ 0,0,0 },
	m_Speed{ speed }

{
}

TransformComponent::TransformComponent(int width, int height, float speed)
	:m_Width{width}
	, m_Height{height}
	, m_Velocity{ 0,0,0}
	, m_Speed{speed}
	,m_Scale{ 1,1,1 }

{
}

void TransformComponent::Translate(engine::Vector3 vec)
{
	Translate(vec.x, vec.y, vec.z);
}


void TransformComponent::Translate(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::Move(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}


void TransformComponent::Rotate(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

void TransformComponent::Scale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

void TransformComponent::Update(float deltaTime)
{
	if (m_Velocity.x < 0)
		m_Direction = -1;
	if (m_Velocity.x > 0)
		m_Direction = 1;
	m_Position.x += m_Velocity.x * deltaTime;
	m_Position.y += m_Velocity.y * deltaTime;
}

void TransformComponent::Render()
{
}
