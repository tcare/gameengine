#include "TestScene.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../GameEngine.h"

TestScene::TestScene(GameEngine &engine, EntityManager &entityManager)
: Scene(engine, entityManager) {
    font.loadFromFile("Assets/Fonts/NintendBoldRM8E.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setString("Hello, world!");
    text.setPosition(100, 100);
    
    RegisterAction(sf::Keyboard::Scan::Escape, Action::Name::QUIT);
}

void TestScene::Update() {
    
}

void TestScene::HandleAction(Action &action) {
    switch (action.name) {
        case Action::Name::QUIT:
            engine.Quit();
            break;
        default:
            break;
    }
}

void TestScene::Render(sf::RenderWindow &window) {
    window.draw(text);
}
