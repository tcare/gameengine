#include "TestScene.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../GameEngine.h"

TestScene::TestScene()
: Scene() {
    //NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
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

    Entity animationEntity = GetEntityManager().AddEntity();
    animationEntity.AddComponent<SpriteComponent>(texture);
    const Animation animation(
        texture,
        sf::Vector2i(96, 96),
        10,
        sf::Vector2i(0, 1),
        4);
    auto& animationComponent = animationEntity.AddComponent<AnimationComponent>(animation);
    animationComponent.GetAnimation().GetSprite().setPosition(500, 500);

    RegisterAction(sf::Keyboard::Scan::Escape, Action::Name::QUIT);
    //NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
}

void TestScene::Update() {
    GetEntityManager().Update();

    for (auto& entity : GetEntityManager().GetAllEntities()) {
        if (entity.HasComponent<AnimationComponent>()) {
            entity.GetComponent<AnimationComponent>().GetAnimation().Update();
        }
    }
}

void TestScene::HandleAction(Action &action) {
    switch (action.GetName()) {
        case Action::Name::QUIT:
            GameEngine::Instance().Quit();
            break;
        default:
            break;
    }
}

void TestScene::Render(sf::RenderWindow &window) {
    window.draw(text);
    window.draw(sprite);

    for (auto& entity : GetEntityManager().GetAllEntities()) {
        if (entity.HasComponent<AnimationComponent>()) {
            const sf::Sprite& animationSprite = entity.GetComponent<AnimationComponent>().GetAnimation().GetSprite();
            window.draw(animationSprite);
        }
    }
}
