#pragma once

#include "../Scene.h"
#include "../Entity.h"
#include "../TiledMap.h"

class TiledScene : public Scene {
public:
    TiledScene();

    void Update() override;
    void HandleAction(Action& action) override;
    void Render(sf::RenderWindow &window) override;

private:
    TiledMap tiledMap;
};
