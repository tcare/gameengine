#include "CommonDefines.h"

class Animation {
public:
    Animation(const sf::Texture& texture,
              const sf::Vector2u spriteSize,
              FrameCount animationSpeed,
              const sf::Vector2u frameZeroOffset,
              const FrameCount animLength);

    // Called on every game frame to potentially update the animation
    void Update();

    void SetAnimationSpeed(FrameCount animationSpeed) {
        this->animationSpeed = animationSpeed;
    }

    [[nodiscard]] sf::Sprite& GetSprite() { return sprite; }

private:
    const sf::IntRect GetSpriteRect();

    sf::Vector2u textureSize;
    // Which frame of the animation is currently being displayed
    FrameCount currentFrame = 0;

    // The number of frames the animation has been running
    FrameCount runningFrames = 0;

    // The number of frames to wait before switching to the next frame
    FrameCount animationSpeed;

    // The (x,y) offset of the first frame of the animation (in frames)
    sf::Vector2u frameZeroOffset;

    // The size of each frame of the animation (in pixels)
    sf::Vector2u spriteSize;

    // The length of the animation (in frames)
    FrameCount animLength;

    // Sprite which is being animated
    sf::Sprite sprite;
};