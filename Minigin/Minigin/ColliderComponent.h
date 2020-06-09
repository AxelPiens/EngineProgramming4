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

	ColliderComponent(std::string tag);
	~ColliderComponent();
	const std::string& GetTag()const { return m_Tag; };
	const SDL_Rect& GetCollider() const { return m_Collider; };

protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	SDL_Rect m_Collider;
	std::string m_Tag;
};

