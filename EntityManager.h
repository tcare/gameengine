#pragma once

#include <vector>

#include "Entity.h"

typedef std::shared_ptr<Entity> EntityPtr;
typedef std::vector<EntityPtr> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

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