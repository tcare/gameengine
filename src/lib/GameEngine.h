#pragma once

#include <stack>

#include "CommonDefines.h"
#include "EntityManager.h"
#include "Scene.h"

// Top level class
class GameEngine {
    // Handles loading and unloading of scenes
    
public:
    // Singleton
    GameEngine(GameEngine const&) = delete;
    void operator=(GameEngine const&) = delete;
    GameEngine(GameEngine&&) = delete;
    void operator=(GameEngine&&) = delete;
    static GameEngine& Instance() {
        static GameEngine instance;
        return instance;
    }

    // Runtime flow control
    void Run();
    void Quit();

    // Scene control
    void ChangeScene(const std::string& name, const std::shared_ptr<Scene>& scene);

    // Input control
    void ProcessInput();
    void ProcessEvents();

protected:
    GameEngine();
    ~GameEngine();

private:
    void Init();
    void InitLogging();
    void Render();
    void Update();

    sf::RenderWindow window;

    std::shared_ptr<Scene> currentScene;
    std::map<std::string, std::shared_ptr<Scene>> sceneMap;
    
    bool running = false;
    bool paused = false;
    FrameRate frameRate = 60; //NOLINT(cppcoreguidelines-avoid-magic-numbers)
    FrameCount currentFrame = 0;

    std::shared_ptr<spdlog::logger> logger;
};
