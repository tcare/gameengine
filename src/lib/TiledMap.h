#pragma once

#include "pch.h"

#include <SFML/Graphics/Drawable.hpp>
#include <tmxlite/Map.hpp>

class TiledMap {
    class TileMapLayer : public sf::Drawable, public sf::Transformable {
    public:
        TileMapLayer(const tmx::Map& map, const tmx::TileLayer& layer);

        private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = &texture;
            target.draw(vertices, states);
        }
        
        sf::Texture texture;
        sf::VertexArray vertices;
    };

public:
    TiledMap(const std::string& path) {
        LoadMap(path);
    }

private:
    void LoadMap(const std::string& path);
    void DumpMapInfo();
    tmx::Map map;

    sf::Texture bgTexture;
    std::vector<TileMapLayer> tileMapLayers;
};