#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>
#include "../component/Component.h"

using ComponentID = std::type_index;

class Entity {
	public:
		template<typename T, typename... Args>
		void addComponent(Args&&... args) {
			components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		T* getComponent() {
			auto it = components.find(typeid(T));
			if (it != components.end()) {
				return static_cast<T*>(it->second.get());
			}
			return nullptr;
		}

		template<typename T>
		const T* getComponent() const {
			auto it = components.find(typeid(T));
			if (it != components.end()) {
				return static_cast<const T*>(it->second.get());
			}
			return nullptr;
		}

		template<typename T>
		bool hasComponent() const {
			return components.find(typeid(T)) != components.end();
		}

	private:
		std::unordered_map<ComponentID, std::shared_ptr<Component>> components;
};
