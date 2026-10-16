#pragma once
#include "../GameData/AnimatedSetData.h"
#include <string>
#include <unordered_map>
#include <memory>

class AnimationManager
{
public:
    AnimationManager() = default;
    ~AnimationManager() = default;

    static AnimationManager& GetInstance()
    {
        static AnimationManager am;
        return am;
    }

    bool addAnimationSet(const std::string& name, const AnimatedSetData& data);
    const AnimatedSetData* getAnimationSet(const std::string& name) const;

private:

    std::unordered_map<std::string, AnimatedSetData> m_sets;
};