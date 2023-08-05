#pragma once

#include <SFML/System/Vector2.hpp>
#include "Animation.h"

// Base class for all components which can be attached to an entity
class Component {
public:
    [[nodiscard]] bool Has() const { return has; }
    void SetHas(bool value) { has = value; }
private:
    bool has = false;
};

class SpriteComponent : public Component {
public:
    SpriteComponent(sf::Texture& texture) : sprite(texture) {}
    [[nodiscard]] sf::Sprite& GetSprite() { return sprite; }
private:
    sf::Sprite sprite;
};

class AnimationComponent : public Component {
public:
    AnimationComponent(Animation animation) : animation(std::move(animation)) {}
    [[nodiscard]] Animation& GetAnimation() { return animation; }
    [[nodiscard]] const Animation& GetAnimation() const { return animation; }
private:
    Animation animation;
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

using ComponentPool = std::tuple<std::vector<TransformComponent>,
                                 std::vector<SpriteComponent>,
                                 std::vector<AnimationComponent>>;
