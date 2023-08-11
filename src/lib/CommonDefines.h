#pragma once

#include <cstdint>
#include <memory>

using FrameCount = uint64_t;
using AnimationFrameCount = uint8_t;
using FrameRate = uint16_t;

using EntityId = uint64_t;
constexpr const EntityId MAX_ENTITITES = 1024;

// AssetManager shared pointer shorthand
namespace sf {
    class Texture;
};
using TexturePtr = std::shared_ptr<sf::Texture>;

using FileSize = std::uintmax_t;
constexpr const FileSize MAX_TEXTURE_SIZE = 1024 * 1024 * 10;
