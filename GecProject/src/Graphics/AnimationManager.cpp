#include "AnimationManager.h"

bool AnimationManager::addAnimationSet(const std::string& name, const AnimatedSetData& data)
{
    if (name.empty())
        return false;
    auto it = m_sets.find(name);
    if (it != m_sets.end())
        return false;

    m_sets.emplace(name, data);
    return true;
}

const AnimatedSetData* AnimationManager::getAnimationSet(const std::string& name) const
{
    auto it = m_sets.find(name);
    if (it == m_sets.end())
        return nullptr;
    return &it->second;
}