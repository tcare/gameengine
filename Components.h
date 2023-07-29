#pragma once

#include <SFML/System/Vector2.hpp>

// Base class for all components which can be attached to an entity
struct Component {

};

struct TransformComponent : public Component {
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Vector2f velocity;
    double rotation;
};

