#include "EntityManager.h"

void EntityManager::Update() {
    // Add all queued entities
    if (!entitiesToAdd.empty()) {
        SPDLOG_TRACE("Adding {} queued entities", entitiesToAdd.size());
    }
    for (auto const& entity : entitiesToAdd) {
        entities.push_back(entity);
        entitiesByTag[entity.GetTag()].push_back(entity);
    }
    entitiesToAdd.clear();

    RemoveDeadEntities();
}

Entity EntityManager::AddEntity(const std::string &tag) {
    Entity entity = EntityMemoryPool::Instance().AddEntity(tag);
    entitiesToAdd.push_back(entity);
    SPDLOG_TRACE("Queueing entity {} with tag {} for addition next frame", entity.GetId(), entity.GetTag());
    nextId++;
    return entity;
}

EntityVector& EntityManager::GetAllEntities() {
    return entities;
}

void EntityManager::RemoveDeadEntities() {
    std::erase_if(entities, [](const Entity& entity) {
        return !entity.IsActive();
    });
}
