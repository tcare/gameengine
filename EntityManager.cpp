#include "EntityManager.h"

void EntityManager::Update() {
    // Add all queued entities
    if (!entitiesToAdd.empty()) {
        SPDLOG_TRACE("Adding {} queued entities", entitiesToAdd.size());
    }
    for (auto entity : entitiesToAdd) {
        entities.push_back(entity);
        entitiesByTag[entity->GetTag()].push_back(entity);
    }
    entitiesToAdd.clear();

    RemoveDeadEntities();
}

EntityPtr EntityManager::AddEntity(const std::string &tag) {
    EntityPtr entity = std::make_shared<Entity>(nextId, tag);
    entitiesToAdd.push_back(entity);
    SPDLOG_TRACE("Queueing entity {} with tag {} for addition next frame", entity->GetId(), entity->GetTag());
    nextId++;
    return entity;
}

const EntityVector& EntityManager::GetAllEntities() {
    return entities;
}

void EntityManager::RemoveDeadEntities() {
    std::erase_if(entities, [](EntityPtr entity) {
        return !entity->IsActive();
    });
}
