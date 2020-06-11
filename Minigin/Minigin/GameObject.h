#pragma once
#include "SceneObject.h"
class BaseComponent;

namespace dae
{
	class GameObject : public SceneObject 
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		GameObject(const std::string& name)
			: m_Name{ name } {};
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);
		std::string GetName() { return m_Name; };
		template <class T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

		template <class T>
		std::vector<T*> GetComponents()
		{
			const type_info& ti = typeid(T);
			std::vector<T*> components;

			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					components.push_back(static_cast<T*>(component));
			}

			return components;
		}

	private:
		std::vector<BaseComponent*> m_pComponents;
		std::string m_Name;
	};
}
