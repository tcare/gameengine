#pragma once

class AssetManager {
public:
    void LoadAssets();

    sf::Texture& GetTexture(std::string name);
    sf::Font& GetFont(std::string name);
private:
    void LoadTexture(std::string name, std::string fileName);
    void LoadFont(std::string name, std::string fileName);

    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};