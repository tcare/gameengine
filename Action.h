#pragma once

#include <map>

#include <SFML/Window.hpp>

struct Action {
    enum class Name {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        PAUSE,
        QUIT
    };
    enum class Type {
        START,
        END
    };

    Action(Name name, Type type) : name(name), type(type) {}
    
    const Name name;
    const Type type;
};

// Map from SFML input
typedef std::map<sf::Keyboard::Scancode, Action::Name> ActionMap;
