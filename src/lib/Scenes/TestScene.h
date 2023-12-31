#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Scene.h"
#include "../Entity.h"

class TestScene : public Scene {
public:
    TestScene();

    void Update() override;
    void HandleAction(Action& action) override;
    void Render(sf::RenderWindow &window) override;

private:
    sf::Font font;
    sf::Text text;
    sf::Texture texture;
    sf::Sprite sprite;
};
