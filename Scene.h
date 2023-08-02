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
    Scene() = default;
    virtual ~Scene() = default;
    
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(Scene&&) = delete;

    // Update a single frame
    virtual void Update() = 0;
    virtual void HandleAction(Action& action) = 0;
    virtual void Render(sf::RenderWindow &window) = 0;

    [[nodiscard]] Action::Name GetActionName(sf::Keyboard::Scancode scancode) { return actionMap[scancode]; }

protected:
    void RegisterAction(sf::Keyboard::Scancode, Action::Name);
    [[nodiscard]] EntityManager& GetEntityManager() { return entityManager; }
    [[nodiscard]] bool IsPaused() { return paused; }
    [[nodiscard]] FrameCount GetCurrentFrame() { return currentFrame; }

private:
    FrameCount currentFrame = 0;
    bool paused = false;
    ActionMap actionMap;

    EntityManager entityManager;
};