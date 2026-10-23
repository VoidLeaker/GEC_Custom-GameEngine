#include "GraphicsManager.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "../GameData/AnimatedSetData.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <memory>
#include <string>
#include <iostream>

struct GraphicsManager::priv
{
    struct AnimInstance
    {
        const AnimatedSetData* def = nullptr;
        std::shared_ptr<sf::Texture> texture;
        int currentFrame = 0;
        float timer = 0.f;
    };

    struct SpriteInstance
    {
        sf::Sprite sprite;
        std::map<std::string, AnimInstance> animations;
        std::string currentAnimation;
    };

    std::unordered_map<SpriteId, SpriteInstance> instances;
    SpriteId nextId{ 1 };
};

GraphicsManager::GraphicsManager() = default;

GraphicsManager::~GraphicsManager() = default;

bool GraphicsManager::loadTexture(const std::string& textureName, const std::string& filename)
{
    return TextureManager::GetInstance().loadTexture(textureName, filename);
}

bool GraphicsManager::addAnimationSet(const std::string& animName, const AnimatedSetData& data)
{
    return AnimationManager::GetInstance().addAnimationSet(animName, data);
}

GraphicsManager::SpriteId GraphicsManager::createSprite(const std::string& initialAnim)
{
    if (!privData)
        privData = std::make_unique<priv>();

    const AnimatedSetData* def = AnimationManager::GetInstance().getAnimationSet(initialAnim);
    if (!def)
    {
        std::cerr << "GraphicsManager::createSprite: animation set '" << initialAnim << "' not found\n";
        return 0;
    }

    auto texture = TextureManager::GetInstance().getTexture(def->textureName);
    if (!texture)
    {
        std::cerr << "GraphicsManager::createSprite: texture '" << def->textureName << "' not loaded\n";
        return 0;
    }

    priv::SpriteInstance instance{ sf::Sprite(*texture) };
    priv::AnimInstance animInstance;
    animInstance.def = def;
    animInstance.texture = texture;
    animInstance.currentFrame = 0;
    animInstance.timer = 0.f;

    instance.sprite.setTexture(*texture);
    instance.sprite.setTextureRect(sf::IntRect({0, 0}, {def->frameWidth, def->frameHeight}));

    instance.animations.emplace(initialAnim, animInstance);
    instance.currentAnimation = initialAnim;

    SpriteId id = privData->nextId++;
    privData->instances.emplace(id, std::move(instance));
    return id;
}

void GraphicsManager::destroySprite(SpriteId id)
{
    if (!privData)
        return;

    privData->instances.erase(id);
}

bool GraphicsManager::attachAnimationToSprite(SpriteId id, const std::string& animName)
{
    if (!privData)
        privData = std::make_unique<priv>();

    auto it = privData->instances.find(id);
    if (it == privData->instances.end())
        return false;

    const AnimatedSetData* def = AnimationManager::GetInstance().getAnimationSet(animName);
    if (!def)
        return false;

    auto texture = TextureManager::GetInstance().getTexture(def->textureName);
    if (!texture)
        return false;

    priv::AnimInstance animInstance;
    animInstance.def = def;
    animInstance.texture = texture;
    animInstance.currentFrame = 0;
    animInstance.timer = 0.f;

    it->second.animations.emplace(animName, animInstance);
    return true;
}

void GraphicsManager::setPosition(SpriteId id, Vec2 pos)
{
    if (!privData)
        return;

    auto it = privData->instances.find(id);
    if (it == privData->instances.end())
        return;

    it->second.sprite.setPosition(sf::Vector2f{ pos.x, pos.y });
}

void GraphicsManager::setFlipped(SpriteId id, bool flipped)
{
    if (!privData)
        return;

    auto it = privData->instances.find(id);
    if (it == privData->instances.end())
        return;

    auto& inst = it->second;
    float width = static_cast<float>(inst.sprite.getTextureRect().size.x);

    inst.sprite.setOrigin(sf::Vector2f{ flipped ? width : 0.f, 0.f });
    inst.sprite.setScale(sf::Vector2f{ flipped ? -1.f : 1.f, 1.f });
}

void GraphicsManager::setAnimation(SpriteId id, const std::string& animName)
{
    if (!privData)
        return;

    auto it = privData->instances.find(id);
    if (it == privData->instances.end())
        return;

    if (it->second.animations.find(animName) == it->second.animations.end())
    {
        if (!attachAnimationToSprite(id, animName))
            return;
    }

    it->second.currentAnimation = animName;

    auto& anim = it->second.animations[animName];
    anim.currentFrame = 0;
    anim.timer = 0.f;

    if (anim.texture)
        it->second.sprite.setTexture(*anim.texture);

    if (anim.def)
    {
        it->second.sprite.setTextureRect(
            sf::IntRect({0, 0}, {anim.def->frameWidth, anim.def->frameHeight}));
    }
}

void GraphicsManager::update(float dtSeconds)
{
    if (!privData)
        return;

    for (auto& [id, sprite] : privData->instances)
    {
        if (sprite.currentAnimation.empty())
            continue;

        auto animIt = sprite.animations.find(sprite.currentAnimation);
        if (animIt == sprite.animations.end())
            continue;

        auto& anim = animIt->second;
        const AnimatedSetData* def = anim.def;
        if (!def || !anim.texture)
            continue;

        anim.timer += dtSeconds;

        if (anim.timer >= def->frameSeconds)
        {
            anim.timer -= def->frameSeconds;
            anim.currentFrame++;

            if (anim.currentFrame >= def->numFrames)
            {
                if (def->isLoop)
                    anim.currentFrame = 0;
                else
                    anim.currentFrame = def->numFrames - 1;
            }

            if (def->isHorizontal)
            {
                sprite.sprite.setTextureRect(
                    sf::IntRect({anim.currentFrame * def->frameWidth, 0}, {def->frameWidth, def->frameHeight}));
            }
            else
            {
                sprite.sprite.setTextureRect(
                    sf::IntRect({0, anim.currentFrame * def->frameHeight}, {def->frameWidth, def->frameHeight}));
            }
        }
    }
}

void GraphicsManager::draw(sf::RenderWindow& window)
{
    if (!privData)
        return;

    for (auto& [id, sprite] : privData->instances)
    {
        window.draw(sprite.sprite);
    }
}