#include "CommonDefines.h"

class Animation {
public:
    Animation(const sf::Texture& texture,
              const sf::Vector2i spriteSize,
              FrameCount animationSpeed,
              const sf::Vector2i frameZeroOffset,
              const FrameCount animLength);

    // Called on every game frame to potentially update the animation
    void Update();

    void SetAnimationSpeed(FrameCount animationSpeed) {
        this->animationSpeed = animationSpeed;
    }

    [[nodiscard]] sf::Sprite& GetSprite() { return sprite; }

private:
    const sf::IntRect GetSpriteRect();

    sf::Vector2i textureSize;
    // Which frame of the animation is currently being displayed
    AnimationFrameCount currentFrame = 0;

    // The number of frames the animation has been running
    FrameCount runningFrames = 0;

    // The number of frames to wait before switching to the next frame
    AnimationFrameCount animationSpeed;

    // The (x,y) offset of the first frame of the animation (in frames). Use signed to avoid narrowing conversions.
    sf::Vector2i frameZeroOffset;

    // The size of each frame of the animation (in pixels). Use signed to avoid narrowing conversions.
    sf::Vector2i spriteSize;

    // The length of the animation (in frames)
    AnimationFrameCount animLength;

    // Sprite which is being animated
    sf::Sprite sprite;
};