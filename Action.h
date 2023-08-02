#pragma once

#include <map>

#include <SFML/Window.hpp>

class Action {
public:
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
    
    [[nodiscard]] Name GetName() const { return name; }
    [[nodiscard]] Type GetType() const { return type; }
private:
    Name name;
    Type type;
};

// Map from SFML input
typedef std::map<sf::Keyboard::Scancode, Action::Name> ActionMap; //NOLINT(modernize-use-using)
