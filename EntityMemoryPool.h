#pragma once

#include "Components.h"

// Forward declaration
class Entity;

// Singleton class for managing entity memory
class EntityMemoryPool {
public:
    // Singleton implementation
    EntityMemoryPool(const EntityMemoryPool&) = delete;
    EntityMemoryPool& operator=(const EntityMemoryPool&) = delete;
    EntityMemoryPool(EntityMemoryPool&&) = delete;
    EntityMemoryPool& operator=(EntityMemoryPool&&) = delete;
    static EntityMemoryPool& Instance() {
        static EntityMemoryPool instance{MAX_ENTITITES};
        return instance;
    }

    Entity AddEntity(const std::string &tag);
    template<typename T>
    T& GetComponent(EntityId id) {
        return std::get<std::vector<T>>(pool)[id];
    }
    template<typename T>
    bool HasComponent(EntityId id) {
        return std::get<std::vector<T>>(pool)[id].Has();
    }
    template<typename T, typename... TArgs>
    T& AddComponent(EntityId id, TArgs... args) {
        auto& componentVec = std::get<std::vector<T>>(pool);
        ASSERT(componentVec.size() < id || componentVec[id].Has() == false, "Component already exists");
        componentVec.emplace_back(args...);
        auto& component = componentVec.back();
        component.SetHas(true);
        return component;
    }
    template<typename T>
    void RemoveComponent(EntityId id) {
        auto component = GetComponent<T>(id);
        ASSERT(component.Has() == true, "Component does not exist");
        component.SetHas(false);
    }

    const std::string& GetTag(EntityId id) const {
        return tags[id];
    }
    bool IsActive(EntityId id) const {
        return active[id];
    }
    void SetInactive(EntityId id) {
        active[id] = false;
    }

protected:
    EntityMemoryPool(EntityId maxEntities);

private:
    EntityId GetNextEntityIndex();

    ComponentPool pool;
    std::vector<std::string> tags;
    // TODO(tcare): change to a bitset and track the first inactive location. Alternatively change to a queue
    std::vector<bool> active;
};