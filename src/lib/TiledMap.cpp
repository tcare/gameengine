#include "TiledMap.h"

#include "AssetManager.h"
#include "EntityManager.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ImageLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include <iostream>
#include <filesystem>

namespace {
    const std::array<std::string, 4u> LayerStrings = {
        std::string("Tile"),
        std::string("Object"),
        std::string("Image"),
        std::string("Group")
    };
}

void TiledMap::LoadMap(const std::string& path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Map file does not exist");
    }

    if (!map.load(path)) {
        throw std::runtime_error("Failed loading map");
    }

    DumpMapInfo();

    auto& assetMgr = AssetManager::Instance();

    // Load tileset textures
    for (const auto& tileset : map.getTilesets()) {
        assetMgr.LoadTexture(tileset.getImagePath());
    }

    // Process layers by loading textures and creating entities
    bool seenBackground = false;
    const auto& layers = map.getLayers();
    for (const auto& layer : layers) {
        switch (layer->getType()) {
            case tmx::Layer::Type::Image: {
                ASSERT(!seenBackground, "Map has multiple background layers");
                seenBackground = true;

                const auto& imageLayer = layer->getLayerAs<tmx::ImageLayer>();
                
                const auto& texture = assetMgr.LoadTexture(imageLayer.getImagePath());

                auto bgEntity = entityMgr.AddEntity("background");
                bgEntity.AddComponent<SpriteComponent>(*texture);
            }
            break;

            case tmx::Layer::Type::Tile: {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

                auto tileEntity = entityMgr.AddEntity("tile");
                tileEntity.AddComponent<VerticesComponent>(tileLayer.getVertices());
            }

            default:
                continue;
        }
    }


}

void TiledMap::DumpMapInfo() {
    std::cout << "Loaded Map version: " << map.getVersion().upper << ", " << map.getVersion().lower << std::endl;
    if (map.isInfinite()) {
        std::cout << "Map is infinite.\n";
    } else {
        std::cout << "Map Dimensions: " << map.getBounds() << std::endl;
    }

    const auto& mapProperties = map.getProperties();
    std::cout << "Map class: " << map.getClass() << std::endl;

    std::cout << "Map tileset has " << map.getTilesets().size() << " tilesets" << std::endl;
    for (const auto& tileset : map.getTilesets()) {
        std::cout << "- Tileset: " << tileset.getName() << std::endl;
        std::cout << "- Tileset class: " << tileset.getClass() << std::endl;
        std::cout << "- Tileset path: " << tileset.getImagePath() << std::endl;
    }

    std::cout << "Map has " << mapProperties.size() << " properties" << std::endl;
    for (const auto& prop : mapProperties) {
        std::cout << "- Found property: " << prop.getName() << std::endl;
        std::cout << "- Type: " << int(prop.getType()) << std::endl;
    }

    std::cout << std::endl;

    const auto& layers = map.getLayers();
    std::cout << "Map has " << layers.size() << " layers" <<  std::endl;
    for (const auto& layer : layers) {
        std::cout << "Found Layer: " << layer->getName() << std::endl;
        std::cout << "- Layer Type: " << LayerStrings[static_cast<std::int32_t>(layer->getType())] << std::endl;
        std::cout << "- Layer Dimensions: " << layer->getSize() << std::endl;
        std::cout << "- Layer Tint: " << layer->getTintColour() << std::endl;

        switch (layer->getType()) {
            case tmx::Layer::Type::Tile: {
                const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
                if (tiles.empty())
                {
                    const auto& chunks = layer->getLayerAs<tmx::TileLayer>().getChunks();
                    if (chunks.empty()) {
                        std::cout << "- Layer has missing tile data\n";
                    }
                    else
                    {
                        std::cout << "- Layer has " << chunks.size() << " tile chunks.\n";
                    }
                }
                else {
                    std::cout << "- Layer has " << tiles.size() << " tiles.\n";
                }
            }
            break;

            case tmx::Layer::Type::Object: {
                const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();
                std::cout << "- Found " << objects.size() << " objects in layer" << std::endl;
                for(const auto& object : objects) {
                    std::cout << "- Object " << object.getUID() << ", " << object.getName() <<  std::endl;
                    const auto& properties = object.getProperties();
                    std::cout << "  - Object has " << properties.size() << " properties" << std::endl;
                    for(const auto& prop : properties) {
                        std::cout << "  - Found property: " << prop.getName() << std::endl;
                        std::cout << "  - Type: " << int(prop.getType()) << std::endl;
                    }

                    if (!object.getTilesetName().empty()) {
                        std::cout << "- Object uses template tile set " << object.getTilesetName() << "\n";
                    }
                }
            }
            break;

            case tmx::Layer::Type::Image:
                std::cout << "- " << layer->getName() << " has image " << layer->getLayerAs<tmx::ImageLayer>().getImagePath() << std::endl;
                break;

            case tmx::Layer::Type::Group: {
                std::cout << "- Checking sublayers" << std::endl;
                const auto& sublayers = layer->getLayerAs<tmx::LayerGroup>().getLayers();
                std::cout << "- LayerGroup has " << sublayers.size() << " layers" << std::endl;
                for (const auto& sublayer : sublayers) {
                    std::cout << " - Found Layer: " << sublayer->getName() << std::endl;
                    std::cout << " - Sub-layer Type: " << LayerStrings[static_cast<std::int32_t>(sublayer->getType())] << std::endl;
                    std::cout << " - Sub-layer Class: " << sublayer->getClass() << std::endl;
                    std::cout << " - Sub-layer Dimensions: " << sublayer->getSize() << std::endl;
                    std::cout << " - Sub-layer Tint: " << sublayer->getTintColour() << std::endl;

                    if (sublayer->getType() == tmx::Layer::Type::Object) {
                        std::cout << " - " << sublayer->getName() << " has " << sublayer->getLayerAs<tmx::ObjectGroup>().getObjects().size() << " objects" << std::endl;
                    }
                    else if (sublayer->getType() == tmx::Layer::Type::Tile) {
                        std::cout << " - " << sublayer->getName() << " has " << sublayer->getLayerAs<tmx::TileLayer>().getTiles().size() << " tiles" << std::endl;
                    }
                }
            }
            break;
            default:
                std::cout << " - Unhandled layer type" << std::endl;
        }

        const auto& properties = layer->getProperties();
        std::cout << "- " << properties.size() << " Layer Properties:" << std::endl;
        for (const auto& prop : properties) {
            std::cout << "- Found property: " << prop.getName() << std::endl;
            std::cout << "- Type: " << int(prop.getType()) << std::endl;
        }
    }
}
