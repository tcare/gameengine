#pragma once

#include "CommonDefines.h"
#include "Action.h"
#include "EntityManager.h"

// Forward declarations
class GameEngine;
namespace sf {
    class RenderWindow;
};

 // Contains all the entities and actions for a scene
class Scene {
public:
    Scene(GameEngine& engine)
    : engine(engine) {}

    // Update a single frame
    virtual void Update() = 0;
    virtual void HandleAction(Action& action) = 0;
    virtual void Render(sf::RenderWindow &window) = 0;

    Action::Name GetActionName(sf::Keyboard::Scancode scancode) { return actionMap[scancode]; }

protected:
    void RegisterAction(sf::Keyboard::Scancode, Action::Name);

    FrameCount currentFrame = 0;
    bool paused = false;
    ActionMap actionMap;

    EntityManager entityManager;

    // Handy references
    GameEngine& engine;
};