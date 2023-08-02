#include "TestScene.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../GameEngine.h"

TestScene::TestScene(GameEngine &engine)
: Scene(engine) {
    font.loadFromFile("Assets/Fonts/NintendBoldRM8E.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setString("Hello, world!");
    text.setPosition(100, 100);

    texture.loadFromFile("Assets/Textures/otters.png");
    sprite.setTexture(texture);
    sprite.setPosition(300, 300);
    sprite.setTextureRect(sf::IntRect(96,0,96,96));

    EntityPtr animationEntity = entityManager.AddEntity();
    animationEntity->sprite = std::make_shared<SpriteComponent>(texture);
    animationEntity->sprite->sprite.setPosition(500, 500);
    Animation animation(
        texture,
        animationEntity->sprite->sprite,
        sf::Vector2u(96, 96),
        sf::Vector2u(0, 1),
        4);
    animationEntity->animation = std::make_shared<AnimationComponent>(animation);

    RegisterAction(sf::Keyboard::Scan::Escape, Action::Name::QUIT);
}

void TestScene::Update() {
    entityManager.Update();

    for (auto entity : entityManager.GetAllEntities()) {
        if (entity->animation) {
            entity->animation->animation.Update();
        }
    }
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
    window.draw(sprite);

    for (auto entity : entityManager.GetAllEntities()) {
        if (entity->sprite) {
            window.draw(entity->sprite->sprite);
        }
    }
}
