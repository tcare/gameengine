#pragma once

#include <string>

#include "Components.h"

class Entity {
public:
    Entity(uint32_t id, std::string tag) : id(id), tag(tag) {}

    void AddComponent(Component& component);
    void RemoveComponent(Component& component);
    void HasComponent(Component& component);
private:
    uint32_t id;
    std::string tag;
    std::vector<Component> components;
};