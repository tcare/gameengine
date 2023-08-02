#pragma once

#include <SFML/System/Vector2.hpp>
#include "Animation.h"

// Base class for all components which can be attached to an entity
struct Component {
    bool has = false;
};

struct SpriteComponent : public Component {
    SpriteComponent(sf::Texture& texture) : texture(texture) {}
    sf::Sprite sprite;
    sf::Texture& texture;
};

struct TransformComponent : public Component {
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Vector2f velocity;
    double rotation;
};

struct AnimationComponent : public Component {
    AnimationComponent(Animation& animation) : animation(animation) {}
    Animation animation;
};

typedef std::tuple<TransformComponent, AnimationComponent> ComponentTuple;
