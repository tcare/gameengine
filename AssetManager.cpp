#include "AssetManager.h"

void AssetManager::LoadAssets() {

}

void AssetManager::LoadTexture(std::string name, std::string fileName) {
    ASSERT(!name.empty(), "No texture name provided");
    ASSERT(!fileName.empty(), "No texture file name provided");

    if (textures.find(name) != textures.end()) {
        SPDLOG_WARN("Texture {} already loaded", name);
    }

    sf::Texture texture;
    if (!texture.loadFromFile(fileName)) {
        SPDLOG_ERROR("Failed to load texture {}", fileName);
    } else {
        textures[name] = texture;
    }
}

void AssetManager::LoadFont(std::string name, std::string fileName) {
    ASSERT(!name.empty(), "No texture name provided");
    ASSERT(!fileName.empty(), "No texture file name provided");

    if (textures.find(name) != textures.end()) {
        SPDLOG_WARN("Texture {} already loaded", name);
    }

    sf::Font font;
    if (!font.loadFromFile(fileName)) {
        SPDLOG_ERROR("Failed to load texture {}", fileName);
    } else {
        fonts[name] = font;
    }
}
