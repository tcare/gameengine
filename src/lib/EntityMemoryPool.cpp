#include "EntityMemoryPool.h"

#include "Entity.h"

Entity EntityMemoryPool::AddEntity(const std::string &tag){
    // Get next inactive index
    const EntityId nextId = GetNextEntityIndex();
    
    // Initialize components
    // auto setActive = [index = nextId](auto& component) {
    //     component[index].SetHas(true);
    // };
    // std::apply([&setActive](auto&... components) { (setActive(components), ...); }, pool);

    // Initialize tag
    tags[nextId] = tag;

    // Set active
    active[nextId] = true;

    // Return constructed Entity using nextId
    return {nextId};
}

EntityId EntityMemoryPool::GetNextEntityIndex() {
    // There are certainly more efficient ways to track inactive entities depending on usage patterns.
    // For the moment, just find the first inactive entity.
    auto it = std::find(active.begin(), active.end(), false);
    return std::distance(active.begin(), it);
}

EntityMemoryPool::EntityMemoryPool(EntityId maxEntities) {
    std::apply([maxEntities](auto&... vec) { ((vec.reserve(maxEntities)), ...); }, pool);

    // Initialize tags
    tags.resize(maxEntities);

    // Initialize active
    active.resize(maxEntities);
}