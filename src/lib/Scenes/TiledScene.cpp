#include "TiledScene.h"

TiledScene::TiledScene()
: tiledMap("assets/maps/map.tmx", GetEntityManager()) {

}

void TiledScene::Update() {
    GetEntityManager().Update();
}

void TiledScene::HandleAction(Action &action) {

}

void TiledScene::Render(sf::RenderWindow & window) {
    auto& entityMgr = GetEntityManager();

    // Render background
    auto& bgEntity = entityMgr.GetEntitiesByTag("background");
    for (auto& entity : bgEntity) {
        ASSERT(bgEntity.size() <= 1, "There should only be one background entity");
        auto &bgSprite = entity.GetComponent<SpriteComponent>().GetSprite();
        window.draw(bgSprite);
    }
    
}
