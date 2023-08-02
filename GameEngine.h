#pragma once

#include "pch.h"

#include <stack>

#include "CommonDefines.h"
#include "EntityManager.h"
#include "Scene.h"

// Top level class
class GameEngine {
    // Handles loading and unloading of scenes
    
public:
    GameEngine();
    ~GameEngine();

    // Runtime flow control
    void Run();
    void Quit();

    // Scene control
    void ChangeScene(std::string name, std::shared_ptr<Scene> scene);

    // Input control
    void ProcessInput();
    void ProcessEvents();
    
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
    FrameRate frameRate = 60;
    FrameCount currentFrame = 0;

    std::shared_ptr<spdlog::logger> logger;
};
