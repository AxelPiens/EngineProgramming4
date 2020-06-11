#pragma once
#include "BaseComponent.h"
#include "Vector3.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
	TransformComponent(float speed);
	TransformComponent(int width, int height, float speed);
	void Translate(dae::Vector3 vec);
	void Translate(float x, float y, float z);
	void Move(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);
	const int GetHeight() const {return m_Height;};
	const int GetWidth() const { return m_Width; };
	const dae::Vector3& GetVelocity() const { return m_Velocity; };
	void SetVelocity(const dae::Vector3& velocity) { m_Velocity = velocity; };
	void SetVelocityY(float y) { m_Velocity.y = y; };
	void SetVelocityX(float x) { m_Velocity.x = x; };
	const dae::Vector3& GetPosition() const { return m_Position; }
	const dae::Vector3& GetScale() const { return m_Scale; }
	const dae::Vector3& GetRotation() const { return m_Rotation; }
	const dae::Vector3& GetForward() const { return m_Forward; }
	const dae::Vector3& GetUp() const { return m_Up; }
	const dae::Vector3& GetRight() const { return m_Right; }
	
protected:
	void Update(float deltaTime) override;
	void Render() override;

private:
	dae::Vector3 m_Position;
	dae::Vector3 m_Rotation;
	dae::Vector3 m_Scale;
	dae::Vector3 m_Forward;
	dae::Vector3 m_Right;
	dae::Vector3 m_Up;

	int m_Height = 0;
	int m_Width = 0;
	float m_Speed = 5;
	dae::Vector3 m_Velocity;
};

