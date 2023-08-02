#include "CommonDefines.h"

class Animation {
public:
    Animation(const sf::Texture& texture,
              sf::Sprite& sprite,
              const sf::Vector2u spriteSize,
              const sf::Vector2u frameZeroOffset,
              const FrameCount animLength);

    // Called on every game frame to potentially update the animation
    void Update();

private:
    const sf::IntRect GetSpriteRect();
    // Which frame of the animation is currently being displayed
    FrameCount currentFrame = 0;

    // The number of frames the animation has been running
    FrameCount runningFrames = 0;

    // The number of frames to wait before switching to the next frame
    FrameCount animationSpeed = 10;

    // The (x,y) offset of the first frame of the animation (in frames)
    const sf::Vector2u frameZeroOffset;

    // The size of each frame of the animation (in pixels)
    const sf::Vector2u spriteSize;

    // The length of the animation (in frames)
    const FrameCount animLength;

    // Reference to the texture containing the animation frames
    const sf::Texture& texture;

    // Reference to the sprite which is being animated
    sf::Sprite& sprite;
};