#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace sf { class Texture; }

// Singleton class that manages textures. It allows loading and retrieving textures by name.
class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager() = default;

	static TextureManager& GetInstance()
	{
		static TextureManager tm;
		return tm;
	}

	bool loadTexture(const std::string& name, const std::string& filename);

	std::shared_ptr<sf::Texture> getTexture(const std::string& name) const;
private:

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
};