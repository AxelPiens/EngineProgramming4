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
		void Translate(engine::Vector3 vec);
		void Translate(float x, float y, float z);
		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void Scale(float x, float y, float z);
		const int GetHeight() const { return m_Height; };
		const int GetWidth() const { return m_Width; };
		const engine::Vector3& GetVelocity() const { return m_Velocity; };
		void SetVelocity(const engine::Vector3& velocity) { m_Velocity = velocity; };
		void SetVelocityY(float y) { m_Velocity.y = y; };
		void SetVelocityX(float x) { m_Velocity.x = x; };
		const engine::Vector3& GetPosition() const { return m_Position; }
		const engine::Vector3& GetScale() const { return m_Scale; }
		const engine::Vector3& GetRotation() const { return m_Rotation; }
		const engine::Vector3& GetForward() const { return m_Forward; }
		const engine::Vector3& GetUp() const { return m_Up; }
		const engine::Vector3& GetRight() const { return m_Right; }
		int GetDirection() const { return m_Direction; };
	protected:
		void Update(float deltaTime) override;
		void Render() override;

	private:
		engine::Vector3 m_Position;
		engine::Vector3 m_Rotation;
		engine::Vector3 m_Scale;
		engine::Vector3 m_Forward;
		engine::Vector3 m_Right;
		engine::Vector3 m_Up;

		int m_Height = 0;
		int m_Width = 0;
		float m_Speed = 5;
		engine::Vector3 m_Velocity;
		int m_Direction = 1;

		bool m_MoveTowards = false;
	};

