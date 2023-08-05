#pragma once

#include <vector>

#include "Entity.h"

using EntityVector = std::vector<Entity>;
using EntityMap = std::map<std::string, EntityVector>;

class EntityManager {
public:
    void Update();

    Entity AddEntity(const std::string& tag = "default");
    EntityVector& GetEntitiesByTag(const std::string& tag);
    EntityVector& GetAllEntities();
private:
    void RemoveDeadEntities();

    EntityId nextId = 0;
    EntityVector entities;
    EntityVector entitiesToAdd;
    EntityVector entitiesToRemove;
    EntityMap entitiesByTag;
};