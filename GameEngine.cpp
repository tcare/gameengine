#include "pch.h"
#include "GameEngine.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Scenes/TestScene.h"

GameEngine::GameEngine() {
    InitLogging();
}

GameEngine::~GameEngine() {
    SPDLOG_LOGGER_INFO(logger, "GameEngine shutdown. Cleaning up...");
    spdlog::shutdown();
}

// Main loop of the game engine
void GameEngine::Run()
{
    Init();

    running = true;

    while (running) {
        SPDLOG_LOGGER_TRACE(logger, "Begin frame {}", currentFrame);

        if (!paused) {
            Update();
            ProcessEvents();
        }

        Render();

        SPDLOG_LOGGER_TRACE(logger, "End frame {}", currentFrame);
        currentFrame++;
    }
}

void GameEngine::Quit() {
    running = false;
    SPDLOG_LOGGER_INFO(logger, "Shutting down GameEngine next frame");
}

void GameEngine::Update()
{
    currentScene->Update();
}

void GameEngine::ChangeScene(const std::string& name, const std::shared_ptr<Scene>& scene) {
    sceneMap[name] = scene;
    currentScene = scene;
}

// Process events from SFML. Required for window events and input.
void GameEngine::ProcessEvents() {
    //NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
    // Events use unions, so disable the warning for this block
    sf::Event event{};
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
    //NOLINTEND(cppcoreguidelines-pro-type-union-access)
}

void GameEngine::Init() {
    // Init debugging
    SPDLOG_LOGGER_INFO(logger, "Initializing GameEngine");
    window.create(sf::VideoMode(800, 600), "Game Engine"); //NOLINT(cppcoreguidelines-avoid-magic-numbers)
    window.setFramerateLimit(frameRate);

    auto initscene = std::make_shared<TestScene>();
    
    ChangeScene("test", initscene);
}

// Initialize global spdlog logger
void GameEngine::InitLogging() {
    // Create stdout console logger
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%^%l%$] %v");

    // Create file logger
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("game.log", true);
    file_sink->set_level(spdlog::level::trace);
    file_sink->set_pattern("[%^%l%$ %s:%#] %v");

    // Create combined logger
    using sink_ptr = std::shared_ptr<spdlog::sinks::sink>;
    using sinks_init_list = std::initializer_list<sink_ptr>;
    const sinks_init_list multi_sinks = {console_sink, file_sink};
    logger = std::make_shared<spdlog::logger>("multi_sink", multi_sinks);
    logger->set_level(spdlog::level::trace);

    // Enable auto flush and become default logger
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::set_default_logger(logger);

    SPDLOG_LOGGER_INFO(logger, "Logging initialized");
}

void GameEngine::Render() {
    window.clear(sf::Color::Black);

    currentScene->Render(window);

    window.display();
}
