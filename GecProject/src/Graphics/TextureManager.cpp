#include "TextureManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

bool TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    if (name.empty() || filename.empty())
        return false;

    auto it = m_textures.find(name);
    if (it != m_textures.end())
        return true;

    auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(filename))
    {
        std::cerr << "TextureManager: failed to load texture '" << filename << "'\n";
        return false;
    }

    m_textures.emplace(name, std::move(tex));
    return true;
}

std::shared_ptr<sf::Texture> TextureManager::getTexture(const std::string& name) const
{
    auto it = m_textures.find(name);
    if (it == m_textures.end())
        return nullptr;
    return it->second;
}