#include "AssetManager.h"

#include <filesystem>

TexturePtr AssetManager::GetTexture(const std::string& name) {
    VERIFY(!name.empty(), "No texture name provided");
    VERIFY(textures.contains(name), "Trying to use an unloaded texture");
    return textures[name];
}

TexturePtr AssetManager::LoadTexture(const std::string& name, const std::string& path) {
    VERIFY(!name.empty(), "No texture name provided");
    VERIFY(!path.empty(), "No texture file name provided");

    if (textures.contains(name)) {
        SPDLOG_WARN("Texture {} already loaded", name);
        return textures[name];
    }

    VERIFY(std::filesystem::exists(path), "Texture file does not exist");

    auto fileSize = std::filesystem::file_size(path);
    VERIFY(fileSize != 0, "Texture file is empty");
    
    VERIFY(fileSize <= MAX_TEXTURE_SIZE, "Texture file is too large");

    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        SPDLOG_ERROR("Failed to load texture {}", path);
        VERIFY(false, "Failed to load texture");
    } else {
        textures[name] = std::make_shared<sf::Texture>(std::move(texture));
    }

    SPDLOG_INFO("Loaded texture {} from {} | {}b | {}x{}", name, path, fileSize, texture.getSize().x, texture.getSize().y);
    return textures[name];
}

