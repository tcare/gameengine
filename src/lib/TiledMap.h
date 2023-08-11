#pragma once

#include "pch.h"

#include <SFML/Graphics/Drawable.hpp>
#include <tmxlite/Map.hpp>

class EntityManager;

class TiledMap {

public:
    TiledMap(const std::string& path, EntityManager& entityMgr) : entityMgr(entityMgr) {
        LoadMap(path);
    }

    void Render(sf::RenderWindow& window) {
        //window.draw(tileMapLayers[0]);
    }

private:
    void LoadMap(const std::string& path);
    void DumpMapInfo();
    tmx::Map map;
    EntityManager& entityMgr;
};