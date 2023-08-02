#pragma once

#include <string>
#include "Components.h"
#include "CommonDefines.h"

class Entity {
public:
    Entity(EntityId id, std::string tag) : id(id), tag(tag) {
    }

    void Update();
    
    // An inactive entity will be removed on the next frame.
    void SetInactive() { active = false; }

    const EntityId GetId() const { return id; }
    const std::string& GetTag() const { return tag; }
    bool IsActive() const { return active; }

    // TODO(tcare): Move these to a component manager
    std::shared_ptr<AnimationComponent> animation;
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<SpriteComponent> sprite;
private:
    const EntityId id;
    const std::string tag;
    bool active = true;
};