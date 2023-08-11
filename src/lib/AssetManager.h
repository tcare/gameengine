#pragma once

#include "CommonDefines.h"

#include <string>

class AssetManager {
public:
    // Singleton
    AssetManager(AssetManager const&) = delete;
    void operator=(AssetManager const&) = delete;
    AssetManager(AssetManager&&) = delete;
    void operator=(AssetManager&&) = delete;
    static AssetManager& Instance() {
        static AssetManager instance;
        return instance;
    }

    AssetManager() = default;

    [[nodiscard]] TexturePtr GetTexture(const std::string& name);

    TexturePtr LoadTexture(const std::string& name, const std::string& path);
    TexturePtr LoadTexture(const std::string& path) { return LoadTexture(path, path); }
private:
    std::map<std::string, TexturePtr> textures;
};