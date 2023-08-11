#pragma once

#include "Components.h"
#include "EntityMemoryPool.h"

class Entity {
public:
    Entity(EntityId id)
    : id(id) {}

    void Update();
    
    // An inactive entity will be removed on the next frame.
    void SetInactive() { EntityMemoryPool::Instance().SetInactive(id); }

    [[nodiscard]] EntityId GetId() const { return id; }

    template<typename T>
    T& GetComponent() {
        return EntityMemoryPool::Instance().GetComponent<T>(id);
    }
    template<typename T>
    bool HasComponent() const {
        return EntityMemoryPool::Instance().HasComponent<T>(id);
    }
    template<typename T, typename... TArgs>
    T& AddComponent(TArgs... args) {
        return EntityMemoryPool::Instance().AddComponent<T>(id, std::forward<TArgs>(args)...);
    }

    [[nodiscard]] bool IsActive() const { return EntityMemoryPool::Instance().IsActive(id); }
    [[nodiscard]] const std::string& GetTag() const { return EntityMemoryPool::Instance().GetTag(id); }
private:
    EntityId id;
};

static_assert(sizeof(Entity) == sizeof(EntityId), "Passing around entities should be no worse than passing around entity ids.");
