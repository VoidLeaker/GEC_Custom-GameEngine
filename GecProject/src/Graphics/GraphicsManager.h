#pragma once
#include <cstdint>
#include <string>
#include <memory>

namespace sf { class RenderWindow; }

struct AnimatedSetData;
struct Vec2 { float x{ 0.f }; float y{ 0.f }; };

class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();

    using SpriteId = std::uint32_t;
    using Vec2 = ::Vec2;

    static GraphicsManager& GetInstance()
    {
        static GraphicsManager gm;
        return gm;
    }

    bool loadTexture(const std::string& textureName, const std::string& filename);
    bool addAnimationSet(const std::string& animName, const AnimatedSetData& data);

    SpriteId createSprite(const std::string& initialAnim);
    void destroySprite(SpriteId id);
    bool attachAnimationToSprite(SpriteId id, const std::string& animName);
    
    void setPosition(SpriteId id, Vec2 pos);
    void setFlipped(SpriteId id, bool flipped);
    void setAnimation(SpriteId id, const std::string& animName);
    
    void update(float dtSeconds);
    void draw(sf::RenderWindow& window);

private:
    GraphicsManager(const GraphicsManager&) = delete;
    GraphicsManager& operator=(const GraphicsManager&) = delete;

    struct priv;
    std::unique_ptr<priv> privData;
};