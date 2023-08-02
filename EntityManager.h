#pragma once

#include <vector>

#include "Entity.h"

using EntityPtr = std::shared_ptr<Entity>;
using EntityVector = std::vector<EntityPtr>;
using EntityMap = std::map<std::string, EntityVector>;

class EntityManager {
public:
    void Update();

    EntityPtr AddEntity(const std::string& tag = "default");
    const EntityVector& GetEntitiesByTag(const std::string& tag);
    const EntityVector& GetAllEntities();
private:
    void RemoveDeadEntities();

    EntityId nextId = 0;
    EntityVector entities;
    EntityVector entitiesToAdd;
    EntityVector entitiesToRemove;
    EntityMap entitiesByTag;
};