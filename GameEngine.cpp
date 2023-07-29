#include <memory>

#include "GameEngine.h"
#include "Scenes/TestScene.h"

void GameEngine::Run() {
    Init();

    running = true;

    while (running) {
        

        if (!paused) {
            Update();
            ProcessEvents();
        }

        // Render
        Render();
        

        currentFrame++;
    }
}

void GameEngine::Quit() {
    running = false;
}

void GameEngine::Update()
{
    currentScene->Update();
}

void GameEngine::ChangeScene(std::string name, std::shared_ptr<Scene> scene) {
    sceneMap[name] = scene;
    currentScene = scene;
}

void GameEngine::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
            {
                Action action {
                    currentScene->GetActionName(event.key.scancode),
                    event.KeyPressed ? Action::Type::START : Action::Type::END
                };
                currentScene->HandleAction(action);
            }
            break;

            case sf::Event::Closed:
            running = false;
            break;

            default:
            break;
        }
    }
}

void GameEngine::Init()
{
    window.create(sf::VideoMode(800, 600), "Game Engine");
    window.setFramerateLimit(frameRate);

    auto initscene = std::make_shared<TestScene>(*this, entityManager);
    
    ChangeScene("test", initscene);
}

void GameEngine::Render() {
    window.clear(sf::Color::Black);

    currentScene->Render(window);

    window.display();
}
