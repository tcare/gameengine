#pragma once

#include <SFML/System/Vector2.hpp>
#include "Animation.h"

// Base class for all components which can be attached to an entity
class Component {
    [[nodiscard]] bool Has() const { return has; }
    bool has = false;
};

class SpriteComponent : public Component {
public:
    SpriteComponent(sf::Texture& texture) : sprite(texture) {}
    [[nodiscard]] sf::Sprite& GetSprite() { return sprite; }
private:
    sf::Sprite sprite;
};

class TransformComponent : public Component {
public:
    TransformComponent(sf::Vector2f position,
                       sf::Vector2f scale,
                       sf::Vector2f velocity,
                       double rotation)
    : position(position),
      scale(scale),
      velocity(velocity),
      rotation(rotation) {}

    [[nodiscard]] sf::Vector2f GetPosition() const { return position; }
    [[nodiscard]] sf::Vector2f GetScale() const { return scale; }
    [[nodiscard]] sf::Vector2f GetVelocity() const { return velocity; }
    [[nodiscard]] double GetRotation() const { return rotation; }
private:
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Vector2f velocity;
    double rotation;
};

class AnimationComponent : public Component {
public:
    AnimationComponent(Animation animation) : animation(std::move(animation)) {}
    [[nodiscard]] Animation& GetAnimation() { return animation; }
private:
    Animation animation;
};

using ComponentTuple = std::tuple<TransformComponent, AnimationComponent>;
