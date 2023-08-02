#include "Animation.h"

#include <SFML/Graphics/Rect.hpp>

Animation::Animation(const sf::Texture &texture,
                     sf::Sprite &sprite,
                     const sf::Vector2u spriteSize,
                     const sf::Vector2u frameZeroOffset,
                     const FrameCount animLength)
    : texture(texture),
    sprite(sprite),
    spriteSize(spriteSize),
    frameZeroOffset(frameZeroOffset),
    animLength(animLength) {
    ASSERT(animLength > 1, "Why use an animation if there's only one frame?");
    sprite.setTexture(texture);
    sprite.setTextureRect(GetSpriteRect());
}

void Animation::Update() {
    runningFrames++;

    // If we are advancing to the next frame of animation, update the sprite
    FrameCount newCurrentFrame = runningFrames / animationSpeed % animLength;
    if (newCurrentFrame != currentFrame) {
        SPDLOG_DEBUG("Updating animation frame from {} to {}", currentFrame, newCurrentFrame);
        currentFrame = newCurrentFrame;
        sprite.setTextureRect(GetSpriteRect());
    }
}

const sf::IntRect Animation::GetSpriteRect() {
    // Get width and height of the texture
    auto textureSize = texture.getSize();

    // Calculate current frame offset
    auto framesPerRow = textureSize.x / spriteSize.x;
    auto framesPerColumn = textureSize.y / spriteSize.y;
    
    auto newRow = frameZeroOffset.x + currentFrame % framesPerRow;
    auto newColumn = frameZeroOffset.y + currentFrame / framesPerColumn;

    auto topLeftX = newRow * spriteSize.x;
    auto topLeftY = newColumn * spriteSize.y;

    SPDLOG_TRACE("New animation frame: ({}, {}) pixels: ({}, {})", newRow, newColumn, topLeftX, topLeftY);

    // Return the rectangle
    return sf::IntRect(topLeftX, topLeftY, spriteSize.x, spriteSize.y);
}
