#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <string>
	class TransformComponent;
	class ColliderComponent : public BaseComponent
	{

	public:
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

		ColliderComponent(std::string tag, bool isTrigger, int changeX, int changeY);
		~ColliderComponent();
		const std::string& GetTag()const { return m_Tag; };
		const SDL_Rect& GetCollider() const { return m_Collider; };
		bool GetIsTrigger() const { return m_IsTrigger; };
		void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; };
		void SetSizeX(int sizeX) { m_SizeX = sizeX; };
		void SetSizeY(int sizeY) { m_SizeY = sizeY; };
	protected:
		void Update(float deltaTime) override;
		void Render() override;
	private:
		SDL_Rect m_Collider;
		std::string m_Tag;
		bool m_IsTrigger = false;
		int m_ChangeX;
		int m_ChangeY;
		int m_SizeX;
		int m_SizeY;
	};

