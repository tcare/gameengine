#pragma once

#include <string>
#include "Components.h"
#include "CommonDefines.h"

class Entity {
public:
    Entity(EntityId id, std::string tag)
    : id(id), tag(std::move(tag)) {}

    void Update();
    
    // An inactive entity will be removed on the next frame.
    void SetInactive() { active = false; }

    [[nodiscard]] EntityId GetId() const { return id; }
    [[nodiscard]] const std::string& GetTag() const { return tag; }
    [[nodiscard]] bool IsActive() const { return active; }

    // TODO(tcare): Move these to a component manager
    //NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    std::shared_ptr<AnimationComponent> animation;
    std::shared_ptr<TransformComponent> transform;
    std::shared_ptr<SpriteComponent> sprite;
    //NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

private:
    EntityId id;
    std::string tag;
    bool active = true;
};